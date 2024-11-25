#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>  // For rand() and srand()
using namespace std;

// Swap function
void swap(int* a, int* b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function with last element as pivot
int partition(vector<int>& arr, int low, int high) 
{
    int pivot = arr[high];  // Choose the last element as pivot
    int i = low - 1;        // Index of the smaller element
    for (int j = low; j <= high - 1; j++) 
    {
        if (arr[j] < pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;  // Return the pivot index
}

// Partition function with random pivot
int randomPivotPartition(vector<int>& arr, int low, int high) 
{
    // Generate a random pivot index between low and high
    int randomIndex = low + rand() % (high - low + 1);
    swap(&arr[randomIndex], &arr[high]);  // Move random pivot to end

    // Use the standard partition function with this random pivot
    return partition(arr, low, high);
}

// QuickSort with last element as pivot
void quickSort(vector<int>& arr, int low, int high) 
{
    if (low < high) 
    {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// QuickSort with random pivot selection
void quickSortRandomPivot(vector<int>& arr, int low, int high) 
{
    if (low < high) 
    {
        int pivotIndex = randomPivotPartition(arr, low, high);
        quickSortRandomPivot(arr, low, pivotIndex - 1);
        quickSortRandomPivot(arr, pivotIndex + 1, high);
    }
}

// Utility function to print the array
void printArray(const vector<int>& arr) 
{
    for (int num : arr) 
    {
        cout << num << " ";
    }
    cout << endl;
}

int main() 
{
    // Initialize random seed
    srand(time(0));

    // Original array
    vector<int> arr = {33, 12, 52, 3, 75, 29, 41, 6, 19};

    cout << "Original Array: ";
    printArray(arr);

    // Measure time for QuickSort with last element as pivot
    vector<int> arr1 = arr;  // Copy of the array
    clock_t start = clock();
    quickSort(arr1, 0, arr1.size() - 1);
    clock_t end = clock();
    double time_taken_original = double(end - start) / CLOCKS_PER_SEC;

    cout << "Sorted Array with last element as pivot: ";
    printArray(arr1);
    cout << "Time taken by Quick Sort (last element as pivot): " << time_taken_original << " seconds" << endl;

    // Measure time for QuickSort with random pivot
    vector<int> arr2 = arr;  // Copy of the array
    start = clock();
    quickSortRandomPivot(arr2, 0, arr2.size() - 1);
    end = clock();
    double time_taken_random = double(end - start) / CLOCKS_PER_SEC;

    cout << "Sorted Array with random pivot: ";
    printArray(arr2);
    cout << "Time taken by Quick Sort (random pivot): " << time_taken_random << " seconds" << endl;

    return 0;
}

