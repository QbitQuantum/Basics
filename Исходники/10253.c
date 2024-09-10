long long ch(long long a,long long b){
	if (a==1)return b;
	long long g,i;
	i=ceill(b/(double)a);
	a=a*i-b;
	b*=i;
	g=gcd(a,b);
	a/=g;
	b/=g;
	return ch(a,b);
}