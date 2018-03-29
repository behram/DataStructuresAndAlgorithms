#include <iostream>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <cstdlib>

using namespace std;

void insertSort(int array[], int size){
	int temp, j, i;
	for(i = size-2; i >= 0; i--) {
		temp = array[i];

		for (j = i; j < size-1 && temp > array[j+1]; j++)
		{
			array[j] = array[j+1];
		}
		array[j]=temp;
	}
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
	}
}

int * loadArray(int size) {
	int* a = new int[size];
	for (int i = 0; i < size; i++)
		a[i] = rand() % 100;

	return a;
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
	}
}

void sortings(int size)
{
	cout<<"---------------Loading "<<size<<" elements -----------"<<endl;

	//INSERTSORT
	clock_t  all = clock();
	insertSort(loadArray(size),size);
	all = clock() - all;
	cout << "Insert sort " << (((float)all)/CLOCKS_PER_SEC) << endl;

	// BUBBLESORT 1
    all = clock();
    bubbleSort(loadArray(size),size);
	all = clock() - all;
    cout << "Bubble sort " << (((float)all)/CLOCKS_PER_SEC) << endl;

	//MERGESORT
	all = clock();
    mergeSortIter(loadArray(size),size);
	all = clock() - all;
	cout << "Merge sort " << (((float)all)/CLOCKS_PER_SEC) << endl;
}
int main()
{
	sortings(100);
	sortings(10000);
	sortings(100000);

	return 1;
}
