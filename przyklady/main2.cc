#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>

using std::abs;
using std::accumulate;
using std::cout;
using std::endl;
using std::for_each;
using std::stable_sort;
using std::transform;
using std::vector;
int main()
{
    vector<int> v{1, 2, 3, 4, 5};
    transform(v.begin(), v.end(), v.begin(),
              [](const auto &n)
              { return n * 2; });
    for_each(v.begin(), v.end(),
             [](const auto &n)
             { cout << n << ' '; });
    // Sumowanie elementów z wektora v
    cout << endl
         << accumulate(v.begin(), v.end(), 0) << endl;
    // Odejmowanie od 100 kolejnych elementów z wektora v
    cout << accumulate(v.begin(), v.end(), 100,
                       [](const auto &init, const auto &a)
                       {
                           return init - a;
                       })
         << endl;
    // Sortowanie elementów w wektorze u, względem modułu liczb
    vector<int> u{-2, -1, 0, 1, 2, 3, 4};
    stable_sort(u.begin(), u.end(),
                [](const auto &l, const auto &r)
                {
                    return abs(l) < abs(r);
                });
    for_each(u.begin(), u.end(),
             [](const auto &n)
             { cout << n << ' '; });
    cout << endl;
}
