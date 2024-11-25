#include <iostream>
#include <vector>
#include <ctime>
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

// Insertion Sort for small arrays
void insertionSort(vector<int>& arr, int low, int high) 
{
    for (int i = low + 1; i <= high; i++) 
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Hybrid QuickSort with fallback to Insertion Sort for small subarrays
void hybridQuickSort(vector<int>& arr, int low, int high) 
{
    const int threshold = 10; // Threshold for switching to Insertion Sort

    while (low < high) 
    {
        // Use Insertion Sort for small subarrays
        if (high - low < threshold) 
        {
            insertionSort(arr, low, high);
            break;
        }
        else 
        {
            int pivotIndex = partition(arr, low, high);
            
            // Optimized recursive calls for tail recursion
            if (pivotIndex - low < high - pivotIndex) 
            {
                hybridQuickSort(arr, low, pivotIndex - 1);
                low = pivotIndex + 1;
            } 
            else 
            {
                hybridQuickSort(arr, pivotIndex + 1, high);
                high = pivotIndex - 1;
            }
        }
    }
}

// Function to generate a fixed array of a given size (descending order)
vector<int> generateFixedArray(int size) 
{
    vector<int> arr(size);
    for (int i = 0; i < size; i++) 
    {
        arr[i] = size - i;  // Descending order array
    }
    return arr;
}

int main() 
{
    // Array sizes to test
    vector<int> sizes = {100, 1000, 10000};

    for (int size : sizes) 
    {
        // Generate a fixed array of the current size in descending order
        vector<int> arr = generateFixedArray(size);

        // Measure time for Hybrid QuickSort with Insertion Sort fallback
        clock_t start = clock();
        hybridQuickSort(arr, 0, arr.size() - 1);
        clock_t end = clock();

        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        cout << "Time taken by Hybrid Quick Sort on array of size " << size << ": " << time_taken << " seconds" << endl;
    }

    return 0;
}
