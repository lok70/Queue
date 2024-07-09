#pragma once
#include <vector>
#include<iostream>

template <
    class T,
    class Container = std::vector<T>,
    class Comparator = std::less<typename Container::value_type>>
    class heap_priority_queue
{
private:
    Container body;
    Comparator comp;

    size_t _parent(size_t i) const
    {
        return (i - 1) / 2;
    }

    size_t _left(size_t i) { return 2 * i + 1; }

    size_t _right(size_t i) { return 2 * (i + 1); }

    bool greater(const T& first, const T& second) { return !comp(first, second); }

    bool exists(size_t i) { return i < size(); }


    void heapify(size_t i) {
        size_t i_max = i;
        size_t left = _left(i);
        if (exists(left) && greater(body[left], body[i_max]))
        {
            i_max = left;
        }
        size_t right = _right(i);
        if (exists(right) && greater(body[right], body[i_max]))
        {
            i_max = right;
        }
        if (i_max != i)
        {
            std::swap(body[i], body[i_max]);
            heapify(i_max);
        }
    }


    void _print(size_t index, size_t padding)
    {
        size_t right = _right(index);
        size_t left = _left(index);
        if (exists(right))
            _print(right, padding + 1);
        for (size_t i = 0; i < padding; ++i)
            std::cout << "    ";
        std::cout << body[index] << std::endl;
        if (exists(left))
            _print(left, padding + 1);
    }

public:
    heap_priority_queue() {
        body = Container();
        comp = Comparator();
    }

    template <class FwdIt>
    heap_priority_queue(FwdIt first, FwdIt last)
    {
        while (first != last)
            push(*first++);
    }
    heap_priority_queue(std::initializer_list<T> values)
    {
        for (const T& i : values)
            push(i);
    }
    heap_priority_queue(const heap_priority_queue& other)
    {
        body = other.body;
        comp = other.comp;
    }
    heap_priority_queue& operator=(const heap_priority_queue& other)
    {
        body = other.body;
        comp = other.comp;
    }

    size_t size() const { return body.size(); }

    bool empty() const { return size() == 0; }

    const T& top() const { return body[0]; }
 
    void push(const T& x)
    {
        body.push_back(x);
        size_t i = size() - 1;
        size_t parent = _parent(i);
        while (i > 0 && greater(body[i], body[parent]))
        {
            std::swap(body[i], body[parent]);
            i = parent;
            parent = _parent(i);
        }
    }
    void pop()
    {
        if (size() > 0)
        {
            body[0] = body[size() - 1];
            body.pop_back();
            heapify(0);
        }
    }

    void print() {
        _print(0, 0);
    }


    friend heap_priority_queue merge(heap_priority_queue first, heap_priority_queue second)
    {
        size_t size = second.size();
        for (size_t i = 0; i < size; ++i)
        {
            first.push(second.body[i]);
        }
        return first;
    }

    friend std::ostream& operator<<(std::ostream& out, const heap_priority_queue& heap)
    {
        size_t size = heap.size();
        for (size_t i = 0; i < size; ++i)
        {
            out << heap.body[i] << " ";
        }
        return out;
    }
    heap_priority_queue& operator+=(const heap_priority_queue& other)
    {
        size_t other_size = other.size();
        for (size_t i = 0; i < other_size; ++i)
        {
            push(other.body[i]);
        }
        return *this;
    }

};
