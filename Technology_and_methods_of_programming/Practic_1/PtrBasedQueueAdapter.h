#pragma once

#include "PtrBasedQueue.h"

using namespace std;

class PtrBasedQueueAdapter {
public:
    void Display() {
        bool is_first = false;

        for (int i = 0; i < Size(); ++i) {

            if (is_first) {
                cout << " ";
            }

            is_first = true;

            cout << Front();
            Push(Front());
            Pop();
        }

        cout << endl;
    }

    PtrBasedQueueAdapter() : self_(*this) { // 4
        queue_ = new PtrBasedQueue; // 1 + 3 = 4
    }

    ~PtrBasedQueueAdapter() { // 1
        delete queue_; // 1
    }

    void Push(int value) { // 11
        queue_->Push(value); // 1 + 10 = 11
    }

    void Pop() { // 7
        queue_->Pop(); // 1 + 6 = 7
    }

    size_t Size() { // 2
        return queue_->Size(); // 1 + 1 = 2
    }

    int& Front() { // 3
        return queue_->Front(); // 1 + 2 = 3
    }

    int& Back() { // 3
        return queue_->Back(); // 1 + 2 = 3
    }

    int* GetElementByIndex(int index) { // 4 + 1 + 5 + 3 + index * (15 + 7) + 22 + (N - index - 1) * (15 + 7) =
        // = 22 * N + 13
        if (index >= 0 && index < Size()) { // 1 + 1 + 2 = 4
            int* result; // 1


            PtrBasedQueue* tmp_q = new PtrBasedQueue(); // 1 + 1 + 3 = 5
            int size = Size(); // 1 + 2 = 3

            for (int i = 0; i < index; ++i) { // index * (15 + 7)
                tmp_q->Push(Front()); // 1 + 11 + 3 = 15
                Pop(); // 7
            }

            tmp_q->Push(Front()); // 1 + 11 + 3 = 15
            Pop(); // 7

            result = &(tmp_q->Back()); // 1 + 1 + 1 + 2 = 5

            for (int i = index + 1; i < size; ++i) { // (N - index - 1) * (15 + 7)
                tmp_q->Push(Front()); // 1 + 11 + 3 = 15
                Pop(); // 7
            }

            queue_ = tmp_q; // 1

            return result; // 1
        } else { // 1
            throw std::out_of_range("Index out of range!"); // 1
        }
    }

    int& operator[](int index) { // 22 * N + 14
        return *(GetElementByIndex(index)); // 1 + 22 * N + 13 = 22 * N + 14
    }

    void BubbleSort() { // O(n^2)
        for (int i = 0; i < Size(); ++i) {
            for (int j = 0; j < Size() - 1; ++j) {
                if (self_[j] > self_[j + 1]) {
                    int a = self_[j];
                    self_[j] = self_[j + 1];
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
        int n = Size(); // 1 + 2 = 3

        for (int i = n / 2 - 1; i >= 0; --i) { // N / 2 * log2(N) * (176 * N + 133)
            Heapify(n, i); // log2(N) * (176 * N + 133)
        }

        for (int i = n - 1; i > 0; i--) { // (N - 1) *
            int a = self_[0]; // 1 + 22 * N + 14 = 22 * N + 15
            self_[0] = self_[i]; // 1 + 22 * N + 14 + 22 * N + 14 = 44 * N + 29
            self_[i] = a; // 1 + 22 * N + 14 = 22 * N + 15
            Heapify(i, 0);
        }
    }

private:
    void Heapify(int end, int start) { // 2 + 4 + 4 + 44 * N + 32 + 44 * N + 32 + 22 * N + 15 + 44 * N + 29 + 22 * N + 15 = 176 * N + 133
        int largest = start; // 1 + 1 = 2
        int left = start * 2 + 1; // 1 + 1 + 1 + 1 = 4
        int right = start * 2 + 2; // 1 + 1 + 1 + 1 = 4

        if (left < end && self_[left] > self_[largest]) { // 1 + 22 * N + 14 + 1 + 22 * N + 14 + 1 + 1 = 44 * N + 32
            largest = left; // 1
        }
        if (right < end && self_[right] > self_[largest]) { // 1 + 22 * N + 14 + 1 + 22 * N + 14 + 1 + 1 = 44 * N + 32
            largest = right; // 1
        }
        if (largest == start) {
            return;
        }

        int a = self_[largest]; // 1 + 22 * N + 14 = 22 * N + 15
        self_[largest] = self_[start]; // 1 + 22 * N + 14 + 22 * N + 14 = 44 * N + 29
        self_[start] = a; // 1 + 22 * N + 14 = 22 * N + 15
        Heapify(end, largest); //-> выполняется в худшем случае log2(N) раз, иными словами это цикл с log2(N) итераций
        // log2(N) * 176 * N + 133
    }

    PtrBasedQueue* queue_;
    PtrBasedQueueAdapter& self_;
};