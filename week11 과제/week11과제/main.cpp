#include "yuhan_stack.h"
#include <iostream>

int main() {
    Stack<int> myStack;

    int numElements;
    std::cout << "������ ���� �Է� : ";
    std::cin >> numElements;

    for (int i = 1; i <= numElements; ++i) {
        int value;
        std::cout << "���� " << i << "��°�� ��: ";
        std::cin >> value;
        myStack.push(value);
    }

    std::cout << "Popping elements from the stack:" << std::endl;

    while (!myStack.isEmpty()) {
        std::cout << "Pop: " << myStack.pop() << std::endl;
    }

    return 0;
}