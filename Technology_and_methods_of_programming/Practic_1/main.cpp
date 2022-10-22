#include <iostream>
#include <ctime>
#include <fstream>
#include "PtrBasedQueueAdapter.h"

using namespace std;

void Test_1() {
    PtrBasedQueueAdapter q;
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    q.Display();
    cout << endl;
    q.Pop();
    q.Display();
    cout << endl;
    q.Pop();
    q.Display();
    cout << endl;
    q.Pop();
    q.Display();
    q.Pop();
    cout << ":";
    q.Display();
    cout << ":";
    q.Push(1);
    cout << ":";
    q.Display();
    cout << ":";
    q.Pop();
    cout << ":";
    q.Display();
    cout << ":";
}

void Test_2() {
    PtrBasedQueueAdapter q;
    q.Push(1);
    q.Push(2);
    q.Push(3);
    cout << ":";
    q.Display();
    cout << ":";
    q.Pop();
    cout << ":";
    q.Display();
    cout << ":";
    q.Push(4);
    cout << ":";
    q.Display();
    cout << ":";
    q.Pop();
    cout << ":";
    q.Display();
    cout << ":";
}

void Test_3() {
    PtrBasedQueueAdapter q;

    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    q.Push(5);
    q.Display();
    //int& a = *(q.GetElementByIndex(4));
    //a = 454;
    q.Display();
    //a = 4544;
    q.Display();
}

void Test_4() {
    PtrBasedQueueAdapter q;

    q.Push(65);
    q.Push(3);
    q.Push(76);
    q.Push(87);
    q.Push(54);

    q.Display();

    cout << endl;

    //q.BubbleSort();

    q.Display();
}

void Test_5() {
    PtrBasedQueueAdapter q;

    q.Push(12);
    q.Push(11);
    q.Push(15);
    q.Push(10);
    q.Push(9);
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(13);
    q.Push(14);
    q.Push(0);
    q.Push(0);
    q.Push(0);
    q.Push(0);
    q.Push(4);
    q.Push(5);
    q.Push(6);
    q.Push(7);
    q.Push(8);
    q.Push(64);
    q.Push(43);
    q.Push(-11);
    q.Push(-65);
    cout << "Before sorting:" << endl;
    q.Display();

    //q.HeapSort();
    cout << "After sorting:" << endl;
    q.Display();
    cout << "Check for saving queue property:" << endl;
    cout << q.Front() << endl;
    q.Push(1);
    cout << q.Front() << endl;
    q.Display();
}

void CheckTimeForHeap(const string& unsorted_filename, const string& sorted_filename) {
    PtrBasedQueueAdapter q;

    ifstream ifs(unsorted_filename);

    while(!ifs.eof()) {
        int i;
        ifs >> i;
        q.Push(i);
    }
    cout << q.Size() << endl;
    auto start_time = clock();
    //q.Display();
    q.HeapSort();
    //q.Display();
    cout << float(clock() - start_time) / CLOCKS_PER_SEC << endl;

    ofstream ofs(sorted_filename);
    int size = q.Size();
    bool is_first = false;
    for (int i = 0; i < size; ++i) {
        if (is_first) {
            ofs << " ";
        }
        is_first = true;
        ofs << q.Front();
        q.Pop();
    }
}

void CheckTimeForBubble(int n) {
    PtrBasedQueueAdapter q;
    bool is_first = false;
    for (int i = 0; i < n; ++i) {
        q.Push(rand());
    }

    auto start_time = clock();
    //q.Display();
    q.BubbleSort();
    //q.Display();
    cout << float(clock() - start_time) / CLOCKS_PER_SEC << endl;
}

void Test_6() {
    PtrBasedQueueAdapter q;

    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    q.Push(5);
    q.Display();
    q[4] = q[1];
    q[1] = q[3];
    q[3] = q[2];
    q.Display();
    q.Pop();
    q.Pop();
    q.Display();
    //cout << *(q.GetElementByIndex(1)) << endl;
    //q.Display();
}

int main() {
    //Test_1();
    //Test_2();
    //Test_3();
    //Test_4();
    //Test_5();
    string unsorted_filename = "1.txt";
    string sorted_filename = "2.txt";

    int n = 300;
    for (int test = n; test <= 3000; test = test + 300) {
        ofstream ofs(unsorted_filename);
        bool is_first = false;
        for (int i = 0; i < test; ++i) {
            if (is_first) {
                ofs << " ";
            }
            is_first = true;
            ofs << rand();
        }
        ofs.close();
        CheckTimeForHeap(unsorted_filename, sorted_filename);
    }

    return 0;
}
