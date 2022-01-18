#ifndef TRI_LIST_H
#define TRI_LIST_H

#include "tri_list_concepts.h"

#include <variant>
#include <list>
#include <ranges>

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
    std::ranges::ref_view<tri_container> modified_elems;

public:

    tri_list()
    {
        modified_elems = std::views::all(elems);
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
        auto wrapped_modifier = [&](tri_type elem)
        {
            if constexpr(std::holds_alternative<T>(elem))
                return visit(m, elem);
            else
                return elem;
        };

        modified_elems = elems | std::views::transform(wrapped_modifier);
    }

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    void reset()
    {
    }

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    auto range_over()
    {
        auto filter_modifier = [&](tri_type elem)
        {
            return std::holds_alternative<T>(elem);
        };

        return modified_elems | std::views::filter(filter_modifier) | std::views::transform([](tri_type elem){return std::get<T>(elem);});
    }
};

#endif // TRI_LIST_H