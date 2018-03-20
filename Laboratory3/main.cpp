#include<iostream>
#include<string.h>

using namespace std;

struct Element{
    int key;
    Element *next;
    Element *prev;
};

struct List2W{
    Element *head;
};

void init(List2W& l){
    l.head = new Element;
    l.head = NULL;
}

void insertHead(List2W& l, int x){
    Element *fresh = new Element;
    Element *p = l.head;
    fresh->key = x;
    if (p == NULL){
        fresh->next = fresh;
        fresh->prev = fresh;
    } else {
        fresh->next = l.head;
        fresh->prev = fresh->next->prev;
        fresh->prev->next = fresh;
        fresh->next->prev = fresh;
    }
    l.head = fresh;
}

bool deleteHead(List2W& l, int &value){
    Element *p = l.head;
    if (p==NULL) return false;

    Element *temp;
    temp = l.head;
    value=temp->key;
    if (l.head == p->next)
        l.head = NULL;
    else {
        p->next->prev = p->prev;
        p->prev->next = p->next;
        l.head = p->next;
    }
    delete temp;
    return true;
}

void insertTail(List2W& l, int x){
    Element *fresh = new Element;
    Element *p = l.head;
    fresh->key = x;
    if (p == NULL){
        fresh->next = fresh;
        fresh->prev = fresh;
        l.head = fresh;
    } else {
        p = p->prev;
        fresh->next = p->next;
        fresh->prev = p;
        p->next = fresh;
        fresh->next->prev = fresh;
    }
}

bool deleteTail(List2W& l, int &value){
    Element *p = l.head;
    if (p==NULL) return false;
    p=p->prev;
    Element *temp;
    temp = p;
    value=temp->key;
    if (l.head == p)
        l.head = NULL;
    else
    {
        p->next->prev = p->prev;
        p->prev->next = p->next;
    }
    delete temp;
    return true;
}

int findValue(List2W& l, int value){
    Element *p = l.head;
    int counter = 0;
    if (p!=NULL)
        while (true)
        {
            if (p->key == value)
                return counter;
            p = p->next;
            if (p==l.head)
                break;
            counter++;
        }
    return -1;
}

void removeAllValue(List2W& l, int value){
    if (l.head!=NULL){
        bool isBreak = true;
        Element *p = l.head;
        Element *temp;
        if (p!=NULL)
            while (true)
            {
                if (p->key == value){
                    temp = p;
                    if (p == l.head){
                        if (p->next == p) {
                            l.head = NULL;
                            delete p;
                            break;
                        }else{
                            l.head = p->next;
                            isBreak = false;
                        }
                    }

                    p->next->prev = p->prev;
                    p->prev->next = p->next;
                    p = p->next;

                    delete temp;
                }
                else
                {
                    p = p->next;
                }
                if (p==l.head && isBreak)
                    break;
                else
                    isBreak = true;
            }
    }
}

void showListFromHead(List2W& l){
    Element *p = l.head;
    if (p!=NULL)
        while (true)
        {
            cout<<p->key<<",";
            p = p->next;
            if (p==l.head) break;
        }
    cout<<endl;
}

void deleteOddPositions(List2W& l){
    Element *p = l.head;
    int counter = 1;
    if (p!=NULL){
        while (true)
        {
            if(counter%2 == 0){

            }
            cout<<p->key<<",";
            p = p->next;
            if (p==l.head) break;
        }
    }
    cout<<endl;
}

void showListFromTail(List2W& l){
    Element *p = l.head;
    if (p!=NULL)
    {
        p=p->prev;
        while (true)
        {
            cout<<p->key<<",";
            if (p==l.head) break;
            p = p->prev;
        }
    }
    cout<<endl;
}

void clearList(List2W& l){
    if (l.head!=NULL)
    {
        Element *p = l.head;
        int v;
        while (p!=NULL)
        {
            deleteHead(l,v);
            if (l.head->next==l.head)
            {
                deleteHead(l,v);
                break;
            }
            p = p->next;
        }
    }
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
void showBool(bool val){
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

bool isCommand(const char *command,const char *mnemonic){
    return strcmp(command,mnemonic)==0;
}

int main(){
    const int commandSize=2;
    const int MAXLINE=100;
    char line[MAXLINE];
    char command[commandSize+1];
    List2W *list;
    list=new List2W[1];
    int currentL=0;
    int value;
    command[commandSize]='\0';
    while(true){
        cin >> command[0];
        if(command[0]=='#')
        {
            cin.getline(line, MAXLINE);
            continue;
        }
        cin >> command[1];

        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }

        if(isCommand(command,"DH"))
        {
            int value=-9999;
            bool retBool=deleteHead(list[currentL],value);
            if(retBool)
                cout << value << endl;
            else
                showBool(false);
            continue;
        }
        if(isCommand(command,"DT"))
        {
            int value=-9999;
            bool retBool=deleteTail(list[currentL],value);
            if(retBool)
                cout << value << endl;
            else
                showBool(false);
            continue;
        }

        if(isCommand(command,"ST"))
        {
            showListFromTail(list[currentL]);
            continue;
        }

        if(isCommand(command,"SH"))
        {
            showListFromHead(list[currentL]);
            continue;
        }

        if(isCommand(command,"DE"))
        {
            deleteOddPositions(list[currentL]);
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

        cin >> value;

        if(isCommand(command,"FV"))
        {
            int ret;
            ret=findValue(list[currentL],value);
            cout << ret << endl;
            continue;
        }

        if(isCommand(command,"RV"))
        {
            removeAllValue(list[currentL],value);
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
            list=new List2W[value];
            continue;
        }

        if(isCommand(command,"AD"))
        {
            addList(list[currentL],list[value]);
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
        return 1;
    }
}
