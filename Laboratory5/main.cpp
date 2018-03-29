#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits.h>

using namespace std;

void showArray(int array[], int size){
    for (int i = 0; i<size; i++) {
        cout << array[i] << ',';
    }
    cout << endl;
}

void insertSort(int array[], int size){
    int temp, j, i;
    for(i = size-2; i >= 0; i--) {
        temp = array[i];

        for (j = i; j < size-1 && temp > array[j+1]; j++)
        {
            array[j] = array[j+1];
        }
        array[j]=temp;
        showArray(array,size);
    }
}

void mergeArray(int array[], int nFrom, int mid, int nTo){
    int *left = new int[mid-nFrom+1];
    int *right = new int[nTo-mid+1];
    int i;

    for (i = 0; i < mid-nFrom; i++) {
        left[i] = array[nFrom+i];
    }
    left[mid-nFrom] = INT_MAX;
    for (i = 0; i< nTo-mid; i++) {
        right[i] = array[mid+i];
    }
    right[nTo-mid] = INT_MAX;
    int g = 0;
    int d = 0;
    for (int i = nFrom; i< nTo; i++) {
        if (left[g]<right[d])
        {
            array[i] = left[g];
            g++;
        } else {
            array[i] = right[d];
            d++;
        }
    }

    delete[] left;
    delete[] right;
}

void bubbleSort(int array[], int size){
    int i;
    for(i = size-1; i > 0; i--)
    {
        int j;
        for (j = size-1; j > 0; j--)
        {
            if(array[j]<array[j-1])
            {
                int temp= array[j];
                array[j]=array[j-1];
                array[j-1]=temp;
            }
        }
        showArray(array,size);
    }
}

void mergeSortIter(int array[], int size){
    int mid, end, i;

    for (i=1; i < size; i*=2) {
        int k;
        for (k = 0; k<size; k+=2*i) {
            mid = k+i;
            end = k+2*i;
            if (end>size) {
                end = size;
                if (mid > size) {
                    mid = size;
                }
            }
            mergeArray(array,k, mid, end);
        }
        showArray(array, size);
    }
}

int * loadArray(int size){
    int *arr = new int[size];
    for (int i = 0; i<size; i++) {
        cin >> arr[i];
    }
    return arr;
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    int size=0;
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

        // read next argument, one int size
        stream >> size;

        // one-argument command
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }

        if(isCommand(command,"IS")) //*
        {
            int *arr=loadArray(size);
            showArray(arr,size);
            insertSort(arr,size);
            continue;
        }

        if(isCommand(command,"BS")) //*
        {
            int *arr=loadArray(size);
            showArray(arr,size);
            bubbleSort(arr,size);
            continue;
        }

        if(isCommand(command,"MI")) //*
        {
            int *arr=loadArray(size);
            showArray(arr,size);
            mergeSortIter(arr,size);
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
