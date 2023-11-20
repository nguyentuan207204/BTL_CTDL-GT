#ifndef __DOUBLELINKLIST_CPP__
#define __DOUBLELINKLIST_CPP__

#include <iostream>

template <class T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;
};

template <class T>
class DoubleLinkList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoubleLinkList() {
        head = nullptr;
        tail = nullptr;
    }

    Node<T>* makeNode(T x) {
        Node<T>* newNode = new Node<T>;
        newNode->data = x;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        return newNode;
    }


    void InsertNodeFirst(T x) {
        Node<T>* newNode = makeNode(x);
        newNode->next = head;
        if (head != nullptr)
            head->prev = newNode;
        head = newNode;
        if (tail == nullptr)
            tail = newNode;
    }

    void InsertNodeEnd(T x) {
        Node<T>* newNode = makeNode(x);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    int size() {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void themgiua(T x, int k) {
        int n = size();
        if (k < 1 || k > n + 1)
            return;
        if (k == 1) {
            InsertNodeFirst(x);
            return;
        }
        Node<T>* temp = head;
        for (int i = 1; i < k - 1; i++) {
            temp = temp->next;
        }
        Node<T>* newNode = makeNode(x);
        newNode->next = temp;
        temp->prev->next = newNode;
        newNode->prev = temp->prev;
        temp->prev = newNode;
    }
    Node<T>* getHead(){
      return head;
    }
     void setHead(Node<T>* newHead) {
        head = newHead;
    }
    Node<T>* getTail(){
       return tail;
    }
    void duyetXuoi(){
       Node<T>* current=head;
       while(current!=nullptr){
          std::cout<<current->data<<" ";
          current=current->next;
       }
        std::cout<<std::endl;
    }
    void duyetNguoc(){
        Node<T>* current=tail;
        while(current!=nullptr){
            std::cout<<current->data<<" ";
            current=current->prev;
        }
        std::cout<<std::endl;

    }

    ~DoubleLinkList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}
};

#endif // __DOUBLELINKLIST_H__
