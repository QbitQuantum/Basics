void QSort(int array[], int low, int high)
{
    if(low <high)
    {
        int pivot = partition(array, low, high); // 分割

        QSort(array, low, pivot-1);
        QSort(array, pivot+1, high);
    }
}