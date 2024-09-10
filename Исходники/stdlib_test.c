void stdlib_test(){
	ldiv_t ans;
	long N = 15;
	long D = 4;
	ans = ldiv(N,D);
	printf("%ld %ld",ans.quot,ans.rem);



}