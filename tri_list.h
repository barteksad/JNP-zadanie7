#ifndef TRI_LIST_H
#define TRI_LIST_H

#include "tri_list_concepts.h"

#include <variant>
#include <list>
#include <ranges>
#include <functional>

namespace
{

    template <typename T, typename T1, typename T2, typename T3>
    concept one_of_tri = (std::same_as<T1, T> || std::same_as<T2, T> || std::same_as<T3, T>);

}; // namespace

template <typename T1, typename T2, typename T3>
class tri_list
{
private:
    using tri_type = std::variant<T1, T2, T3>;
    using tri_container = std::list<tri_type>;

    tri_container elems;
    std::function<tri_type(tri_type)> modifiers;

public:
    tri_list()
    {
        modifiers = std::identity();
    }

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    void push_back(const T &t)
    {
        elems.push_back(t);
    }

    template <typename T, modifier<T> F>
    requires one_of_tri<T, T1, T2, T3>
    void modify_only(F m = F{})
    {
        modifiers = [*this, m](tri_type elem) -> tri_type
        {
            elem = modifiers(elem);
            if (std::holds_alternative<T>(elem))
                return tri_type(std::invoke(m, std::get<T>(elem)));
            else
                return elem;
        };
    }

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    void reset()
    {
        modifiers = std::identity();
    }

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    auto range_over()
    {
        auto filter_modifier = [](const tri_type &elem)
        {
            return std::holds_alternative<T>(elem);
        };

        auto get_value = [](const tri_type &elem)
        {
            return std::get<T>(elem);
        };

        return elems | std::views::transform(modifiers)
                     | std::views::filter(filter_modifier) 
                     | std::views::transform(get_value);
    }
};

#endif // TRI_LIST_H