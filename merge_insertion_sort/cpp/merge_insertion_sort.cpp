#include "merge_insertion_sort.hpp"
#include <unordered_map>

int string_to_int(const std::string& str) {

    std::stringstream ss(str);
    int ret;
    if (!(ss >> ret) || ret < 0)
        throw std::runtime_error("Error: Invalid int format");
    return (ret);
}

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
    std::vector<int> maxs;
    std::unordered_map<int, int> max_to_min;

    for (size_t i = 0; i < vec.size() - 1; i += 2) {

        const int *max = &std::max(vec[i], vec[i + 1]);
        const int *min = &std::min(vec[i], vec[i + 1]);

        max_to_min[*max] = *min;
        maxs.push_back(*max);

    }

    int* leftover = NULL;

    // If there is an odd number of elements, save the last one
    if (vec.size() % 2 == 1) {
        leftover = &vec[vec.size() - 1];
    }

    // Sorting max array recursively
    vec = sort_vec(maxs);

    std::vector<int> S = vec;
    // Pushing first pair in new vector and max of the rest
    S.insert(S.begin(), max_to_min[S[0]]);

    // Initialize jacobstahl sequence
    size_t p = 0;
    size_t n = 2;
    size_t tmp;

    // Extracting min of all pairs (except first one) in new vector
    // Grouping them in jacobstahl sequence
    // Use binary search to find the right position in new vector
    for (size_t i = 1; i < vec.size();) {
        for (size_t j = i + n - 1; j >= i; j--) {
            if (j >= vec.size())
                continue;
            S.insert(S.begin() + bs_vec(S, 0, bs_vec(S, j + 1, S.size(), vec[j]), max_to_min[vec[j]]), max_to_min[vec[j]]);
        }
        i += n;
        tmp = n;
        n = n + 2 * p;
        p = tmp;
    }

    if (leftover) {
        S.insert(S.begin() + bs_vec(S, 0, S.size() - 1, *leftover), *leftover);
    }

    return S;
}
