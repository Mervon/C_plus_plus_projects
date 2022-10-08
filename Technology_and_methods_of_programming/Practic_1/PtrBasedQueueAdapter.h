#pragma once

#include "PtrBasedQueue.h"

using namespace std;

class PtrBasedQueueAdapter {
public:
    PtrBasedQueueAdapter() : self_(*this) {
        queue_ = new PtrBasedQueue;
    }

    void Display() {
        queue_->Display();
    }

    void Push(int value) {
        queue_->Push(value);
    }

    void Pop() {
        queue_->Pop();
    }

    size_t Size() {
        return queue_->Size();
    }

    int Front() {
        return queue_->Front();
    }

    int& GetElementByIndex(int index) {
        return queue_->GetElementByIndex(index);
    }

    int& operator[](int index) {
        return GetElementByIndex(index);
    }

    void BubbleSort() { // O(n^2)
        for (int i = 0; i < Size(); ++i) {
            for (int j = 0; j < Size() - 1; ++j) {
                if (self_[j] > self_[j + 1]) {
                    int a = self_[j];
                    swap(self_[j], self_[j + 1]);
                    self_[j + 1] = a;
                }
            }
        }
    }

    /*
     * Heap sorting - first of we need to make heap from source queue
     * that can be done within O(N) operations,
     * and then we need to swap first element with last, and make heap
     * again on the data[0,size-1], that can be done within O(log(N))
     * operations. The total operation count is O(N + (N * log(N))) =
     * O(N * log(N))
     */

    void HeapSort() { // O(N*log(N))
        int n = Size();

        for (int i = n / 2 - 1; i >= 0; --i) {
            Heapify(n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            swap(self_[0], self_[i]);
            Heapify(i, 0);
        }
    }

private:
    void Heapify(int end, int start) {
        int largest = start;
        int left = start * 2 + 1;
        int right = start * 2 + 2;

        if (left < end && self_[left] > self_[largest]) {
            largest = left;
        }
        if (right < end && self_[right] > self_[largest]) {
            largest = right;
        }
        if (largest != start) {
            swap(self_[largest], self_[start]);
            Heapify(end, largest);
        }
    }

    PtrBasedQueue* queue_;
    PtrBasedQueueAdapter& self_;
};