// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>

struct SYM {
    char ch;
    int prior;
};

template <typename T>
class TPQueue {
 private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& data, Node* next = nullptr)
            : data(data), next(next) {}
    };
    Node* head;
    Node* tail;
    size_t size;

 public:
    TPQueue() : head(nullptr), tail(nullptr), size(0) {}
    ~TPQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void push(const T& item) {
        Node* newNode = new Node(item);
        if (!head || item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            if (!tail) tail = head;
            size++;
            return;
        }
        Node* current = head;
        while (current->next && current->next->data.prior >= item.prior) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) {
            tail = newNode;
        }
        size++;
    }
    T pop() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
        delete temp;
        size--;
        return data;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data.ch << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    size_t getSize() const {
        return size;
    }
    bool isEmpty() const {
        return size == 0;
    }
};

#endif  // INCLUDE_TPQUEUE_H_
