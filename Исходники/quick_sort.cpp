void my_qsort(int * arr, int l, int r) {
	if (l >= r)
	    return;
	
	int pivot = rand() % (r - l) + l;
	int j = partition(arr, l, r, pivot);
	my_qsort(arr, l, j);
	my_qsort(arr, j + 1, r);
}