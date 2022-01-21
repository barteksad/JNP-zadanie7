#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::ranges::sort;
using std::views::filter;
using std::views::reverse;
using std::views::transform;
int main()
{
    vector<int> numbers = {5, 3, 2, 1, 6, 4};
    auto even_func = [](int n)
    { return n % 2 == 0; };
    auto double_func = [](int n)
    { return n * 2; };
    auto print = [](auto vec)
    {
        for (auto const &v : vec)
            cout << v << " ";
        cout << endl;
    };
    //* Składanie widoków za pomocą operatora | (tzw. pipe operator)
    auto results = numbers | filter(even_func) |
                   transform(double_func) | reverse;
    //*/
    /* Alternatywnie bez operatora |
    auto results =
    reverse(transform(filter(numbers, even_func), double_func));
    //*/
    // Wydruki
    print(results);
    print(numbers);
    print(results);
    print(numbers | transform(double_func) | reverse);
    print(reverse(transform(numbers, double_func)));
    // Późniejsza modyfikacja wektora numbers
    numbers.push_back(2);
    print(numbers);
    print(results);
    // Sortowanie
    sort(numbers);
    print(numbers);
    auto rev_numbers = numbers | reverse;
    print(rev_numbers);
    sort(rev_numbers);
    print(rev_numbers);
    // sort(results); // Error
    vector vec_results(results.begin(), results.end());
    print(vec_results);
    sort(vec_results);
    print(vec_results);
}