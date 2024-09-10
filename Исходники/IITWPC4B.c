int main(){
	int t, n; //(1 <= T <= 10^5)   (n >= 1 && n <= 10^9)
	fast_scani(&t);
	while(t--){
		fast_scani(&n);
		if((n&1)){
			// faster than 	printf("%.Lf\n", roundl(1.0l*(n+3)*(n+3)/48.0));
			printf("%lld\n", (unsigned long long)roundl(1.0l*(n+3)*(n+3)/48.0));
		}
		else{
			printf("%lld\n", (unsigned long long)roundl(1.0l*n*n/48.0));			
		}
	}
	return 0;
}