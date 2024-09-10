//快速排序
Qsort(int a[], int low, int high) {
	if (low < high) {
		int pk = Partition(a, low, high);
		Qsort(a, low, pk-1);
		Qsort(a, pk+1, high);
	}
}