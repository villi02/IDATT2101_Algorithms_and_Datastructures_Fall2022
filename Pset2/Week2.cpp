#include <iostream>
#include <time.h>
#include <stdio.h>
#include <math.h>

// Task 2.1-1
// Calculates x to the power of n
double calc_pow(double base, int power)
{
    if (power == 0)
        return 1;

    else
        return base * calc_pow(base, (power - 1));
}

double calc_pow2(double base, int power)
{
    if (power == 0)
        return 1;

    else if (power % 2 == 0)
        return calc_pow2(base * base, power / 2);

    else
        return (base * calc_pow2(base * base, (power - 1) / 2));
}

int main(void)
{

    // Test data
    std::cout << "\n (2.1-1) "
              << "2"
              << " raised to the "
              << "power of "
              << "12"
              << " is " << calc_pow(2, 12) << std::endl;
    std::cout << "\n (2.1-1) "
              << "3"
              << " raised to the "
              << "power of "
              << "14"
              << " is " << calc_pow(3, 14) << std::endl;

    std::cout << "\n (2.2-3) "
              << "2"
              << " raised to the "
              << "power of "
              << "12"
              << " is " << calc_pow2(2, 12) << std::endl;
    std::cout << "\n (2.2-3) "
              << "3"
              << " raised to the "
              << "power of "
              << "14"
              << " is " << calc_pow2(3, 14) << std::endl;

    // Create a user input
    double base;
    std::cout << "\nEnter Base : ";
    std::cin >> base;

    int power;
    std::cout << "\nEnter power : ";
    std::cin >> power;

    // Get starting timepoint
    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();

    double result1 = calc_pow(base, power);

    // Get ending timepoint
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    long duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count();

    std::cout << "\n (2.1-1) "
              << base << " raised to the "
              << "power of " << power << " is " << result1
              << "\nDuration of function: " << duration1 << "[µs]"
              << std::endl;

    // Get starting timepoint
    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();

    double result2 = calc_pow2(base, power);

    // Get ending timepoint
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    long duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count();

    std::cout << "\n (2.2-3) "
              << base << " raised to the "
              << "power of " << power << " is " << result2
              << "\nDuration of function: " << duration2 << "[µs]"
              << std::endl;

    time_t startTime;
    time_t now;
    float elapsedTime;
    float setTime = 60;

    double base_normal = 1.001;

    int powers[] = {200, 400, 800, 1600, 3200, 6337};

    for (int i = 0; i < 6; i++)
    {
        // Get starting timepoint
        std::chrono::steady_clock::time_point begin221 = std::chrono::steady_clock::now();

        for (int j = 0; j < 1000000; j++)
        {
            calc_pow(base_normal, powers[i]);
        }
        // Get ending timepoint
        std::chrono::steady_clock::time_point end221 = std::chrono::steady_clock::now();
        long duration221 = std::chrono::duration_cast<std::chrono::microseconds>(end221 - begin221).count();

        std::cout << "\n (2.1-1) "
                  << " base: 1.001 "
                  << "power: " << powers[i] << " run 100 000 times"
                  << "\nDuration of function: " << duration221 << "[µs]"
                  << std::endl;

        // Get starting timepoint
        std::chrono::steady_clock::time_point begin233 = std::chrono::steady_clock::now();

        for (int j = 0; j < 10000; j++)
        {
            calc_pow2(base_normal, powers[i]);
        }
        // Get ending timepoint
        std::chrono::steady_clock::time_point end233 = std::chrono::steady_clock::now();
        long duration233 = std::chrono::duration_cast<std::chrono::microseconds>(end233 - begin233).count();

        std::cout << "\n (2.2-3) "
                  << " base: 1.001 "
                  << "power: " << powers[i] << " run 100 000 times"
                  << "\nDuration of function: " << duration233 << "[µs]"
                  << std::endl;

        // Get starting timepoint
        std::chrono::steady_clock::time_point beginBuiltInn = std::chrono::steady_clock::now();

        for (int j = 0; j < 10000; j++)
        {
            pow(base_normal, powers[i]);
        }
        // Get ending timepoint
        std::chrono::steady_clock::time_point endBuiltInn = std::chrono::steady_clock::now();
        long durationBuiltInn = std::chrono::duration_cast<std::chrono::microseconds>(endBuiltInn - beginBuiltInn).count();

        std::cout << "\n (Built inn function) "
                  << " base: 1.001 "
                  << "power: " << powers[i] << " run 100 000 times"
                  << "\nDuration of function: " << durationBuiltInn << "[µs]"
                  << std::endl;
    }
}
