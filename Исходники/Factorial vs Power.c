int main()
{
    long long int i,a,j;
    dpsum[1]=0;
    for(i=2;i<3000000;i++)
        dpsum[i]=dpsum[i-1]+logl(i);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld",&a);
        {
            j=pow(e,(logl(a)+1));
            //printf("Approx =%lld\n",j);
            double ss = dpsum[j]/log(a);
            while(ss>j)
            {
                j--;
                ss = dpsum[j]/log(a);
            }
        }
        printf("%lld\n",j+1);
    }
    return 0;
}