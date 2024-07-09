#include <chrono>
#include <queue>
#include <fstream>
#include "priority_queue.h"
#include "heap_priority_queue.h"
#include <random>
#include <set>

using namespace std::chrono;

template <class T>
struct length
{
    bool operator()(const T& a, const T& b) const
    {
        return a.size() < b.size();
    }
};

std::string trim(const std::string& s)
{
    std::string r;
    for (char c : s)
        if ((!ispunct(c) || c == '-') && c != '»' && c != '…')
            r += c;
    return r;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    {
        std::vector<int> v;
        v.reserve(1000);
        std::generate_n(back_inserter(v), 10, rand);
        heap_priority_queue<int, std::vector<int>, std::greater<int>> h(v.begin(), v.end());
        h.print();
    }

    high_resolution_clock::time_point t1, t2;
    size_t N = 10000000;

    std::priority_queue<int> std_priotity_queue;

    heap_priority_queue<int> my_heap_priority_queue;

    priority_queue<int> queue;


    std::cout << "Добавление элемента:" << std::endl;
    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < N; i++)
        std_priotity_queue.push(rand());
    t2 = high_resolution_clock::now();
    std::cout << "std::priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        my_heap_priority_queue.push(rand());
    }

    t2 = high_resolution_clock::now();
    std::cout << "heap_priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;
    std::cout << std::endl;

    /*t1 = high_resolution_clock::now();
    for (size_t i = 0; i < N; i++)
        queue.push(rand());
    t2 = high_resolution_clock::now();
    std::cout << "priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;*/

    std::cout << "Извлечение максимального" << std::endl;
    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < N; i++)
        std_priotity_queue.pop();
    t2 = high_resolution_clock::now();
    std::cout << "std::priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;

 
    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < N; i++)
        my_heap_priority_queue.pop();
    t2 = high_resolution_clock::now();
    std::cout << "heap_priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;
    std::cout << std::endl;

    std::cout << "Создание из массива элементов" << std::endl;
    std::vector<int> v;
    for (size_t i = 0; i < N; i++)
        v.push_back(i);


    t1 = high_resolution_clock::now();
    std::priority_queue<int> a2(v.begin(), v.end());
    t2 = high_resolution_clock::now();
    std::cout << "std::priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;


    t1 = high_resolution_clock::now();
    heap_priority_queue<int> h2(v.begin(), v.end());
    t2 = high_resolution_clock::now();
    std::cout << "heap_priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;
    std::cout << std::endl;

    std::cout << "Слияние двух очередей с приоритетами" << std::endl;
    std::priority_queue<int> a3 = a2;
    t1 = high_resolution_clock::now();
    while (!a2.empty())
    {
        a3.push(a2.top());
        a2.pop();
    }
    t2 = high_resolution_clock::now();
    std::cout << "std::priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;


    heap_priority_queue<int> h3 = h2;
    t1 = high_resolution_clock::now();
    h3 += h2;
    t2 = high_resolution_clock::now();
    std::cout << "heap_priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;
    std::cout << std::endl;
    std::cout << "20 самых длинных слов" << std::endl;

    using T = std::string;
    using Con = std::vector<T>;
    using Cmp = length<T>;


    std::set<T> s1;
    std::priority_queue<T, Con, Cmp> p1;
    heap_priority_queue<T, Con, Cmp> h1;

    std::ifstream ifs("Мастер и Маргарита.txt");
    std::string word;
    while (ifs >> word) {
        s1.insert(trim(word));
    }
    t1 = high_resolution_clock::now();
    for (const auto& w : s1) {
        p1.push(trim(w));
    }

    for (size_t i = 0; i < 20 && !p1.empty(); i++) {
        std::cout << p1.top() << std::endl;
        p1.pop();
    }

    std::cout << std::endl;
    t2 = high_resolution_clock::now();
    std::cout << "std::priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;
    std::cout << std::endl;

    ifs.close();
   ifs.open("Мастер и Маргарита.txt");

    t1 = high_resolution_clock::now();
    for (const auto& w : s1) {
        h1.push(trim(w));
    }

    for (size_t i = 0; i < 20 && !h1.empty(); i++) {
        std::cout << h1.top() << std::endl;
        h1.pop();
    }

    std::cout << std::endl;
    t2 = high_resolution_clock::now();
    std::cout << "heap_priority_queue: " << duration_cast<milliseconds>(t2 - t1).count() << " милисекунд" << std::endl;
    std::cout << std::endl;
}