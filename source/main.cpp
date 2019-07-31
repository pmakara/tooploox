#include <string>
#include <iostream>

#include "MedianCalculator.hpp"

int main()
{
    ToopLoox::MedianCalculator calculator;

    while (true)
    {
        std::string nextToken;
        std::cin >> nextToken;

        if (nextToken == "q")
        {
            break;
        }
        else if (nextToken == "m")
        {
            std::cout << calculator.getMedian() << " " << std::flush;
        }
        else
        {
            try
            {
                calculator.addNumber(std::stoi(nextToken));
            }
            catch (const std::exception&)
            {
                std::cerr << "Invalid integer: " << nextToken << std::endl;
            }
        }

    }

    return 0;
}