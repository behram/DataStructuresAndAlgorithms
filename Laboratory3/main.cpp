#include<iostream>
#include <string>
#include <sstream>

using namespace std;

// Two-way unordered cycled list without sentinel
struct Element {
	int key;
	Element *prev, *next;
};

struct List2W {
	Element *head;
	int length;
};

void init(List2W& l) {
	l.head = NULL;
	l.length=0;
}

void insertHead(List2W& l, int x) {
	Element *newEl = new Element;
	newEl->key = x;
	if (l.head==NULL)
	{
		newEl->next = newEl;
		newEl->prev = newEl;
		l.head = newEl;
	}
	else if (l.head->next!=l.head)
	{
		l.head->prev->next = newEl;
		newEl->prev = l.head->prev;
		newEl->next = l.head;
		l.head->prev = newEl;
		l.head = newEl;
	} else{
        newEl->next = l.head;
        newEl->prev = l.head;
        l.head->next = newEl;
        l.head->prev = newEl;
        l.head = newEl;
    }
    l.length++;
}

bool deleteHead(List2W& l, int &value) {
	if (l.head==NULL)
		return false;
	Element *del = l.head;
	value = del->key;
	if (del->next == del)
	{
		delete del;
		l.head = NULL;
	}
	else
	{
		l.head->prev->next = l.head->next;
		l.head->next->prev = l.head->prev;
		l.head = l.head->next;
		delete del;
	}
	l.length--;
	return true;
}

void insertTail(List2W& l, int x) {

	if (l.head == NULL)
    {
        insertHead(l,x);
        return;
    }

	Element *newEl = new Element;
	newEl->key = x;

	if (l.head->next!=l.head)
    {
        newEl->next = l.head;
        newEl->prev = l.head->prev;
        l.head->prev->next = newEl;
        l.head->prev = newEl;
    }else
    {
        newEl->next =l.head;
        newEl->prev = l.head;
        l.head->prev = newEl;
        l.head->next = newEl;
    }
    l.length++;

}


bool deleteTail(List2W& l, int &value) {
    if (l.head == NULL)
        return false;
    if (l.head->next == l.head)
    {
        Element *del = l.head;
        value = del->key;
        l.head = NULL;
        delete del;
    }else
    {
        Element *del = l.head->prev;
        value = del->key;
        del->prev->next = l.head;
        l.head->prev = del->prev;
        delete del;
    }
    l.length--;
    return true;

}

int findValue(List2W& l, int value) {

    if (l.head == NULL)
        return -1;
    Element *el = l.head;
    int pos = 0;

    while (el->next != l.head)
    {
        if (el->key==value)
        {
            return pos;
        }
        pos++;
        el = el->next;
    }
    if (el->key == value)
    {return pos;}


	return -1;
}


bool removeElement(List2W& l, int x)
{
    int holder;
    if (x==0)
    {
        deleteHead(l, holder);
        return true;
    }else if (x==l.length-1)
    {
        deleteTail(l, holder);
        return true;
    }else if (x>l.length-1 || x<0)
    {
        return false;
    }
    else
    {
        Element *del = l.head;
        for (int i = 0; i<x; i++)
        {
            del = del-> next;
        }
        del->next->prev = del->prev;
        del->prev->next = del->next;
        delete del;
    }
    l.length--;
    return true;
}


void removeAllValue(List2W& l, int value) {

    int pos;
    while (1){
        pos = findValue(l,value);
        if (pos == -1)
            break;
        removeElement(l,pos);
    }
}

void showListFromHead(List2W& l) {
    if (l.head==NULL) {
        cout << endl;
        return;}

    Element *el = l.head;
    cout << el->key << ",";

    while(el->next!=l.head)
    {
        el = el->next;
        cout << el->key << ",";
    }
    cout << endl;
}

void showListFromTail(List2W& l) {
    if (l.head==NULL){
        cout << endl;
        return;}

    Element *el = l.head->prev;
    cout << el->key << ",";

    while(el->prev!=l.head->prev)
    {
        el = el->prev;
        cout << el->key << ",";
    }
    cout << endl;
}

