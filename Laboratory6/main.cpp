#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

struct Heap{
    int *arr;
    int size;
    int pos;
};

void init(Heap& h, int size){
    h.arr = new int[size];
    h.size = 0;
    h.pos = 0;
}

void heapify(Heap &h,int index, int size)
{
    int leftChild = 2 * index + 1;
    if (leftChild < size)
    {
        if (leftChild+1 < size)
        {
            if (h.arr[leftChild+1] > h.arr[leftChild])
            {
                leftChild++;
            }
        }
        if (h.arr[leftChild] > h.arr[index])
        {
            swap(h.arr[index], h.arr[leftChild]);
            heapify(h, leftChild, size);
        }
    }
}

void heapAdjustment(Heap &h)
{
    for(int i=(h.pos-1)/2;i>=0;i--)
        heapify(h, i, h.pos);
}

void loadAndMakeHeap(Heap &h, int howMany){
    string numbers;
    getline(cin,numbers);
    istringstream iss(numbers);
    int i = 0;
    while (iss) {
        string numb;
        iss >> numb;
        h.arr[i] = atoi(numb.c_str());
        i++;
    }
    h.pos = howMany;
    heapAdjustment(h);
}

void add(Heap &h, int value)
{
    if (h.size == -1)
    {
        return;
    }
    h.arr[h.pos] = value;
    int p = h.pos;
    h.pos++;
    while(value > h.arr[(p-1)/2]){
        swap(h.arr[p],h.arr[(p-1)/2]);
        p = (p-1)/2;
    }
}

void makeSorted(Heap& h)
{
    int a = 0;
    for (int i = h.pos-1; i >= 0; i--)
    {
        a++;
        swap(h.arr[0], h.arr[i]);
        heapify(h, 0, h.pos-a);
    }
    h.size = -1;
}

void show(Heap& h){
    for(int i=0;i<h.pos;i++)
    {
        cout << h.arr[i] << ",";
    }
    cout << endl;
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
    Heap *heap;
    int currentH=0;
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
            show(heap[currentH]);
            continue;
        }

        if(isCommand(command,"MS")) //*
        {
            makeSorted(heap[currentH]);
            continue;
        }

        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"IN")) //*
        {
            init(heap[currentH],value);
            continue;
        }

        if(isCommand(command,"LD"))
        {
            loadAndMakeHeap(heap[currentH],value);
            continue;
        }

        if(isCommand(command,"AD"))
        {
            add(heap[currentH],value);
            continue;
        }

        if(isCommand(command,"CH"))
        {
            currentH=value;
            continue;
        }

        if(isCommand(command,"GO"))
        {
            heap=new Heap[value];
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}


