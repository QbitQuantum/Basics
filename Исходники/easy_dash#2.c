int main()
{
    int t;
    scanf("%d",&t);
    long long a,b,x;
    while(t-->0)
    {
        scanf("%lld%lld",&a,&b);
        a=(long long)ceill(sqrt((double)a));
        b=(long long)(sqrt((double)a));
        x=b-a+1;
        printf("%lld\n",x);
    }
    return 0;
}