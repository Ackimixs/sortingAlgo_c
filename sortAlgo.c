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

void bubbleSortV2(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        bool sorted = false;
        for (int j = 0 ; j < size - i - 1; j++) {
            if (array[j] > array[j+1]) {
                sorted = true;
                swap(array, j, j+1);
            }
        }
        if (sorted == false) {
            return;
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


//random for counting sort
void randomizeArraySizeSize(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size*size;
    }
}


//random for counting sort
void randomizeArrayLog(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (size * (int) (log(size)));
    }
}

void randomizeArrayLogN(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (((size * (int) (log(size))) - size));
    }
}

void randomizeArraySizeSizeN(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % ((size*size)-size);
    }
}

void randomizeArrayBest(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }
}

void randomizeArrayNotBest(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000000;
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
    int numberOfTests = 50;
    int maxArraySize = 50;

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
    srand(time(NULL));

    printf("-----------    TESTING  ALGORITHM     -------------\n");

    //random
    printf("Bubble Sort : \n");
    //writeFile("/home/acki/Documents/Projet-final/bubble_sort/bubble_sort.csv", bubbleSort, randomizeArray);
    printf("bubble sort finished\n");


    //random V2
    printf("Bubble Sort V2: \n");
    //writeFile("/home/acki/Documents/Projet-final/bubble_sort_V2/bubble_sortV2.csv", bubbleSortV2, randomizeArray);
    printf("bubble sort V2 finished\n");


    // croissant V2
    printf("Bubble Sort V2 croissant: \n");
    //writeFile("/home/acki/Documents/Projet-final/bubble_sort_croissant_V2/bubble_sort_croissantV2.csv", bubbleSortV2, ascendingOrder);
    printf("bubble sort croissant finished\n");


    //decroissant V2
    printf("Bubble Sort V2 decroissant : \n");
    //writeFile("/home/acki/Documents/Projet-final/bubble_sort_decroissant_V2/bubble_sort_decroissantV2.csv", bubbleSortV2, descendingOrder);
    printf("bubble sort decroissant finished\n");


    // Heap Sort V2
    printf("Heap Sort : \n");
    //writeFile("/home/acki/Documents/Projet-final/heap_sort/heap_sort.csv", heapSort, randomizeArray);
    printf("heap sort finished\n");


    // Counting Sort
    printf("Counting Sort : \n");
    //writeFile("/home/acki/Documents/Projet-final/counting_sort/counting_sort.csv", countingSort, randomizeArray);
    printf("Counting Sort finished\n");


    // Counting Sort best
    printf("Counting sort best\n");
    //writeFile("/home/acki/Documents/Projet-final/counting_sort_best/counting_sort_best.csv", countingSort, randomizeArrayBest);
    printf("counting sort best finished\n");


    // Counting Sort not best
    printf("Coutning sort not best :\n");
    //writeFile("/home/acki/Documents/Projet-final/counting_sort_not_best/counting_sort_not_best.csv", countingSort, randomizeArrayNotBest);
    printf("Counting sort not best finished\n");


    // Counting Sort N carré
    printf("Counting Sort N carre : \n");
    //writeFile("/home/acki/Documents/Projet-final/counting_sortnn/counting_sort_n_n.csv", countingSort, randomizeArraySizeSize);
    printf("Counting Sort N carre finished\n");


    // Counting Sort N log(n)
    printf("Counting Sort N log(n) : \n");
    //writeFile("/home/acki/Documents/Projet-final/counting_sortlog/counting_sort_log.csv", countingSort, randomizeArrayLog);
    printf("Counting Sort N log(n) finished\n");

    // Counting Sort N log(n) - n
    printf("Counting Sort N log(n) - n : \n");
    writeFile("/home/acki/Documents/Projet-final/counting_sortlogN/counting_sort_log_n.csv", countingSort, randomizeArrayLogN);
    printf("Counting Sort N log(n) - n finished\n");

    // Counting Sort N log(n) - n
    printf("Counting Sort N carre - n : \n");
    //writeFile("/home/acki/Documents/Projet-final/counting_sortnnn/counting_sort_n_n_n.csv", countingSort, randomizeArraySizeSizeN);
    printf("Counting Sort N carre - n finished\n");
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

void comparBubble() {
    srand(time(NULL));

    printf("-----------    TESTING  ALGORITHM     -------------\n");

    //random
    printf("Compare bubble Sort : \n");
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/checkBubbleBad/bubble_sort.csv", bubbleSort, descendingOrder);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/checkBubbleBad/heap_sort.csv", heapSort, descendingOrder);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/checkBubbleBad/counting_sort.csv", countingSort, descendingOrder);
    printf("Compare bubble finished\n");
}

