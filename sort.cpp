#include "DataGenerator.cpp"

void quickSortVerComp(int a[], int l, int r, long long &comp)
{
    int pivot = a[l + (r - l) / 2];
    int i = l, j = r;
    while (++comp && i <= j)
    {
        while (++comp && a[i] < pivot)
            i++;
        while (++comp && a[j] > pivot)
            j--;
        if (++comp && i <= j)
            swap(a[i++], a[j--]);
    }
    if (++comp && j > l)
        quickSortVerComp(a, l, j, comp);
    if (++comp && i < r)
        quickSortVerComp(a, i, r, comp);
}

void quickSort(int a[], int l, int r)
{
    int pivot = a[l + (r - l) / 2];
    int i = l, j = r;
    while (i <= j)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
            swap(a[i++], a[j--]);
    }
    if (j > l)
        quickSort(a, l, j);
    if (i < r)
        quickSort(a, i, r);
}

void quickSortVerTime(int a[], int l, int r, double &time)
{
    clock_t start, end;
    start = double(clock());
    quickSort(a, l, r);
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void mergeVerComp(int a[], int l, int r, long long &comp)
{
    int *b = new int[r - l + 1];
    int m = l + (r - l) / 2;
    int b_id = 0, l_id = l, r_id = m + 1;
    for (int i = l; ++comp && i <= r; i++)
    {
        if ((++comp && r_id > r) || ((++comp && l_id <= m) && (++comp && a[l_id] <= a[r_id])))
            b[b_id++] = a[l_id++];
        else
            b[b_id++] = a[r_id++];
    }
    for (int i = l; ++comp && i <= r; i++)
        a[i] = b[i - l];
    delete[] b;
}

void mergeSortVerComp(int a[], int l, int r, long long &comp)
{
    if (++comp && l < r)
    {
        int m = l + (r - l) / 2;
        mergeSortVerComp(a, l, m, comp);
        mergeSortVerComp(a, m + 1, r, comp);
        mergeVerComp(a, l, r, comp);
    }
}

void merge(int a[], int l, int r)
{
    int *b = new int[r - l + 1];
    int m = l + (r - l) / 2;
    int b_id = 0, l_id = l, r_id = m + 1;
    for (int i = l; i <= r; i++)
    {
        if (r_id > r || (l_id <= m && a[l_id] <= a[r_id]))
            b[b_id++] = a[l_id++];
        else
            b[b_id++] = a[r_id++];
    }
    for (int i = l; i <= r; i++)
        a[i] = b[i - l];
    delete[] b;
}

void mergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, r);
    }
}

