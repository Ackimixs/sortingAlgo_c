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
    int *count = (int *)calloc(max + 1, sizeof(int));
    int *output = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i-1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }

    free(count);
    free(output);
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

void bogoSort(int *array, int size) {
    while (!isSorted(array, size)) {
        for (int i = 0 ; i < size; i++) {
            int j = rand() % size;
            swap(array, i, j);
        }
    }
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

void randomizeArraySizeSize(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size*size;
    }
}

void randomizeArrayBest(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10;
    }
}

void randomizeArrayNotBest(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000000;
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

void runFunction(sortAlgo sort, FILE *file, sortAlgo random) {

    int *arr;
    int n;
    double time_spent = 0.0;
    int numberOfTests = 10;
    int maxArraySize = 25;

    for (int i = 1; i <= maxArraySize; i++) {
        n = i * 500;

        arr = malloc(n * sizeof(int));

        for (int j = 0; j < numberOfTests; j++) {
            time_spent += getExecutionTime(sort, arr, n, random);
        }

        time_spent = time_spent / numberOfTests;
        if (file != NULL) {
            printf("Done for : %d value\n", n);
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
    //writeFile("bubble_sort.csv", bubbleSort, randomizeArray);
    printf("bubble sort finished\n");
    printf("Heap Sort : \n");
    //writeFile("heap_sort.csv", heapSort, randomizeArray);
    printf("heap sort finished\n");
    printf("Counting Sort : \n");
    writeFile("counting_sort.csv", countingSort, randomizeArray);
    printf("Counting Sort finished\n");
    printf("Counting sort best\n");
    //writeFile("counting_sort_best.csv", countingSort, randomizeArrayBest);
    printf("counting sort best finished\n");
    printf("Coutning sort not best :\n");
    //writeFile("counting_sort_not_best.csv", countingSort, randomizeArrayNotBest);
    printf("Counting sort not best finished\n");
}


void writeFile(char *fileName, sortAlgo sort, sortAlgo random) {
    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    runFunction(sort, file, random);

    fclose(file);
}