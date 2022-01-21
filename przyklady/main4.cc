#include <variant>
#include <vector>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
using std::get;
using std::same_as;
using std::string;
using std::variant;
using std::vector;
using std::visit;
int main()
{
    using func_t = function<int()>;
    variant<int, float, string, func_t> var;
    var = 1;
    cout << get<int>(var) << endl;
    cout << get<0>(var) << endl;
    // cout << get<float>(var) << endl; // wyjątek
    var = "napis";
    cout << get<string>(var) << endl;
    cout << get<2>(var) << endl;
    // cout << get<1>(var) << endl; // wyjątek
    var = []()
    { return 127 * 2; };
    cout << get<func_t>(var)() << endl;
    cout << get<3>(var)() << endl;
    vector<variant<double, int>> vars = {5, -0.125, 0, -3, 0.5};
    auto is_int_func = []<typename T>(T t)
    {
        if constexpr (same_as<T, int>)
        {
            cout << "jest int: " << t << endl;
        }
        else
        {
            cout << "nie int: " << t << endl;
        }
    };
    for (auto it = vars.begin(); it != vars.end(); ++it)
        visit(is_int_func, *it);
}