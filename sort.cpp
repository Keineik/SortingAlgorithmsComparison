#include "DataGenerator.cpp"

void quickSortVerComp(int a[], int l, int r, long long &comp) {
    int pivot = a[l + (r - l)/2];
    int i = l, j = r;
    while (++comp && i <= j){
        while (++comp && a[i] < pivot) i++;
        while (++comp && a[j] > pivot) j--;
        if (++comp && i <= j) swap(a[i++], a[j--]);
    }
    if (++comp && j > l) quickSortVerComp(a, l, j, comp);
    if (++comp && i < r) quickSortVerComp(a, i, r, comp);
}

void quickSort(int a[], int l, int r) {
    int pivot = a[l + (r - l)/2];
    int i = l, j = r;
    while (i <= j){
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) swap(a[i++], a[j--]);
    }
    if (j > l) quickSort(a, l, j);
    if (i < r) quickSort(a, i, r);
}

void quickSortVerTime(int a[], int l, int r, double &time){
    clock_t start, end;
    start = double(clock());
    quickSort(a, l, r);
    end = double(clock());
    time = (double(end) - double(start))/double(CLOCKS_PER_SEC); 
}

void mergeVerComp(int a[], int l, int r, long long &comp) {
    int *b = new int[r - l + 1];
    int m = l + (r - l)/2;
    int b_id = 0, l_id = l, r_id = m + 1;
    for (int i = l; i <= r; i++) {
        if ((++comp && r_id > r) || ( (++comp && l_id <= m) && (++comp && a[l_id] <= a[r_id])))
            b[b_id++] = a[l_id++];
        else 
            b[b_id++] = a[r_id++];
    }
    for (int i = l; i <= r; i++) a[i] = b[i - l];
    delete[] b;
}

void mergeSortVerComp(int a[], int l, int r, long long &comp) {
    if (++comp && l < r) {
        int m = l + (r - l)/2;
        mergeSortVerComp(a, l, m, comp);
        mergeSortVerComp(a, m + 1, r, comp);
        mergeVerComp(a, l, r, comp);
    }
}

void merge(int a[], int l, int r) {
    int *b = new int[r - l + 1];
    int m = l + (r - l)/2;
    int b_id = 0, l_id = l, r_id = m + 1;
    for (int i = l; i <= r; i++) {
        if (r_id > r || (l_id <= m && a[l_id] <= a[r_id]))
            b[b_id++] = a[l_id++];
        else 
            b[b_id++] = a[r_id++];
    }
    for (int i = l; i <= r; i++) a[i] = b[i - l];
    delete[] b;
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l)/2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, r);
    }
}

void mergeSortVerTime(int a[], int l, int r, double &time){
    clock_t start, end;
    start = double(clock());
    mergeSort(a, l, r);
    end = double(clock());
    time = (double(end) - double(start))/double(CLOCKS_PER_SEC); 
}

void heapifyVerComp(int a[], int n, int k, long long &comp) {
    int lc = 2*k + 1, rc = 2*k + 2;
    if (++comp && lc >= n) return;
    int maxc = lc;
    if ((++comp && rc < n) && (++comp && a[rc] > a[lc])) maxc = rc;
    if (++comp && a[maxc] > a[k]) {
        swap(a[maxc], a[k]);
        heapifyVerComp(a, n, maxc, comp);
    }
}

void heapSortVerComp(int a[], int n, long long &comp) {
    for (int i = (n - 1)/2; i >= 0; i--)
        heapifyVerComp(a, n, i, comp);
    int heapSize = n;
    while (++comp && heapSize) {
        swap(a[0], a[--heapSize]);
        heapifyVerComp(a, heapSize, 0, comp);
    }
}

void heapify(int a[], int n, int k) {
    int lc = 2*k + 1, rc = 2*k + 2;
    if (lc >= n) return;
    int maxc = lc;
    if (rc < n && a[rc] > a[lc]) maxc = rc;
    if (a[maxc] > a[k]) {
        swap(a[maxc], a[k]);
        heapify(a, n, maxc);
    }
}

void heapSort(int a[], int n) {
    for (int i = (n - 1)/2; i >= 0; i--)
        heapify(a, n, i);
    int heapSize = n;
    while (heapSize) {
        swap(a[0], a[--heapSize]);
        heapify(a, heapSize, 0);
    }
}

void heapSortVerTime(int a[], int n, double &time){
    clock_t start, end;
    start = double(clock());
    heapSort(a, n);
    end = double(clock());
    time = (double(end) - double(start))/double(CLOCKS_PER_SEC);
}

void flashSortVerComp(int a[], int n, long long &comp) {
    int MAXid = 0, MIN = a[0];
    for (int i = 1; i < n; i++) {
        if (++comp && a[MAXid] < a[i]) MAXid = i;
        MIN = min(MIN, a[i]);
    }
    if (++comp && a[MAXid] == MIN) return;

    int m = 0.1*n;
    int *bucket = new int[m] {};
    double coef = (m - 1.0)/(a[MAXid] - MIN);

    // count the number of elements in each bucket
    for (int i = 0; i < n; i++) {
        int j = coef*(a[i] - MIN);
        bucket[j]++;
    }
    for (int i = 1; i < m; i++) bucket[i] += bucket[i - 1];

    // put elements in their rightful buckets
    swap(a[0], a[MAXid]);
    for (int i = 0, j = 0, k = m - 1; i < n;) {
        for (; j > bucket[k];) k = coef*(a[++j] - MIN);
        int temp = a[j];
        for (;++comp && j <= bucket[k]; i++) {
            k = coef*(temp - MIN);
            swap(temp, a[bucket[k]--]);
        }
    }

    // insertion sort
    for (int i = 0; i < n; i++)
        for (int j = i; ++comp && j > 0 && a[j - 1] > a[j]; j--)
            swap(a[j], a[j - 1]);
    
    delete[] bucket;
}

void flashSortVerTime(int a[], int n, double &time) {
    clock_t start, end; 
    start = double(clock());

    int MAXid = 0, MIN = a[0];
    for (int i = 1; i < n; i++) {
        if (a[MAXid] < a[i]) MAXid = i;
        MIN = min(MIN, a[i]);
    }
    if (a[MAXid] == MIN) return;

    int m = 0.1*n;
    int *bucket = new int[m] {};
    double coef = (m - 1.0)/(a[MAXid] - MIN);

    // count the number of elements in each bucket
    for (int i = 0; i < n; i++) {
        int j = coef*(a[i] - MIN);
        bucket[j]++;
    }
    for (int i = 1; i < m; i++) bucket[i] += bucket[i - 1];

    // put elements in their rightful buckets
    swap(a[0], a[MAXid]);
    for (int i = 0, j = 0, k = m - 1; i < n;) {
        for (; j > bucket[k];) k = coef*(a[++j] - MIN);
        int temp = a[j];
        for (; j <= bucket[k]; i++) {
            k = coef*(temp - MIN);
            swap(temp, a[bucket[k]--]);
        }
    }

    // insertion sort
    for (int i = 0; i < n; i++)
        for (int j = i; j > 0 && a[j - 1] > a[j]; j--)
            swap(a[j], a[j - 1]);
    
    delete[] bucket;
    end = double(clock());
    time = (double(end) - double(start))/double(CLOCKS_PER_SEC);
}