#ifndef BINSEARCH_H
#define BINSEARCH_H

#include <vector>

template <typename T>
int binSearch(const std::vector<T>& vec, const T& target) {
    int left = 0;
    int right = static_cast<int>(vec.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (vec[mid] == target) {
            return mid;
        }

        if (vec[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

#endif