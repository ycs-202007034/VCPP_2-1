// stack.h ��� ����

#pragma once
#include <stdexcept>

template <typename T>
class Stack {
private:
    // ��� Ŭ���� ����
    class Node {
    public:
        T data;
        Node* prev_node;
        Node(const T& data, Node* prev_node) : data(data), prev_node(prev_node) {}
    };

    Node* top; // ������ �� ���� ����Ű�� ������

public:
    // ������
    Stack() : top(nullptr) {}

    // �Ҹ���
    ~Stack();

    // push �Լ� ����
    void push(const T& data);

    // pop �Լ� ����
    T pop();

    // top �Լ� ����
    T topValue() const;

    // isEmpty �Լ� ����
    bool isEmpty() const;
};

// ���ø� ��� �Լ����� ���Ǹ� ���⿡ �߰�
template <typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::push(const T& data) {
    top = new Node(data, top);
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        // ������ ������� ���� ó��
        throw std::runtime_error("pop() ȣ�� �� ������ ����ֽ��ϴ�.");
    }

    T data = top->data;
    Node* tmp = top;
    top = top->prev_node;
    delete tmp;
    return data;
}

template <typename T>
T Stack<T>::topValue() const {
    if (isEmpty()) {
        // ������ ������� ���� ó��
        throw std::runtime_error("topValue() ȣ�� �� ������ ����ֽ��ϴ�.");
    }

    return top->data;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}