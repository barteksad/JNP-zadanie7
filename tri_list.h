#ifndef TRI_LIST_H
#define TRI_LIST_H

#include "tri_list_concepts.h"

#include <variant>
#include <list>
#include <ranges>
#include <functional>
#include <iterator>
#include <cstddef>

namespace
{

    template <typename T, typename T1, typename T2, typename T3>
    concept one_of_tri = (std::same_as<T1, T> || std::same_as<T2, T> || std::same_as<T3, T>);

}; // namespace

template <typename T1, typename T2, typename T3>
class tri_list
{
private:
    using tri_type_t = std::variant<T1, T2, T3>;
    using tri_container = std::list<tri_type_t>;
    using tri_modifiers_f = std::function<tri_type_t(tri_type_t)>;

    tri_container elems;
    tri_modifiers_f modifiers;

    struct Iterator 
    {
        private:

            typename tri_container::const_iterator m_ptr;
            tri_modifiers_f m_modifiers;

        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = tri_type_t;
            using pointer           = const value_type*;
            using reference         = const value_type;

            Iterator(decltype(m_ptr) _ptr, tri_modifiers_f _modifiers) : m_ptr(_ptr), m_modifiers(_modifiers) {}

            reference operator*() const 
            {
                auto value = m_modifiers(*m_ptr);
                return value; 
            }

            pointer operator->() { return m_ptr; }

            Iterator& operator++() { m_ptr++; return *this; }  

            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };  

    };

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
        modifiers = [*this, m](tri_type_t elem) -> tri_type_t
        {
            elem = modifiers(elem);
            if (std::holds_alternative<T>(elem))
                return tri_type_t(std::invoke(m, std::get<T>(elem)));
            else
                return elem;
        };
    }

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    void reset()
    {
        modifiers = [*this](tri_type_t elem) -> tri_type_t
        {
            if (std::holds_alternative<T>(elem))
                return elem;
            else
                return tri_type_t(std::invoke(modifiers, elem));
        };
    }

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    auto range_over()
    {
        auto filter_modifier = [](const tri_type_t &elem)
        {
            return std::holds_alternative<T>(elem);
        };

        auto get_value = [](const tri_type_t &elem)
        {
            return std::get<T>(elem);
        };

        return elems | std::views::transform(modifiers)
                     | std::views::filter(filter_modifier) 
                     | std::views::transform(get_value);
    }

    Iterator begin() { return Iterator(elems.begin(), modifiers); }
    Iterator end()   { return Iterator(elems.end(), modifiers); }
};

#endif // TRI_LIST_H