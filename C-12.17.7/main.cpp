#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left);
    int i = left, j = mid, k = 0;

    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while (i < mid) temp[k++] = arr[i++];
    while (j < right) temp[k++] = arr[j++];

    for (int l = 0; l < temp.size(); ++l)
        arr[left + l] = temp[l];
}

void merge_sort(vector<int>& arr) {
    int n = arr.size();

    // Step sizes: 1, 2, 4, 8, ...
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size;
            int right = min(left + 2 * size, n);
            merge(arr, left, mid, right);
        }
    }
}

int main() {
    vector<int> data = {5, 2, 9, 1, 5, 6, 3, 8, 7, 4};

    cout << "Before sort: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    merge_sort(data);

    cout << "After sort: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    return 0;
}