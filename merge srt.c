#include <stdio.h>

void merge(int a[], int l, int h, int m) {
    int c[100], i, j, k;
    i = l;
    j = m + 1;
    k = l;
    while (i <= m && j <= h) {
        if (a[i] < a[j]) {
            c[k++] = a[i++];
        } else {
            c[k++] = a[j++];
        }
    }
    while (i <= m) {
        c[k++] = a[i++];
    }
    while (j <= h) {
        c[k++] = a[j++];
    }
    for (i = l; i < k; i++) {
        a[i] = c[i];
    }
}

void mergesort(int a[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergesort(a, low, mid);
        mergesort(a, mid + 1, high);
        merge(a, low, high, mid);
    }
}

int main() {
    int i, n, a[100];
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    mergesort(a, 0, n - 1);
    printf("Elements in sorted order: ");
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}