void showBool(bool val) {
    if (val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

void checkEvenValues(List2W& l) {

    if (l.head==NULL) {
        cout << endl;
        return;
    }

    Element *el = l.head;
    if(el->key%2 == 1){
        showBool(false);
        return;
    }

    while(el->next!=l.head)
    {
        el = el->next;
        if(el->key%2 == 1){
            showBool(false);
            return;
        }
    }
    showBool(true);
    cout << endl;
}

void clearList(List2W& l) {

    int len = l.length, t;
    for (int i = 0; i<len; i++)
        deleteTail(l,t);

}

void addListOld(List2W& l1, List2W& l2) {

    if (l1.length==l2.length)
    {
        Element *e1 = l1.head;
        Element *e2 = l2.head;
        int x =0;
        for (int i = 0; i<=l1.length; i++)
        {
            if(e1->key==e2->key)
                x++;
            e1 = e1->next;
            e2 = e2->next;
        }
        if (x==l1.length)
            return;
    }
    Element *e = l2.head;
    for (int i = 0 ; i<l2.length ; i++)
    {
        insertTail(l1,e->key);
        e = e->next;
    }
    clearList(l2);
}

void addList(List2W& l1,List2W& l2){
    if (l1.head == NULL)
    {
        l1=l2;
        l2.head = NULL;
    }
    else if (l2.head == NULL)
    {
        return;
    }
    else if (l1.head == l2.head)
    {
        return;
    }
    else
    {
        Element *last1 = l1.head->prev;
        Element *last2 = l2.head->prev;

        last1->next = l2.head;
        l2.head->prev = last1;

        last2->next = l1.head;
        l1.head->prev = last2;

        l2.head = NULL;
    }
}

bool doubleElements(List2W & l)
{
    if(l.head==NULL)
        return false;
    int len;
    Element *el = l.head;
    if (l.length>1)
    {
        len = l.length;
        for(int i = 0; i< len; i++){
            Element *addin = new Element;
            addin->key = el->key;

            addin->prev =el;
            addin->next =el->next;
            el->next->prev = addin;
            el->next = addin;
            el = el->next->next;

            l.length++;
        }
    }else{
        Element *addin = new Element;
        addin->key = el->key;
        el->next = addin;
        el->prev = addin;
        addin->next = el;
        addin->prev = el;
        l.length++;
    }

    return true;

}


bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}

int main() {
	string line;
	string command;
	List2W *list;
    list = new List2W[1];
	int currentL = 0;
	int value;
	cout << "START" << endl;
	while (true) {
		getline(cin, line);
		std::stringstream stream(line);
		stream >> command;
		if (line == "" || command[0] == '#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0] = toupper(command[0]);
		command[1] = toupper(command[1]);

		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}


		// zero-argument command
		if (isCommand(command, "DH")) //*
		{
			int retValue;
			bool retBool = deleteHead(list[currentL], retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if (isCommand(command, "DT")) //*
		{
			int retValue;
			bool retBool = deleteTail(list[currentL], retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if (isCommand(command, "SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}
		if (isCommand(command, "DE"))
        {
            doubleElements(list[currentL]);
            continue;
        }

		if (isCommand(command, "ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if (isCommand(command, "CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if (isCommand(command, "IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "FV"))
		{
			int ret;
			ret = findValue(list[currentL], value);
			cout << ret << endl;
			continue;
		}

		if (isCommand(command, "RV"))
		{
			removeAllValue(list[currentL], value);
			continue;
		}

        if (isCommand(command, "EV"))
        {
            checkEvenValues(list[currentL]);
            continue;
        }


		if (isCommand(command, "AD")) //*
		{
			addList(list[currentL], list[value]);
			continue;
		}

		if (isCommand(command, "CH")) //*
		{
			currentL = value;
			continue;
		}

		if (isCommand(command, "IH")) //*
		{
			insertHead(list[currentL], value);
			continue;
		}

		if (isCommand(command, "IT")) //*
		{
			insertTail(list[currentL], value);
			continue;
		}

		if (isCommand(command, "GO")) //*
		{
			list = new List2W[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}
