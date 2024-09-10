void round(T arr[], size_t size){
	min = ULLONG_MAX;
	for (int i = 0; i < 10; i++){
		start = __rdtsc();

		for (int i = 0; i < size; i++){
			arr[i] = (arr[i] >= 0) ? (T)(int)(arr[i] + 0.5) : (T)(int)(arr[i] - 0.5);
		}

		finish = __rdtsc();
		if (finish - start < min){
			min = finish - start;
		}
	}
	printf("round#time for %d elements: %d\n", size, min);
}