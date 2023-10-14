#include "merge_insertion_sort.hpp"

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

int find_max_in_pairs(std::vector<std::pair<int, int> >& pairs, int start, int end,
             const int& target) {

    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first == target) {
            return i;
        }
    }
    throw std::runtime_error("Error: bs_pairs didn't find target max");
}

std::vector<int> sort_vec(std::vector<int>& vec) {

    // Base case
    if (vec.size() == 1) {
        return vec;
    }

    // Getting max and pairs arrays
    std::vector<int> max;
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < vec.size() - 1; i += 2) {

        if (vec[i] > vec[i + 1]) {
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
            max.push_back(vec[i]);
        } else {
            pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
            max.push_back(vec[i + 1]);
        }
    }

    int* leftover = NULL;

    // If there is an odd number of elements, save the last one
    if (vec.size() % 2 == 1) {
        leftover = &vec[vec.size() - 1];
    }

    // Sorting max array recursively
    vec = sort_vec(max);

    std::vector<int> S = vec;
    // Pushing first pair in new vector and max of the rest
    size_t min_pos = find_max_in_pairs(pairs, 0, pairs.size() - 1, vec[0]);
    S.insert(S.begin(), pairs[min_pos].second);
    pairs.erase(pairs.begin() + min_pos);

    // Initialize jacobstahl sequence
    size_t p = 0;
    size_t n = 2;
    size_t tmp, min, max_pos;

    // Extracting min of all pairs (except first one) in new vector
    // Grouping them in jacobstahl sequence
    // Use binary search to find the right position in new vector
    for (size_t i = 1; i < vec.size();) {
        for (size_t j = i + n - 1; j >= i; j--) {
            if (j >= vec.size())
                continue;
            min_pos = find_max_in_pairs(pairs, 0, pairs.size() - 1, vec[j]);
            min = pairs[min_pos].second;
            max_pos = bs_vec(S, 0, bs_vec(S, j + 1, S.size(), vec[j]), min);
            S.insert(S.begin() + max_pos, min);
            pairs.erase(pairs.begin() + min_pos);
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
