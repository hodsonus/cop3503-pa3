#ifndef PA3
#define PA3

#include <iostream>
#include <string>

class Node {

  private:
    std::string data;
    Node* next;
    Node* prev;

  public:
    Node(std::string data, Node* next, Node* prev);
    Node* getNext();
    Node* getPrev();
    std::string getData();
    void setData(std::string toSet);
    void setNext(Node* next);
    void setPrev(Node* prev);
};

class LinkedList {

  private:
    Node* head;
    Node* tail;

  public:
    bool remove(std::string toRemove);
    void insert(std::string toInsert);
    void traverse();
    Node* search(std::string toFind);
    Node* getHead();
    Node* getTail();
};

class Stack {

  private:
    LinkedList* list;

  public:
    void push(std::string data);
    std::string pop();
};

class pa3 {

  private:
    Stack myStack;

  public:


};

#endif
