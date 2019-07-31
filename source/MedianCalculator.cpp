#include "MedianCalculator.hpp"

namespace ToopLoox
{

void MedianCalculator::addNumber(int value) 
{
	tree.add(value);
}

double MedianCalculator::getMedian() const
{
	if (tree.getSize() == 0)
	{
		throw std::runtime_error("Couldn't calculate median from empty set");
	}

	if (tree.getSize() % 2 == 1)
	{
		return tree[tree.getSize() / 2];
	}

	return (tree[tree.getSize() / 2] + tree[tree.getSize() / 2 - 1]) / 2.0;
}

}
