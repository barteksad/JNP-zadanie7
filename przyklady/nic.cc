#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <variant>

using std::abs;
using std::accumulate;
using std::cout;
using std::endl;

template<typename A, typename B>
requires std::same_as<A, B>
void nic(A a, B b)
{

}

int main()
{
    auto x = std::variant<int, float>(1);
    int y = 2;

    nic(x, y)
}
