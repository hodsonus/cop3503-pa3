#include <iostream>
#include <string>
#include "pa3.h"

//node constructor
Node::Node(std::string data, Node* next) {

  this->data = data;
  this->next = next;
}

//returns the next node
Node* Node::getNext() {

  return this->next;
}

//returns this node's data
std::string Node::getData() {

  return this->data;
}

//sets the node's data to the string that is passed in
void Node::setData(std::string toSet) {

  this->data = toSet;
}

//sets this node's next node
void Node::setNext(Node* next) {

  this->next = next;
}

//removes data from the list
bool LinkedList::remove(std::string toRemove) {

    //if the head is null then there are no nodes and thus no string to remove
    if (head == NULL) {
      return false;
    }

    //start at the head
    Node * temp = head;

    //if the head is equal to the element we want to remove
    if (temp->getData().compare(toRemove)==0) {
      head = head->getNext();
      delete temp;
      return true;
    }

    /* keep going until the next node in the linked list is null or the next
     node in the linked list is the element that we are searching for */
    while (temp->getNext() != NULL && !(temp->getNext()->getData().compare(toRemove)==0)) {
      temp = temp->getNext();
    }

    /* from the previous while loop, if the next element is null, then the
    element is not present in the list */
    if (temp->getNext() == NULL) return false;

    /* if the previous if statement is not executed, then we know the next
    element is the one that we are searching for! delete it! */

      // temp->getNext()->getNext() != NULL
      temp->setNext(temp->getNext()->getNext());
      delete temp->getNext();
      return true;
}

//data to insert
void LinkedList::insert(std::string toInsert) {

  //start at the head
  Node* current = head;

  //if the head is null, then the element is inserted as the head
  if (current == NULL) {

    head = new Node(toInsert, NULL);
    return;
  }

  //keep going until the next node in the linked list is null
  while (current->getNext() != NULL) {

    current = current->getNext();
  }

  /* set the next node in the linked list, which is null at this point, to
  the element we want to insert */
  current->setNext(new Node(toInsert, NULL));
}

//print the linked list, seperated by spaces
void LinkedList::traverse() {

  //start at the head
  Node* temp = head;

  //we've printed none, so far
  int count = 0;

  //so long as there's elements in the linked list that havent been printed...
  while (temp != NULL) {

    //print the current element
    std::cout << temp->getData();

    //increment the amount of printed elements
    count++;

    /* these lines control the formatting. if we have printed a multiple of 8
    elements, then we are at the end of the line and should indent. if we have
    printed between 0 and 8 noninclusive, then we must seperate the elements
    with a tab*/
    if (count%8 > 0 && count%8 < 8) std::cout << "\t";
    if (count % 8 == 0) std::cout << std::endl;

    //move to the next element
    temp = temp->getNext();
  }

  //print additional line
  if (count != 0) std::cout << std::endl;
}

//search the linked list and return the node's memory address
Node* LinkedList::search(std::string toFind) {

  //start at the head
  Node * temp = head;

  /* if the head is null, then there are no elements in the linked list and
  thus no element that we are searching for */
  if (temp == NULL) return NULL;

  //if the current element (the head) is equal to the element we want to find, return it!
  if (temp->getData().compare(toFind)==0) return temp;

  /* so long as the next element is not null and it is not the element we are
  looking for, move to the next element */
  while (temp->getNext() != NULL && !(temp->getNext()->getData().compare(toFind)==0)) {

    temp = temp->getNext();
  }

  //from the previous loop, if the next element is null then the element isnt in the list
  if (temp->getNext() == NULL) return NULL;

  //if we have gotten this far, then the next element is the element we're looking for!
  return temp->getNext();
}

//return the head of the linked list
Node* LinkedList::getHead() {

  return this->head;
}

//set the head to the passed in head
void LinkedList::setHead(Node* head) {

  this->head = head;
}

//stack constructor
Stack::Stack() {

  list = new LinkedList();
}

//push from the stack
void Stack::push(std::string data) {

  list->insert(data);
}

//pop from the stack
std::string Stack::pop() {

  if (list->getHead() == NULL) {
    return "";
  }

  Node* current = list->getHead();

  if (current->getNext() == NULL) {

    std::string toReturn = current->getData();
    list->setHead(NULL);
    delete current;
    return toReturn;
  }

  //breaks when the node after the next is null
  while (current->getNext()->getNext() != NULL) {
    current = current->getNext();
  }

  std::string toReturn = current->getNext()->getData();

  delete current->getNext();
  current->setNext(NULL);

  return toReturn;
}

//prints stack
void Stack::printStack() {

  list->traverse();
}

int main() {

  Stack* myStack = new Stack();

  myStack->push("hi");

  myStack->push("hello");

  myStack->push("donut");

  myStack->printStack();

  myStack->pop();

  myStack->pop();

  myStack->printStack();

  myStack->pop();

  myStack->pop();

  myStack->printStack();

  return 0;
}
