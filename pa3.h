#ifndef PA3
#define PA3

#include <iostream>
#include <string>

class Node {

  private:
    string data;
    Node* next;

  public:
    Node(string data, Node* next);
    Node* getNext();
    string getData();
    void setData(string toSet);
    void setNext(Node* next);
};

class LinkedList {

  private:
    Node* head;
    Node* tail;

  public:
    bool remove(string toRemove);
    void insert(string toInsert);
    void traverse();
    Node* search(string toFind);
    Node* getHead();
};

class Stack {

  private:
    LinkedList* list;

  public:
    push();
    pop();
};

class pa3 {

  private:
    Stack myStack;

  public:

};

#endif
