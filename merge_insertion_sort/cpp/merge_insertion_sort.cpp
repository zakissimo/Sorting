#include "merge_insertion_sort.hpp"
#include <deque>
#include <list>

int string_to_int(const std::string& str) {

    std::stringstream ss(str);
    int ret;
    if (!(ss >> ret) || ret < 0)
        throw std::runtime_error("Error: Invalid int format");
    return (ret);
}

static size_t get_next_jacobstahl_diff(size_t p, size_t n) { return n + 2 * p; }

int bs_vec(std::vector<int>& vec, int start, int end, const int& target) {

    while (start <= end) {

        int mid = (start + end) / 2;

        if (vec[mid] < target) {
            start = mid + 1;
        } else if (vec[mid] > target) {
            end = mid - 1;
        } else {
            return mid;
        }
    }
    return start;
}

std::vector<int> sort_vec(std::vector<int>& vec) {

    // Base case
    if (vec.size() == 1) {
        return vec;
    }

    // Getting max and pairs arrays
    std::vector<int> max;
    std::map<int, std::list<int> > max_to_min;
    for (size_t i = 0; i < vec.size() - 1; i += 2) {

        if (vec[i] > vec[i + 1]) {
            max_to_min[vec[i]].push_back(vec[i + 1]);
            max.push_back(vec[i]);
        } else {
            max_to_min[vec[i + 1]].push_back(vec[i]);
            max.push_back(vec[i + 1]);
        }
    }

    int leftover = -1;

    // If there is an odd number of elements, save the last one
    if (vec.size() > 1 && vec.size() % 2 == 1) {
        leftover = vec[vec.size() - 1];
    }

    // Sorting max array recursively
    vec = sort_vec(max);

    std::vector<int> S;
    // Pushing first pair in new vector and max of the rest
    int first_min = max_to_min[vec[0]].front();
    max_to_min[vec[0]].pop_front();
    S.push_back(first_min);
    for (size_t i = 0; i < vec.size(); i++) {
        S.push_back(vec[i]);
    }

    // Initialize jacobstahl sequence
    size_t p = 0;
    size_t n = 2;
    size_t tmp;

    // Extracting min of all pairs (except first one) in new vector
    // Grouping them in jacobstahl sequence
    // Use binary search to find the right position in new vector
    for (size_t i = 1; i < vec.size();) {
        for (size_t j = i + n - 1; j >= i; j--) {
            if (j < vec.size()) {
                int max_pos = bs_vec(S, j + 1, S.size(), vec[j]);
                int min = max_to_min[vec[j]].front();
                max_to_min[vec[j]].pop_front();
                int pos = bs_vec(S, 0, max_pos, min);
                S.insert(S.begin() + pos, min);
            }
        }
        i += n;
        if (n < vec.size()) {
            tmp = n;
            n = get_next_jacobstahl_diff(p, n);
            p = tmp;
        }
    }

    if (leftover != -1) {
        int idx = bs_vec(S, 0, S.size() - 1, leftover);
        S.insert(S.begin() + idx, leftover);
    }

    std::swap(S, vec);
    return vec;
}
