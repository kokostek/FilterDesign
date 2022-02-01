#include "Tests.h"

#include <iostream>

int main()
{
    std::cout << "==== Single precision tests ====\n";
    
    std::cout << "\tTestHamming()...";
    FilterDesign::Tests<float>::TestHamming();
    std::cout << " OK\n";

    std::cout << "\tTestWindowedSincLowPass()...";
    FilterDesign::Tests<float>::TestWindowedSincLowPass();
    std::cout << " OK\n";

    std::cout << "==== Double precision tests ====\n";
    
    std::cout << "\tTestHamming()...";
    FilterDesign::Tests<double>::TestHamming();
    std::cout << " OK\n";

    std::cout << "\tTestWindowedSincLowPass()...";
    FilterDesign::Tests<double>::TestWindowedSincLowPass();
    std::cout << " OK\n";

    return EXIT_SUCCESS;
}