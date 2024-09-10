int main(){
	int primeMap[1001], count, *primeList, N, C, idx, st, ed, mid;
	count = getPrimeMap(primeMap);
	primeList = (int*)calloc(count, sizeof(int));
	getPrimeList(primeMap, primeList);
	while(scanf("%d %d", &N, &C) != EOF){
		idx = bSearch(primeList, count, N);
		if((idx+1)%2 == 1){
			mid = idx>>1;
			st = mid-C+1>=0?mid-C+1:0;
			ed = mid+C-1<=idx?mid+C-1:idx;
		}
		else{