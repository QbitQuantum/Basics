int main() {
	int Low, High;
	int Array[] = {6, 7, 3, 8, 10, 9, 1, 4, 5, 2};
	Low = 0;
	High= 9;
	Qsort(Array, Low, High);
	for (int i = 0; i < 10; ++i) {
		printf("%d ", Array[i]);
	}
	return 0;
}