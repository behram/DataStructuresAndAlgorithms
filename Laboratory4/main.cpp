#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

struct Element{
  int key;
  int value;
};

struct ElementLL{
  Element elem;
  ElementLL *next, *prev;
};

struct List2W{
  ElementLL *sentinel;
};

void init(List2W& l){
  l.sentinel = new ElementLL();
  l.sentinel -> next = l.sentinel;
  l.sentinel -> prev = l.sentinel;
}
void insertElem(List2W & l, Element elem){
  ElementLL *n = new ElementLL();
  n -> elem = elem;
  ElementLL *i = l.sentinel;
  while(i->prev->elem.key > n->elem.key && i->prev != l.sentinel) {
    i = i->prev;
  }
  i->prev -> next = n;
  n -> next = i;
  n -> prev = i->prev;
  i -> prev = n;
}

void insertElemSec(List2W & l, Element elem){
  ElementLL *n = new ElementLL();
  n -> elem = elem;
  ElementLL *i = l.sentinel;

  i->prev -> next = n;
  n -> next = i;
  n -> prev = i->prev;
  i -> prev = n;
}


bool findKey(List2W & l,int key, Element &elem){
  if(l.sentinel -> next == l.sentinel)
	  return false;
  ElementLL *n = l.sentinel->next;
  while(n != l.sentinel){
    if(n->elem.key == key){
      elem = n->elem;
      return true;
    }
    n = n->next;
  }
  return false;
}

void removeAllKeys(List2W& l, int key){
  if(l.sentinel -> next == l.sentinel)
	  return;
  ElementLL *n = l.sentinel-> next;

  while(n != l.sentinel){

    if(n->elem.key == key){
      n->prev -> next = n->next;
      n->next -> prev = n->prev;
      ElementLL *tmp = n;
      n = n->next;
      delete tmp;
    }
    else {
      n = n->next;
    }
  }
}

void showListFromHead(List2W& l){
  for(ElementLL *n = l.sentinel->next; n != l.sentinel; n = n->next){
    cout << n->elem.key << "(" << n->elem.value << "),";
  }
  cout << endl;

}

void showListFromTail(List2W& l){
  for(ElementLL *n = l.sentinel->prev; n != l.sentinel; n = n->prev){
    cout << n->elem.key << "(" << n->elem.value << "),";
  }
  cout << endl;
}

void clearList(List2W& l){
  for(ElementLL *tmp = l.sentinel->next; tmp != l.sentinel; tmp=l.sentinel->next){
    l.sentinel->next = l.sentinel->next->next;
    delete tmp;
  }
  init(l);
}

void addList(List2W& l1,List2W& l2){
	if(l2.sentinel->next == l2.sentinel)
		return;
	if(l1.sentinel == l2.sentinel)
	   	return;

	    ElementLL *n = l2.sentinel -> next;

	    while(n != l2.sentinel)
	    {
	        insertElem(l1, n->elem);
	        n = n->next;
	    }

	    clearList(l2);
}

void showBool(bool val){
	if(val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	List2W *list = NULL;
	int currentL=0;
	int value;
	cout << "START" << endl;
	while(true){
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(isCommand(command,"SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(list[currentL], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			removeAllKeys(list[currentL],value);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			insertElem(list[currentL],elem);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List2W[value];
			continue;
		}

		if(isCommand(command,"AD"))
		{
			addList(list[currentL],list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}