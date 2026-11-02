#include "project/heap.h"

#include <algorithm>
#include <stdexcept>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(const std::vector<int>& values) {
    buildHeap(values);
}

bool MaxHeap::empty() const noexcept {
    return data_.empty();
}

std::size_t MaxHeap::size() const noexcept {
    return data_.size();
}

int MaxHeap::top() const {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    return data_.front();
}

bool MaxHeap::contains(int value) const {
    for (int item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

void MaxHeap::push(int value) {
    data_.push_back(value);
    heapifyUp(data_.size() - 1);
}

int MaxHeap::pop() {
    if (empty()) 
        throw std::logic_error("heap empty");
    int maxVal = data_.front();
    data_.front() = data_.back();
    data_.pop_back();

    if(!empty())
        heapifyDown(0);
    return maxVal;
}

void MaxHeap::buildHeap(const std::vector<int>& values) {
    data_ = values;
    if(data_.empty())
        return;
    std::size_t lastNonLeaf = parentIndex(data_.size() - 1);
    for (int i = static_cast<int>(lastNonLeaf); i>=0; i--)
        heapifyDown(static_cast<std::size_t>(i));
}

std::vector<int> MaxHeap::heapSort() {
    if (empty())
        return{};
    std::vector<int> sorted = data_;
    std::size_t n = sorted.size();

 
    auto siftDown = [](std::vector<int>& arr, std::size_t heapSize, std::size_t i) {
        while (true) {
            std::size_t largest = i;
            std::size_t left = (2 * i) + 1;
            std::size_t right = (2 * i) + 2;

            if (left < heapSize && arr[left] > arr[largest]) {
                largest = left;
            }
            if (right < heapSize && arr[right] > arr[largest]) {
                largest = right;
            }
            if (largest == i) {
                break;
            }
            std::swap(arr[i], arr[largest]);
            i = largest;
        }
    };
    for (int i = static_cast<int> (n/2) - 1; i>=0; i--)
        siftDown(sorted, n, static_cast<std::size_t>(i));
    for (std::size_t i = n - 1; i > 0; --i) {
        std::swap(sorted[0], sorted[i]);
        siftDown(sorted, i, 0);
    }
    return sorted;
}

std::vector<int> MaxHeap::toVector() const {
    return data_;
}

std::size_t MaxHeap::parentIndex(std::size_t index) {
    if (index == 0) {
        return 0;
    }
    return (index - 1) / 2;
}

std::size_t MaxHeap::leftChildIndex(std::size_t index) {
    return (2 * index) + 1;
}

std::size_t MaxHeap::rightChildIndex(std::size_t index) {
    return (2 * index) + 2;
}

void MaxHeap::heapifyUp(std::size_t index) {
    while (index > 0) {
        std::size_t pIndex = parentIndex(index);
        if (data_[index] > data_[pIndex]) {
            std::swap(data_[index], data_[pIndex]);
            index = pIndex;
        } else {
            break;
        }
    }
}

void MaxHeap::heapifyDown(std::size_t index) {
    std::size_t size = data_.size();
    while (true) {
        std::size_t largest = index;
        std::size_t left = leftChildIndex(index);
        std::size_t right = rightChildIndex(index);

        if (left < size && data_[left] > data_[largest]) {
            largest = left;
        }
        if (right < size && data_[right] > data_[largest]) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        std::swap(data_[index], data_[largest]);
        index = largest;
    }
}

void MaxHeap::swap(int& a, int& b) {
    std::swap(a, b);
}

bool MaxHeap::isValidHeap() const {
    for (std::size_t i = 1; i < data_.size(); ++i) {
        if (data_[parentIndex(i)] < data_[i]) {
            return false;
        }
    }
    return true;
}
