#ifndef MYSORT_HPP
#define MYSORT_HPP
//Using merge sort because the program is already a high-memory-usage program
//so the user should have enough memory to sort

int merge(int *arr,int low,int high,int mid,int size);
int mergeSort(int *arr,int low,int high,int size);

#endif // MYSORT_HPP
