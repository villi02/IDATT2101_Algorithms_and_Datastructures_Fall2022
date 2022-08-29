#include <iostream>

// Task 2.1-1
// Calculates x to the power of n
int calc_pow(int base, int power)
{
    if (power == 0)
        return 1;

    else if (power == 1)
        return base;
    else 
        return base * calc_pow(base, (power -1));
}

int main(void) 
{

    // Test data
    std::cout << "\n (2.1-1) " << "2" << " raised to the " << "power of " << "12" << " is " << calc_pow(2, 12) << std::endl; 
    std::cout << "\n (2.1-1) " << "3" << " raised to the " << "power of " << "14" << " is " << calc_pow(3, 14) << std::endl; 

    // Create a user input 
    int base;
    std::cout << "\nEnter Base : ";
    std::cin >> base;

    int power;
    std::cout << "\nEnter power : ";
    std::cin >> power;

    int result = calc_pow(base, power);

    std::cout << "\n" << base << " raised to the " << "power of " << power << " is " << result << std::endl; 
}