double sequentialMultiply(int start, int end) {
	double result;
	if(start == end)
		return (double)start;
	if(start > end)
		return (double)nan("");
	result = (double)start++;
	while(start <= end){
		result *= start;
		start++;
	}
	return result;
}