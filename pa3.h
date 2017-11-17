#ifndef PA3
#define PA3

#include <iostream>
#include <string>

class Node {

  private:
    std::string data;
    Node* next;

  public:
    Node(std::string data, Node* next);
    Node* getNext();
    std::string getData();
    void setData(std::string toSet);
    void setNext(Node* next);
};

class LinkedList {

  private:
    Node* head;

  public:
    bool remove(std::string toRemove);
    void insert(std::string toInsert);
    void traverse();
    Node* search(std::string toFind);
    Node* getHead();
    void setHead(Node* head);
};

class Stack {

  private:
    LinkedList* list;

  public:
    Stack();
    void push(std::string data);
    std::string pop();
    void printStack();
    bool contains(std::string data);
    int maxLoopDepth();
    LinkedList* getList();
};

#endif
