void
Qsort(int A[], int left, int right){
    int i,j;
    int pivot;

    if(left + 10 <= right){
        pivot = Median3(A,left,right);
        i = left;
        j = right - 1;
        for(;;){
            while(A[++i] < pivot){}
            while(A[--j] > pivot){}
            if(i < j){
                int t;
                t = A[i];
                A[i] = A[j];
                A[j] = t;
            }
            else break;
        }
        int t = A[i];
        A[i] = A[right - 1];
        A[right - 1] = t;
        
        Qsort(A,left,i - 1);
        Qsort(A,i + 1,right);
    }
    else
        select_sort(A + left, right - left + 1);
}