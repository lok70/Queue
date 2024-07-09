#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <exception>
#include <algorithm>

template<class T, class Container = std::vector<T>, class Compare = std::greater<typename Container::value_type>>
class priority_queue
{
	Container data;
	Compare cmp;

	using size_type = typename Container::size_type;
	using value_type = T;
public:

	priority_queue()
	{}

	template <class FwdIt>
	priority_queue(FwdIt first, FwdIt last)
	{
		while (first != last)
			push(*first++);
	}

	priority_queue(std::initializer_list<T> values)
	{
		for (const T& x : values)
			push(x);
	}

	priority_queue(const priority_queue& other)
	{
		data = other.data;
		cmp = other.cmp;
	}

	priority_queue& operator=(const priority_queue& other)
	{
		data = other.data;
		cmp = other.cmp;
	}

	size_type size() const
	{
		return data.size();
	}

	void push(const T& x)
	{
		auto it = std::upper_bound(data.begin(), data.end(), x, cmp);
		data.insert(it, x);
	}

	void pop()
	{
		if (size() == 0)
			throw std::exception("pop on empty priority_queue");

		data.pop_back();
	}

	const T& top() const
	{
		if (size() == 0)
			throw std::exception("top on empty priority_queue");

		return data[size() - 1];
	}

	bool empty() const
	{
		return size() == 0;
	}

	priority_queue& operator+=(const priority_queue& other)
	{
		data.reserve(size() + other.size());
		std::copy(other.data.cbegin(), other.data.cend(), std::back_inserter(data));
		std::sort(data.begin(), data.end());

		return *this;
	}

	friend priority_queue operator+(const priority_queue& pq1, const priority_queue& pq2)
	{
		priority_queue t = pq1;
		t += pq2;
		return t;
	}

	friend std::ostream& operator<<(std::ostream& os, const priority_queue& pq)
	{
		for (const T& x : pq.data)
			os << x << " ";

		return os;
	}
};