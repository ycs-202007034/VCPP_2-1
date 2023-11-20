// stack.h 헤더 파일

#pragma once
#include <stdexcept>

template <typename T>
class Stack {
private:
    // 노드 클래스 정의
    class Node {
    public:
        T data;
        Node* prev_node;
        Node(const T& data, Node* prev_node) : data(data), prev_node(prev_node) {}
    };

    Node* top; // 스택의 맨 위를 가리키는 포인터

public:
    // 생성자
    Stack() : top(nullptr) {}

    // 소멸자
    ~Stack();

    // push 함수 선언
    void push(const T& data);

    // pop 함수 선언
    T pop();

    // top 함수 선언
    T topValue() const;

    // isEmpty 함수 선언
    bool isEmpty() const;
};

// 템플릿 멤버 함수들의 정의를 여기에 추가
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
        // 스택이 비어있을 때의 처리
        throw std::runtime_error("pop() 호출 시 스택이 비어있습니다.");
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
        // 스택이 비어있을 때의 처리
        throw std::runtime_error("topValue() 호출 시 스택이 비어있습니다.");
    }

    return top->data;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}