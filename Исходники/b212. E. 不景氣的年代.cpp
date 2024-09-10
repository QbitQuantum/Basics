main() {
	int k, n, a, b;
	for(a = 0; a < 10002; a++)	LOW[a] = a & (-a);
	scanf("%d", &k);
	while(k--) {
		scanf("%d", &n);
		for(a = 0; a < n; a++)
			scanf("%d %d %d", &A[a].a, &A[a].b, &A[a].c), 
			B[a].a = A[a].b, B[a].b = A[a].a, B[a].c = A[a].c;
		MergeSort(0, n-1, A), MergeSort(0, n-1, B);
		int Pa, Pb, Pc, t, Ans = 0;
		for(a = 0; a < n; ) {
			Pa = A[a].a;
			while(a < n && A[a].a <= Pa)	a++;
			memset(C, 0, (10000-Pa+2)*4);
			for(b = 0; b < n && Pa+B[b].a <= 10000; ) {
				Pb = B[b].a, Pc = 10000-Pa-Pb+1;
				while(b < n && B[b].a <= Pb) {
					if(B[b].b <= Pa)	Modify(B[b].c+1, Pc);
					b++;
				}
				t = Operator(Pc);
				Ans = Ans > t ? Ans : t;
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}