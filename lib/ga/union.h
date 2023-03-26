/*
 * union.h
 *
 * Union class header file.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 *
 * 26.03.2023  tstih
 *
 */

#ifndef __UNION_H__
#define __UNION_H__

#include <cstdint>
#include <vector>

namespace ga
{

    template <typename T>
    class union_t
    {
    public:
        union_t();
        T find(T p);
        bool connected(T p, T q);
        void merge(T p, T q);
        int get_count() const;

    private:
        std::vector<T> parent_;
        std::vector<int> rank_;
        int count_;

        void resize(int n);
        void add_element();
    };

} // namespace ga

#endif // __UNION_H__
