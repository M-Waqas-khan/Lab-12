#include <iostream>
#include <vector>
using namespace std;

// Function to merge two sorted halves
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements of leftArr
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy any remaining elements of rightArr
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Recursive merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Utility function to print the array
void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    // Test arrays
    vector<vector<int>> testArrays = {
        {38, 27, 43, 3, 9, 82, 10},      // Random elements
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, // Already sorted
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // Reverse sorted
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5},  // All elements the same
        {}                               // Empty array
    };

    // Test merge sort on each array and print results
    for (size_t i = 0; i < testArrays.size(); i++) {
        cout << "Original Array " << i + 1 << ": ";
        printArray(testArrays[i]);

        mergeSort(testArrays[i], 0, testArrays[i].size() - 1);

        cout << "Sorted Array " << i + 1 << ": ";
        printArray(testArrays[i]);
        cout << endl;
    }

    return 0;
}
