#include <iostream>
#include "gtest/gtest.h"
#include "ConcurrentQueue.h"


void Produce(XYZCore::ConcurrentQueue<int>& q, int nbToProduce)
{
	for (int i = 1; i <= nbToProduce; ++i)
	{
		q.push(i);
	}
}

void Consume(XYZCore::ConcurrentQueue<int>& q, std::vector<int> &result, int nbToConsume)
{
	for (int i = 0; i < nbToConsume; ++i)
	{
		auto item = q.pop();
		result.push_back(item);
	}
}

TEST(ConcurrentQueue, MultipleConsumerTest)
{
	const int nbConsumers = 4;
	const int nbToConsume = 3;
	const int nbToProduce = nbToConsume * nbConsumers;
	std::vector<int> result;
	XYZCore::ConcurrentQueue<int> q;

	std::thread prod1(std::bind(Produce, std::ref(q), nbToProduce));

	std::vector<std::thread> consumers;
	for (int i = 0; i < nbConsumers; ++i)
	{
		std::thread consumer(std::bind(&Consume, std::ref(q), std::ref(result), nbToConsume));
		consumers.push_back(std::move(consumer));
	}

	prod1.join();

	for (auto& consumer : consumers) {
		consumer.join();
	}

	std::vector<int> expect{ 1,2,3,4,5,6,7,8,9,10,11,12 };
	EXPECT_EQ(expect, result);
}