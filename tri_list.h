#ifndef TRI_LIST_H
#define TRI_LIST_H

#include "tri_list_concepts.h"

#include <variant>
#include <list>

namespace {

    template <typename T, typename T1, typename T2, typename T3>
    concept one_of_tri = (std::same_as<T1, T> || std::same_as<T2, T> || std::same_as<T3, T>);

}; // namespace

template<typename T1, typename T2, typename T3>
class tri_list
{
public:

    tri_list()=default;

    template <typename T>
    requires one_of_tri<T, T1, T2, T3>
    void push_back(const T& t)
    {
        
    }

    template <typename T, modifier<T> F> 
    void modify_only(F m = F{})
    {

    }

    template <typename T> 
    void reset()
    {

    }

    template <typename T> 
    auto range_over()
    {

    }

    // begin() end()

private:
    std::list<std::variant<T1, T2, T3>> elems;

    template <typename T>
    class Iterator;

};

// template <typename T>
// class Iterator
// {
// public:
//     using difference_type = std::ptrdiff_t;
//     using value_type = T;
//     Iterator();                 // default-initializable
//     bool operator == (const Sentinel&) const;   // equality with sentinel
//     T& operator * () const;     // dereferenceable
//     Iterator& operator ++ ()    // pre-incrementable
//         { /*do stuff...*/ return *this; }
//     void operator ++ (int)      // post-incrementable
//         { ++*this; }
// private:
//     // implementation...
// };

#endif // TRI_LIST_H