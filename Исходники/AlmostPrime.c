int main()
{
unsigned long long int num,n,i,count,temp;
SCAN("%llu",&num);
while(num--)
{
	SCAN("%llu",&n);
	temp=S(n);
	count=temp*temp;
	count==n?(prime(temp)?PRINT("YES\n"):PRINT("NO\n")):PRINT("NO\n");
}
return 0;
}