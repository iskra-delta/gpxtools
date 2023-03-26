/*
 * union.cpp
 * 
 * Union class (for union find function)
 * implementation.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 26.03.2023  tstih
 * 
 */

#include <ga/union.h>

namespace ga
{
    template <typename T>
    union_t<T>::union_t() : count_(0) {}

    template <typename T>
    T union_t<T>::find(T p)
    {
        while (p != parent_[p])
        {
            parent_[p] = parent_[parent_[p]];
            p = parent_[p];
        }
        T root = p;
        p = parent_[p];
        while (p != root)
        {
            parent_[p] = root;
            p = parent_[p];
        }
        return root;
    }

    template <typename T>
    bool union_t<T>::connected(T p, T q) { return find(p) == find(q); }

    template <typename T>
    void union_t<T>::merge(T p, T q)
    {
        if (parent_.empty())
        {
            add_element();
        }
        if (p >= parent_.size())
        {
            resize(p + 1);
        }
        if (q >= parent_.size())
        {
            resize(q + 1);
        }
        int root_p = find(p);
        int root_q = find(q);
        if (root_p == root_q)
        {
            return;
        }
        if (root_p > root_q)
        {
            std::swap(root_p, root_q);
        }
        if (rank_[root_p] < rank_[root_q])
        {
            parent_[root_p] = root_q;
        }
        else if (rank_[root_p] > rank_[root_q])
        {
            parent_[root_q] = root_p;
        }
        else
        {
            parent_[root_q] = root_p;
            rank_[root_p]++;
        }
        count_--;
    }

    template <typename T>
    int union_t<T>::get_count() const { return count_; }

    template <typename T>
    void union_t<T>::resize(int n)
    {
        int old_size = parent_.size();
        parent_.resize(n);
        rank_.resize(n, 0);
        count_ += n - old_size;
        for (int i = old_size; i < n; i++)
            parent_[i] = i;
    }

    template <typename T>
    void union_t<T>::add_element() { resize(1); }

    // Implementation(s)
    template class union_t<uint8_t>;
    template class union_t<char>;
    template class union_t<int>;

} // namespace ga