void mergeSortVerTime(int a[], int l, int r, double &time)
{
    clock_t start, end;
    start = double(clock());
    mergeSort(a, l, r);
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void heapifyVerComp(int a[], int n, int k, long long &comp)
{
    int lc = 2 * k + 1, rc = 2 * k + 2;
    if (++comp && lc >= n)
        return;
    int maxc = lc;
    if ((++comp && rc < n) && (++comp && a[rc] > a[lc]))
        maxc = rc;
    if (++comp && a[maxc] > a[k])
    {
        swap(a[maxc], a[k]);
        heapifyVerComp(a, n, maxc, comp);
    }
}

void heapSortVerComp(int a[], int n, long long &comp)
{
    for (int i = (n - 1) / 2; ++comp && i >= 0; i--)
        heapifyVerComp(a, n, i, comp);
    int heapSize = n;
    while (++comp && heapSize)
    {
        swap(a[0], a[--heapSize]);
        heapifyVerComp(a, heapSize, 0, comp);
    }
}

void heapify(int a[], int n, int k)
{
    int lc = 2 * k + 1, rc = 2 * k + 2;
    if (lc >= n)
        return;
    int maxc = lc;
    if (rc < n && a[rc] > a[lc])
        maxc = rc;
    if (a[maxc] > a[k])
    {
        swap(a[maxc], a[k]);
        heapify(a, n, maxc);
    }
}

void heapSort(int a[], int n)
{
    for (int i = (n - 1) / 2; i >= 0; i--)
        heapify(a, n, i);
    int heapSize = n;
    while (heapSize)
    {
        swap(a[0], a[--heapSize]);
        heapify(a, heapSize, 0);
    }
}

void heapSortVerTime(int a[], int n, double &time)
{
    clock_t start, end;
    start = double(clock());
    heapSort(a, n);
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void flashSortVerComp(int a[], int n, long long &comp)
{
    int MAXid = 0, MIN = a[0];
    for (int i = 1; ++comp && i < n; i++)
    {
        if (++comp && a[MAXid] < a[i])
            MAXid = i;
        MIN = min(MIN, a[i]);
    }
    if (++comp && a[MAXid] == MIN)
        return;

    int m = 0.1 * n;
    int *bucket = new int[m]{};
    bucket[0] = -1;
    double coef = (m - 1.0) / (a[MAXid] - MIN);

    // count the number of elements in each bucket
    for (int i = 0; ++comp && i < n; i++)
    {
        int j = coef * (a[i] - MIN);
        bucket[j]++;
    }
    for (int i = 1; ++comp && i < m; i++)
        bucket[i] += bucket[i - 1];

    // put elements in their rightful buckets
    swap(a[0], a[MAXid]);
    for (int i = 0, j = 0, k = m - 1; ++comp && i < n;)
    {
        for (; ++comp && j > bucket[k];)
            k = coef * (a[++j] - MIN);
        int temp = a[j];
        for (; ++comp && j <= bucket[k]; i++)
        {
            k = coef * (temp - MIN);
            swap(temp, a[bucket[k]--]);
        }
    }

    // insertion sort
    for (int i = 0; i < n; i++)
        for (int j = i; ++comp && j > 0 && ++comp && a[j - 1] > a[j]; j--)
            swap(a[j], a[j - 1]);

    delete[] bucket;
}

void flashSortVerTime(int a[], int n, double &time)
{
    clock_t start, end;
    start = double(clock());

    int MAXid = 0, MIN = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[MAXid] < a[i])
            MAXid = i;
        MIN = min(MIN, a[i]);
    }
    if (a[MAXid] == MIN)
        return;

    int m = 0.1 * n;
    int *bucket = new int[m]{};
    bucket[0] = -1;
    double coef = (m - 1.0) / (a[MAXid] - MIN);

    // count the number of elements in each bucket
    for (int i = 0; i < n; i++)
    {
        int j = coef * (a[i] - MIN);
        bucket[j]++;
    }
    for (int i = 1; i < m; i++)
        bucket[i] += bucket[i - 1];

    // put elements in their rightful buckets
    swap(a[0], a[MAXid]);
    for (int i = 0, j = 0, k = m - 1; i < n;)
    {
        for (; j > bucket[k];)
            k = coef * (a[++j] - MIN);
        int temp = a[j];
        for (; j <= bucket[k]; i++)
        {
            k = coef * (temp - MIN);
            swap(temp, a[bucket[k]--]);
        }
    }

    // insertion sort
    for (int i = 0; i < n; i++)
        for (int j = i; j > 0 && a[j - 1] > a[j]; j--)
            swap(a[j], a[j - 1]);

    delete[] bucket;
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void bubbleSortVerComp(int arr[], int n, long long &comp)
{
    for (int i = 0; ++comp && i < n; i++)
    {
        bool flag = true;
        for (int j = n - 1; ++comp && j > i; j--)
        {
            if (++comp && arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
                flag = false;
            }
        }
        if (++comp && flag)
            break;
    }
}

void bubbleSortVerTime(int arr[], int n, double &time)
{
    clock_t start, end;
    start = double(clock());
    for (int i = 0; i < n; i++)
    {
        bool flag = true;
        for (int j = n - 1; j > i; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
                flag = false;
            }
        }
        if (flag)
            break;
    }
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void selectionSortVerComp(int arr[], int n, long long &comp)
{
    for (int i = 0; ++comp && i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; ++comp && j < n; j++)
        {
            if (++comp && arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (++comp && min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}

void selectionSortVerTime(int arr[], int n, double &time)
{
    clock_t start, end;
    start = double(clock());
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void insertionSortVerComp(int arr[], int n, long long &comp)
{
    for (int i = 1; ++comp && i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (++comp && j >= 0 && ++comp && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertionSortVerTime(int arr[], int n, double &time)
{
    clock_t start, end;
    start = double(clock());
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void shakerSortVerComp(int a[], int n, long long &comp)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (++comp && swapped)
    {
        swapped = false;
        for (int i = start; ++comp && i < end; ++i)
        {
            if (++comp && a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        if (++comp && !swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; ++comp && i >= start; --i)
        {
            if (++comp && a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

void shakerSortVerTime(int a[], int n, double &time)
{
    clock_t s, e;
    s = double(clock());

    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (swapped)
    {
        swapped = false;
        for (int i = start; i < end; ++i)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
    e = double(clock());
    time = (double(e) - double(s)) / double(CLOCKS_PER_SEC);
}

void countingSortVerComp(int a[], int n, long long &comp)
{
    int MAX = a[0];
    for (int i = 1; ++comp && i < n; i++)
        if (++comp && MAX < a[i])
            MAX = a[i];

    int *f = new int[MAX + 1];
    for (int i = 0; ++comp && i < MAX + 1; i++)
        f[i] = 0;

    for (int i = 0; ++comp && i < n; i++)
        f[a[i]]++;
    for (int i = 0, id = 0; ++comp && i <= MAX && ++comp && id < n; i++)
        while (++comp && f[i]-- > 0)
            a[id++] = i;
    delete[] f;
}

void countingSortVerTime(int a[], int n, double &time)
{
    clock_t start, end;
    start = double(clock());
    int MAX = a[0];
    for (int i = 1; i < n; i++)
        if (MAX < a[i])
            MAX = a[i];

    int *f = new int[MAX + 1];
    for (int i = 0; i < MAX + 1; i++)
        f[i] = 0;
    for (int i = 0; i < n; i++)
        f[a[i]]++;
    for (int i = 0, id = 0; i <= MAX && id < n; i++)
        while (f[i]-- > 0)
            a[id++] = i;
    delete[] f;
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void radixSortVerComp(int a[], int n, long long &comp)
{
    int MAX = a[0];
    for (int i = 1; ++comp && i < n; i++)
        if (MAX < a[i])
            MAX = a[i];

    for (int k = 1; ++comp && k <= MAX; k *= 10)
    {
        int f[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int *b = new int[n];
        for (int i = 0; ++comp && i < n; i++)
            b[i] = 0;
        for (int i = 0; ++comp && i < n; i++)
            f[a[i] / k % 10]++;
        for (int i = 1; ++comp && i <= 9; i++)
            f[i] += f[i - 1];
        for (int i = n - 1; ++comp && i >= 0; i--)
        {
            int j = a[i] / k % 10;
            b[f[j] - 1] = a[i];
            f[j]--;
        }
        for (int i = 0; ++comp && i < n; i++)
            a[i] = b[i];
        delete[] b;
    }
}

void radixSortVerTime(int a[], int n, double &time)
{
    clock_t start, end;
    start = double(clock());
    int MAX = a[0];
    for (int i = 1; i < n; i++)
        if (MAX < a[i])
            MAX = a[i];

    for (int k = 1; k <= MAX; k *= 10)
    {
        int f[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int *b = new int[n];
        for (int i = 0; i < n; i++)
            b[i] = 0;
        for (int i = 0; i < n; i++)
            f[a[i] / k % 10]++;
        for (int i = 1; i <= 9; i++)
            f[i] += f[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            int j = a[i] / k % 10;
            b[f[j] - 1] = a[i];
            f[j]--;
        }
        for (int i = 0; i < n; i++)
            a[i] = b[i];
        delete[] b;
    }
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}

void shellSortVerComp(int *arr, int n, long long &comp)
{
    for (int k = n / 2; ++comp && k > 0; k /= 2)
    {
        for (int i = k; ++comp && i < n; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; ++comp && j >= k && ++comp && arr[j - k] > temp; j -= k)
                arr[j] = arr[j - k];
            arr[j] = temp;
        }
    }
}

void shellSortVerTime(int *arr, int n, double &time)
{
    clock_t start, end;
    start = double(clock());
    for (int k = n / 2; k > 0; k /= 2)
    {
        for (int i = k; i < n; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= k && arr[j - k] > temp; j -= k)
                arr[j] = arr[j - k];
            arr[j] = temp;
        }
    }
    end = double(clock());
    time = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
}