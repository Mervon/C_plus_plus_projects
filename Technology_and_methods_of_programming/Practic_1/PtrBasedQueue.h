#pragma once

using namespace std;

class PtrBasedQueue {
    struct Node; //forward declaration
public:
    PtrBasedQueue() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    void Push(int value) {
        Node *new_node = new Node();
        new_node->value_ = value;
        if (size_ == 0) {
            new_node->next_ = nullptr;
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next_ = new_node;
            tail_ = new_node;
        }

        size_++;
    }

    void Pop() {
        Node *node_to_pop = head_;

        head_ = head_->next_;

        delete node_to_pop;

        size_--;
    }

    size_t Size() {
        return size_;
    }

    void Display() {
        Node *head = head_;

        bool is_first = false;

        for (int i = 0; i < size_; i++) {
            if (is_first) {
                cout << " ";
            }
            is_first = true;
            cout << head->value_;
            head = head->next_;
        }
        cout << endl;
    }

    int Front() {
        return head_->value_;
    }

    int& GetElementByIndex(int index) {
        if (index >= 0 && index < size_) {
            Node* head = head_;
            for (int i = 0; i < index + 1; ++i) {
                if (i == index) {
                    return head->value_;
                }
                head = head->next_;
            }
        } else {
            throw std::out_of_range("Index out of range!");
        }
    }

private:
    struct Node {
        int value_;
        Node *next_;
    };
    size_t size_;
    Node *head_;
    Node *tail_;
};