void comparHeapCounting() {
    srand(time(NULL));

    printf("-----------    TESTING  ALGORITHM     -------------\n");

    //random
    printf("Compare bubble Sort : \n");
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/checkHeapCounting/heap_sort.csv", heapSort, randomizeArray);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/checkHeapCounting/counting_sort.csv", countingSort, randomizeArray);
    system("cd /home/acki/CLionProjects/sortingAlgo/Projet-final/checkHeapCounting && gnuplot *.gnu -persist");
    printf("Compare bubble finished\n");
}



void compareAll() {
    compareHeapCountingBest();
    //compareHeapCountingNormal();
    //compareCountingNotBestBubble();
    //compareCountingWorstBubbleWorstBubbleNormal();
}

void compareHeapCountingBest() {
    srand(time(NULL));

    printf("-----------    TESTING  ALGORITHM     -------------\n");

    //random
    printf("Compare Sort 1 : \n");
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkHeapCountingBest/heap_sort.csv", heapSort, descendingOrder);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkHeapCountingBest/counting_sort.csv", countingSort, randomizeArrayBest);
    system("cd /home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkHeapCountingBest && gnuplot *.gnu -persist");
    printf("Compare 1 finished\n");
}

void compareHeapCountingNormal() {
    srand(time(NULL));

    printf("-----------    TESTING  ALGORITHM     -------------\n");

    //random
    printf("Compare Sort 2 : \n");
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkHeapCountingNormal/heap_sort.csv", heapSort, randomizeArray);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkHeapCountingNormal/counting_sort.csv", countingSort, randomizeArray);
    system("cd /home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkHeapCountingNormal && gnuplot *.gnu -persist");
    printf("Compare 2 finished\n");
}

void compareCountingNotBestBubble() {
    srand(time(NULL));

    printf("-----------    TESTING  ALGORITHM     -------------\n");

    //random
    printf("Compare Sort 3 : \n");
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingNotBestBubble/counting_sort.csv", countingSort, randomizeArrayNotBest);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingNotBestBubble/bubble_sort.csv", bubbleSortV2, randomizeArray);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingNotBestBubble/heap_sort.csv", heapSort, randomizeArray);
    system("cd /home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingNotBestBubble && gnuplot *.gnu -persist");
    printf("Compare 3 finished\n");
}

void compareCountingWorstBubbleWorstBubbleNormal() {
    srand(time(NULL));

    printf("-----------    TESTING  ALGORITHM     -------------\n");

    //random
    printf("Compare Sort 5 : \n");
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingWorstBubbleWorstBubbleNormal/counting_sort.csv", countingSort, randomizeArrayNotBest);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingWorstBubbleWorstBubbleNormal/bubble_sort_worst.csv", bubbleSort, descendingOrder);
    writeFile("/home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingWorstBubbleWorstBubbleNormal/bubble_sort.csv", bubbleSort, randomizeArray);
    system("cd /home/acki/CLionProjects/sortingAlgo/Projet-final/check/checkCountingWorstBubbleWorstBubbleNormal && gnuplot *.gnu -persist");
    printf("Compare 5 finished\n");
}