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

    // template <typename T>
    // class Iterator
    // {
    // public:
    //     using iterator_category = std::input_iterator_tag ;
    //     using difference_type = std::ptrdiff_t;
    //     using value_type = T;
    //     Iterator();                              // default-initializable
    //     // bool operator==(const Sentinel &) const; // equality with sentinel
    //     T &operator*() const
    //     {
    //         return std::get<T>(*ptr);
    //     }
    //     Iterator &operator++() // pre-incrementable
    //     {                      /*do stuff...*/
    //         return *this;
    //     }
    //     void operator++(int) // post-incrementable
    //     {
    //         ++*this;
    //     }

    //     // ...same as the previous one, except:
    //     bool operator==(const Iterator &) const; // equality with iterators
    //     Iterator operator++(int)                 // post-incrementable, returns prev value
    //     {
    //         auto temp = *this;
    //         ++*this;
    //         return temp;
    //     }

    // private:
    //     typename tri_container::iterator ptr; 
    // };

public:

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
    }
};

#endif // TRI_LIST_H