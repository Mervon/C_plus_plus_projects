#include <iostream>
#include <vector>
#include "PtrBasedQueueAdapter.h"

using namespace std;

void Test_1() {
    PtrBasedQueue q;
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
    int& a = q.GetElementByIndex(4);
    a = 454;
    q.Display();
    a = 4544;
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

    q.BubbleSort();

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

    q.HeapSort();
    cout << "After sorting:" << endl;
    q.Display();
    cout << "Check for saving queue property:" << endl;
    cout << q.Front() << endl;
    q.Push(1);
    cout << q.Front() << endl;
    q.Display();
}

int main() {
    //Test_1();
    //Test_2();
    //Test_3();
    //Test_4();
    Test_5();
    return 0;
}
