#pragma once

#include "OrderStatsTree.hpp"

namespace ToopLoox
{

class MedianCalculator
{
public:
	void addNumber(int value);
	double getMedian() const;

private:
	OrderStatsTree<int> tree;
};

}
