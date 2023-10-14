#pragma once

#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <algorithm>
#include <ctime>

int string_to_int(const std::string& input);

std::vector<int> sort_vec(std::vector<int>& vec);

template <typename T> void container_is_sorted(T& container) {
    typename T::iterator it = container.begin();
    typename T::iterator it2 = container.begin();
    std::advance(it2, 1);

    while (it2 != container.end()) {
        if (*it > *it2)
            throw std::runtime_error("Error: Container is not sorted");
        it++;
        it2++;
    }
    std::cout << "Container is sorted!" << std::endl;
}

template <typename T> T parse(const std::string& input) {
    T container;
    std::stringstream ss(input);
    std::string part;

    while (std::getline(ss, part, ' ')) {
        if (!part.empty())
            container.push_back(string_to_int(part));
    }
    return (container);
}

template <typename T> void print_container(T& container) {
    for (typename T::iterator it = container.begin(); it != container.end();
         it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}
