#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element
{
    int value;
    Element *next;
};

struct List
{
    Element *head;
    Element *tail;
};

void init(List& l)
{
    l = *new List;
    l.head=0;
    l.tail=0;
}

void insertHead(List& l, int x)
{
    Element *newElem = new Element;
    newElem->value = x;
    newElem->next = l.head;
    if(l.head==0)
    {
        l.tail = newElem;
    }
    l.head = newElem;
}

bool deleteHead(List& l, int &oldHead)
{
    if(l.head==0){

        return false;
    }else{
        oldHead = l.head->value;
        Element *head = l.head;
        l.head = l.head->next;
        delete head;

        return true;
    }
}

void insertTail(List& l, int x)
{
    if(l.head==0){
        insertHead(l, x);
    }else{
        Element *el = new Element;
        el->value = x;
        el->next = NULL;
        l.tail->next = el;
        l.tail = el;
    }
}

bool deleteTail(List& l, int &oldTail)
{
    if(l.head==0){
        return false;
    }else if(l.head==l.tail){
        deleteHead(l, oldTail);
        return true;
    }else{
        oldTail= l.tail->value;
        Element *el=l.head;

        while(el != l.tail){
            if(el->next->next==NULL) break;
            el=el->next;
        }
        delete l.tail;
        l.tail=el;
        el->next=0;

        return true;
    }
}

int findPosOfValue(List& l, int value)
{
    int index=0;
    Element *el= l.head;
    while (el !=NULL)
    {
        if (el->value == value){
            return index;
        }
        el=el->next;
        index++;
    }

    return -1;
}

bool deleteValue(List& l, int value)
{
    int index= findPosOfValue(l, value);
    if (index != -1){
        Element *el=l.head;
        if (index==0){
            l.head=l.head->next;
            delete el;

            return true;
        }else{
            Element *before=el;

            for(int i=0; i<index-1; i++){
                before=before->next;
            }
            el=before->next;
            if (el->next==NULL){
                deleteTail(l, value);
                return true;
            }else{
                before->next=el->next;
                delete el;
                return true;
            }
        }
    }else{
        return false;
    }
}

bool atPosition(List& l, int pos, int &value)
{
    if(l.head==0){
        return false;
    }else{
        Element *el=l.head;
        for(int i=0; i<= pos-1; i++){
            el=el->next;
            if (el==NULL){
                return false;
            }
        }
        value=el->value;
        return true;
    }
}

void showListFromHead(List& l)
{
    Element *el=l.head;
    while (el!=NULL){
        cout << el->value <<",";
        el=el->next;
    }
    cout <<endl;
}

void sumElemPositions(List& l)
{
    int counter = 0;
    Element *el=l.head;
    while (el!=NULL){
        counter = counter+1;
        el=el->next;
    }
    cout <<counter;
    cout <<endl;
}

void sumElemValues(List& l)
{
    int sum = 0;
    Element *el=l.head;
    while (el!=NULL){
        if(el->value%2 == 0){
            sum = sum + el->value;
        }
        el=el->next;
    }
    cout <<sum;
    cout <<endl;
}

void clearList(List& l)
{
    Element *el=l.head;
    while(el!=NULL){
        l.head = l.head->next;
        delete el;
        el=l.head;
    }
    l.head=l.tail=0;
}

void showBool(bool val)
{
    if(val){
        cout << "true" << endl;
    }else{
        cout << "false" << endl;
    }
}


bool isCommand(const string command,const char *mnemonic)
{
    return command==mnemonic;
}

int main()
{
    string line;
    string command;
    List *list;
    int currentL=0;
    int value;
    cout << "START" << endl;
    while(true)
    {
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

        if(isCommand(command,"HA"))
        {
            cout << "END OF EXECUTION" << endl;
            break;
        }


        // zero-argument command
        if(isCommand(command,"DH"))
        {
            int retValue;
            bool retBool=deleteHead(list[currentL],retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }
        if(isCommand(command,"DT"))
        {
            int retValue;
            bool retBool=deleteTail(list[currentL],retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }

        if(isCommand(command,"SH"))
        {
            showListFromHead(list[currentL]);
            continue;
        }

        if(isCommand(command,"SEP"))
        {
            sumElemPositions(list[currentL]);
            continue;
        }

        if(isCommand(command,"SEV"))
        {
            sumElemValues(list[currentL]);
            continue;
        }

        if(isCommand(command,"CL"))
        {
            clearList(list[currentL]);
            continue;
        }

        if(isCommand(command,"IN"))
        {
            init(list[currentL]);
            continue;
        }

        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"FP"))
        {
            int ret;
            ret=findPosOfValue(list[currentL],value);
            cout << ret << endl;
            continue;
        }

        if(isCommand(command,"DV"))
        {
            showBool(deleteValue(list[currentL],value));
            continue;
        }


        if(isCommand(command,"AT"))
        {
            int retValue;
            bool retBool=atPosition(list[currentL],value,retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }

        if(isCommand(command,"CH"))
        {
            currentL=value;
            continue;
        }

        if(isCommand(command,"IH"))
        {
            insertHead(list[currentL],value);
            continue;
        }

        if(isCommand(command,"IT"))
        {
            insertTail(list[currentL],value);
            continue;
        }

        if(isCommand(command,"GO"))
        {
            list=new List[value];
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
}
