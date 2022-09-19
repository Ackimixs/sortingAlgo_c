#include "sortAlgo.h"
//Algorithm
void bubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0 ; j < size - i - 1; j++) {
            if (array[j] > array[j+1]) {
                swap(array, j, j+1);
            }
        }
    }
}

void selectionSort(int *array, int size) {
    int minIndex;
    for (int i = 0; i < size - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        swap(array, i, minIndex);
    }
}

void insertionSort(int *array, int size) {
    int value, index;
    for (int i = 1; i < size; i++) {
        value = array[i];
        index = i - 1;
        while (index >=0 && array[index] > value) {
            array[index+1] = array[index];
            index--;
        }
        array[index+1] = value;
    }
}

void countingSort(int *array, int size) {
    int max = getMax(array, size);

    int *arr = malloc((max+1)*sizeof(int));

    for (int l = 0; l < max+1; l++) {
        arr[l] = 0;
    }

    for (int i = 0 ; i < size; i++) {
        arr[array[i]]++;
    }

    int output[size];
    int index = 0;

    for (int j = 0; j < max+1; j++) {
        while(arr[j] > 0) {
            output[index] = j;
            arr[j]--;
            index++;
        }
    }

    for (int k = 0; k < size; k++) {
        array[k] = output[k];
    }

    free(arr);
}

void heapSort(int *array, int size) {

    for (int i = size / 2 - 1; i >= 0; i--) {
        heap(array, size, i);
    }

    for (int i = size - 1; i >= 0; i--) {
        swap(array, 0, i);
        heap(array, i, 0);
    }
}

void heap(int *array, int size, int index) {
    int largerIndex = index;
    int left = (2*index)+1;
    int right = (2*index)+2;

    if (left < size && array[left] > array[largerIndex]) {
        largerIndex = left;
    }

    if (right < size && array[right] > array[largerIndex]) {
        largerIndex = right;
    }

    if (largerIndex != index) {
        swap(array, index, largerIndex);
        heap(array, size, largerIndex);
    };
}

//Utility function
void swap(int *array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void printArray(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d", array[size-1]);
}

bool isSorted(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i+1]) {
            return false;
        }
    }
    return true;
}

int getMax(int *array, int size) {
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (max < array[i]) {
            max = array[i];
        }
    }
    return max;
}


//Setter part
void randomizeArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100000;
    }
}

void descendingOrder(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = size - i;
    }
}

void ascendingOrder(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
}


//Execution part
/**
 * @param sort
 * @param array
 * @param size
 * @param baseSortType
 * @return the execution time of the algorithm
 */
double getExecutionTime(sortAlgo sort, int *array, int size, sortAlgo baseSortType) {
    struct timespec start;
    struct timespec end;

    baseSortType(array, size);

    double time = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    sort(array, size);

    clock_gettime(CLOCK_MONOTONIC, &end);

    time += (double) (end.tv_sec - start.tv_sec)  + (double) (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    if (!isSorted(array, size)) {
        printf("ERROR ARRAY NOT SORTED");
        exit(1);
    }

    return time;
}

void runFunction(sortAlgo sort, FILE *file) {

    int *arr;
    int n;
    double time_spent = 0.0;
    int numberOfTests = 10;

    for (int i = 1; i <= 5; i++) {
        n = i * 500;

        arr = malloc(n * sizeof(int));

        for (int j = 0; j < numberOfTests; j++) {
            time_spent += getExecutionTime(sort, arr, n, randomizeArray);
        }

        time_spent = time_spent / numberOfTests;
        if (file != NULL) {
            fprintf(file, "%d;%f\n", n, 1000 * time_spent); // in milliseconds
        }
        else {
            printf("%d;%f\n", n, 1000 * time_spent);
        }
        time_spent = 0;
        free(arr);
    }
}

/**
 * Main testing function to know if the array after the algorithm is sorted and to have their execution time
 * @param Size size of the array
 */
void testingAllFunction(int Size) {

    printf("-----------    TESTING  ALGORITHM     -------------\n");
    printf("Size : %d\n\n", Size);

    int *arr = malloc(Size * sizeof(int));

    double time = getExecutionTime(bubbleSort, arr, Size, randomizeArray);

    printf("BUBBLE SORT : \n   - Execution time : %f\n   - IsSorted ? : %d\n", time, isSorted(arr, Size));

    time = getExecutionTime(heapSort, arr, Size, randomizeArray);

    printf("HEAP SORT : \n   - Execution time : %f\n   - IsSorted ? : %d\n", time, isSorted(arr, Size));

    time = getExecutionTime(countingSort, arr, Size, randomizeArray);

    printf("COUNTING SORT : \n   - Execution time : %f\n   - IsSorted ? : %d\n", time, isSorted(arr, Size));

}

/**
 * the run function that write in file and testing all the function
 */
void runAll() {
    printf("-----------    TESTING  ALGORITHM     -------------\n");
    printf("Bubble Sort : \n");
    writeFile("bubble_sort", bubbleSort);
    printf("\n\n");
    printf("Heap Sort : \n");
    writeFile("heap_sort", heapSort);
    printf("\n\n");
    printf("Counting Sort : \n");
    writeFile("counting_sort", countingSort);
    printf("\nEND");
}


void writeFile(char *fileName, sortAlgo sort) {
    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    runFunction(sort, file);

    fclose(file);
}