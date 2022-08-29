#include <algorithm>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using namespace std::chrono;

int maxProfit(int changes[], int n, int *buy_day, int *sell_day)
{
    int buy = changes[0], max_profit = 0, current_price = 0, temp_buy_day = 0;
    ;
    for (int i = 1; i < n; i++)
    {

        current_price += changes[i];

        // Checking for lower buy value
        if (buy > current_price)
        {
            buy = current_price;
            temp_buy_day = i + 1;
        }

        // Checking for higher profit
        else if (current_price - buy > max_profit)
        {
            max_profit = current_price - buy;
            *sell_day = i + 1;
            *buy_day = temp_buy_day;
        }
    }
    return max_profit;
}

void randomArray(int change_array[], int n)
{
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen(rd());                         // seed the generator
    std::uniform_int_distribution<> distr(-10, 10); // define the range

    for (int i = 0; i < n; ++i)
        change_array[i] = distr(gen);
}

int main(void)
{
    // Create a user input size
    int size;
    std::cout << "Enter Size Of Array : ";
    std::cin >> size;

    int *changes = new int[size];
    randomArray(changes, size);

    int buy_day, sell_day;

    // Display whats in the array...
    // for (int i = 0; i < size; ++i)
    //{
    // std::cout << "Item In Element " << i << " of the array = : " << changes[i] << std::endl;
    //}

    // Get starting timepoint
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // Call the function
    int max_profit = maxProfit(changes, size, &buy_day, &sell_day);

    // Get ending timepoint
    // end = clock();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    // auto diff = end - start;

    cout << "\nThe day to buy is day nr " << buy_day << " and the day to sell is day nr "
         << sell_day << " and max profit pr share is " << max_profit;

    std::cout << "\nDuration of function = " << duration << "[µs]" << std::endl;

    return 0;
}