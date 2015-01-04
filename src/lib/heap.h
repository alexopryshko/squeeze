#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

template<class el>
class heap {
public:
    heap() {
        heapBuffer = new vector<el>();
    }
    heap(vector<el> *heapBuffer) {
        this->heapBuffer = heapBuffer;
        build();
    }
    ~heap() {
        delete heapBuffer;
    }

    void build();
    void add(el element);
    el extractMax();
    bool isEmpty() { return heapBuffer->empty(); }

private:
    void heapify(int i);

    vector<el> *heapBuffer = nullptr;
};


template<class el>
void heap<el>::heapify(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int largest = i;
    if (left < heapBuffer->size() && *heapBuffer->at(left) > *heapBuffer->at(i))
        largest = left;
    if (right < heapBuffer->size() && *heapBuffer->at(right) > *heapBuffer->at(largest))
        largest = right;

    if (largest != i) {
        auto iter = heapBuffer->begin();
        iter_swap(iter + i, iter + largest);
        heapify(largest);
    }
}

template<class el>
void heap<el>::build() {
    for (int i = heapBuffer->size() / 2 - 1; i >= 0; --i) {
        heapify(i);
    }
}

template<class el>
void heap<el>::add(el element) {
    heapBuffer->push_back(element);
    int i = heapBuffer->size() - 1;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (*heapBuffer->at(i) < *heapBuffer->at(parent)) {
            return;
        }
        auto iter = heapBuffer->begin();
        iter_swap(iter + i, iter + parent);
        i = parent;
    }
}

template<class el>
el heap<el>::extractMax() {
    if (heapBuffer->empty()) {
        throw;
    }
    el result = heapBuffer->at(0);
    auto iter = heapBuffer->begin();
    *iter = heapBuffer->at(heapBuffer->size() - 1);
    heapBuffer->pop_back();
    if (!heapBuffer->empty()) {
        heapify(0);
    }
    return result;
}