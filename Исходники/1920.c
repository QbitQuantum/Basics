int main(void) {
	int i, num;
	scanf("%d", &n);
	for(i=0; i<n; i++) {
		scanf("%d", &arrN[i]);
	}
	qsort(arrN, n, sizeof(int), compare);
	scanf("%d", &m);
	for(i=0; i<m; i++) {
		scanf("%d", &num);
		printf("%d\n", (int)Bsearch(num, 0, n - 1));
	}
}