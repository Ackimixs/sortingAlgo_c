#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#ifndef SORTINGALGO_SORTALGO_H
#define SORTINGALGO_SORTALGO_H

typedef void (*sortAlgo)(int* , int );

void bubbleSort(int *array, int size);
void selectionSort(int *array, int size);
void insertionSort(int *array, int size);
void countingSort(int *array, int size);

void heapSort(int *array, int size);
void heap(int *array, int size, int index);

void bogoSort(int *array, int size);

void swap(int *array, int i, int j);
void printArray(int *array, int size);
int getMax(int *array, int size);
bool isSorted(int *array, int size);

void runFunction(sortAlgo, FILE *file, sortAlgo random);
void runAll();
double getExecutionTime(sortAlgo sort, int *array, int size, sortAlgo baseSortType);
void randomizeArray(int *array, int size);
void randomizeArraySizeSize(int *array, int size)
void randomizeArrayBest(int *array, int size);
void randomizeArrayNotBest(int *array, int size);

void testingAllFunction(int Size);

void writeFile(char *fileName, sortAlgo sort, sortAlgo random);
#endif //SORTINGALGO_SORTALGO_H
