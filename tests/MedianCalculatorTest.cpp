#include "../source/MedianCalculator.hpp"
#include <gtest/gtest.h>

using namespace ToopLoox;


TEST(MedianCalculatorTest, EmptySetTest) 
{
	MedianCalculator calc;
	ASSERT_THROW(calc.getMedian(), std::runtime_error);
}

TEST(MedianCalculatorTest, CornerCasesTest) 
{
	{
		MedianCalculator calc;
		calc.addNumber(10);
		EXPECT_DOUBLE_EQ(10.0, calc.getMedian());
	}

	{
		MedianCalculator calc;
		calc.addNumber(10);
		calc.addNumber(11);
		EXPECT_DOUBLE_EQ(10.5, calc.getMedian());
	}	

	{
		MedianCalculator calc;
		calc.addNumber(10);
		calc.addNumber(10);
		calc.addNumber(10);
		EXPECT_DOUBLE_EQ(10.0, calc.getMedian());
	}		
}

TEST(MedianCalculatorTest, UserSimulationTest) 
{
	MedianCalculator calc;
	calc.addNumber(6);
	calc.addNumber(8);
	EXPECT_DOUBLE_EQ(7.0, calc.getMedian());

	calc.addNumber(1);
	calc.addNumber(1);
	calc.addNumber(1);
	calc.addNumber(1);
	calc.addNumber(1);
	EXPECT_DOUBLE_EQ(1.0, calc.getMedian());

	calc.addNumber(9);
	calc.addNumber(9);
	calc.addNumber(9);
	EXPECT_DOUBLE_EQ(3.5, calc.getMedian());
}




