#include <iostream>
#include <string>
#include <fstream>
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

  //print additional line if we printed something
  std::cout << std::endl;
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

//checks to see if the stack contains the data that is passed in
bool Stack::contains(std::string data) {

  Node* current = list->getHead();

  while (true) {

    if (current == NULL) return false;
    if (current->getData() == data) return true;
    current = current->getNext();
  }
}

//returns the stack's linked list
LinkedList* Stack::getList() {
  return this->list;
}

int main() {

  //gets valid file instance
  std::cout << "Please enter the name of the input file:" << std::endl;
  std::string fileName;
  std::cin >>  fileName;
  std::ifstream myFile;
  myFile.open(fileName);
  //myFile is false when the file did not open
  if (!myFile) {
        std::cout << "Error when opening file. Please try again." << std::endl;
        exit(1); // terminate with error
    }

  //declare the stacks
  Stack keywords, identifiers, constants, operators, delimiters, errors;

  //declare counting variables
  int amtFOR = 0, amtBEGIN = 0, amtEND = 0;
  int loopDepth = 0;

  //declare temp string for use in analysis loop
  std::string word;

  //loop through each word in the file, delimited by spaces and line breaks
  while (myFile >> word) {

    // std::cout << word << std::endl;

    //check the word to see if it is a keyword
    if (word == "FOR" || word == "BEGIN" || word == "END") {

      if (!keywords.contains(word)) keywords.push(word);

      if (word == "FOR") amtFOR++;
      else if (word == "BEGIN") amtBEGIN++;
      else amtEND++;
    }

    //checks the word to see the delimiters and the operators that it contains
    for (int i = 0; i < word.length(); i++) {

      if (!operators.contains("++") && word.find("++)") > 0) {

        operators.push("++");
        break;
      }

      else if (!delimiters.contains(";") && word.at(i) == ';') {

        delimiters.push(";");
      }
      else if (!delimiters.contains(",") && word.at(i) == ',') {

        delimiters.push(",");
      }
      else if (!operators.contains("+") && word.at(i) == '+') {

        operators.push("+");
      }
      else if (!operators.contains("-") && word.at(i) == '-') {

        operators.push("-");
      }
      else if (!operators.contains("*") && word.at(i) == '*') {

        operators.push("*");
      }
      else if (!operators.contains("/") && word.at(i) == '/') {

        operators.push("/");
      }
      else if (!operators.contains("=") && word.at(i) == '=') {

        operators.push("=");
      }
    }

    //checks the word to see the identifiers that it contains
    {

      //location of the equals sign in the word, -1 if not present
      int indexEquals = word.find("=");

      //single variable case
      if (word.length() == 1 && word.at(0)>='a' && word.at(0)<='z' && !identifiers.contains(word)) {

        identifiers.push(word);
      }

      //equals sign case
      else if (indexEquals >=1 && !identifiers.contains(word.substr(0,indexEquals))) {

        identifiers.push(word.substr(0,indexEquals));
      }

      //parentheses and comma case
      else if (word.at(0) == '(' && word.length()>=2 && !identifiers.contains(word.substr(1, word.length()-2))) {

        identifiers.push(word.substr(1, word.length()-2));
      }

      //semi colon case
      else if (word.length()>=2 && word.at(word.length()-1) == ';' && !identifiers.contains(word.substr(0,word.length()-1))) {

        identifiers.push(word.substr(0,word.length()-1));
      }
    }

    //checks the word to see the constants that it contains
    {

      
    }

    //handles the syntax errors



  }

  //calculate loopdepth

  //print out the results of the lexical analysis
  std::cout << "The depth of nested loop(s) is " << loopDepth << "\n" << std::endl;

  std::cout << "Keywords: ";
  keywords.printStack();

  std::cout << "Identifiers: ";
  identifiers.printStack();

  std::cout << "Constants: ";
  constants.printStack();

  std::cout << "Operators: ";
  operators.printStack();

  std::cout << "Delimiters: ";
  delimiters.printStack();

  std::cout << std::endl << "Syntax Error(s): ";
  if (errors.getList()->getHead() == NULL) std::cout << "NA" << std::endl;
  else errors.printStack();

  //clean up and close
  myFile.close();
  return 0;
}
