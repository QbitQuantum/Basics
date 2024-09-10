void aranjare(float a[], int n) {
	int l = 0, i;
	for (i = 0; i < n; ++i)
		if (a[i] < 0)
			swap(&a[l++], &a[i]);
}