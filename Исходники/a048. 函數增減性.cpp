main() {
	int N, Q, v, L, R, i; 
	int a, b; 

	for(a = 1; a <= 200000; a++) 
		lb[a] = a & -a;
	scanf("%d %d", &N, &Q);
	while(Q--) {
		v = Input(); 
		if(v == 1) {
			i = Input(); 
			if(A[i] == 0) Modify(i, 1);
			else Modify(i, -1); 
		} 
		else {
			L = Input(), R = Input(); 
			b = Operator(R) - Operator(L-1); 
			if(b&1) puts("1");
			else puts("0"); 
		}	
	} 
	return 0; 
}