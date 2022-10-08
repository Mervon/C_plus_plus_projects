#pragma once

using namespace std;

class PtrBasedQueue {
    struct Node; //forward declaration
public:
    PtrBasedQueue() { // 1 + 1 + 1 = 3
        head_ = nullptr; // 1
        tail_ = nullptr; // 1
        size_ = 0; // 1
    }

    void Push(int value) { // 3 + 2 + 4 + 1 = 10
        Node* new_node = new Node(); // 1 + 1 + 1 = 3
        new_node->value_ = value; // 1 + 1 = 2
        if (size_ == 0) { // 2 + 1 + 1 = 4; max(4, 3) = 4
            new_node->next_ = nullptr; // 1 + 1 = 2
            head_ = new_node; // 1
            tail_ = new_node; // 1
        } else { // 2 + 1 = 3
            tail_->next_ = new_node; // 1 + 1 = 2
            tail_ = new_node; // 1
        }

        size_++; // 1
    }

    void Pop() { // 2 + 2 + 1 + 1 = 6
        Node* node_to_pop = head_; // 1 + 1 = 2

        head_ = head_->next_; // 1 + 1 = 2

        delete node_to_pop; // 1

        size_--; // 1
    }

    size_t Size() { // 1
        return size_; // 1
    }

    int& Front() { // 2
        return head_->value_; // 1 + 1 = 2
    }

    int& Back() { // 2
        return tail_->value_; // 1 + 1 = 2
    }

private:
    struct Node {
        int value_;
        Node* next_;
    };
    size_t size_;
    Node* head_;
    Node* tail_;
};