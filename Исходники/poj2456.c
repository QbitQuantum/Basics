int main()
{
    int i,l,r,mid,ans;
    freopen("poj2456.txt","r",stdin);
    freopen("poj2456ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&pos[i]);
        QSort(1,n);
        l=0;
	r=pos[n]-pos[1]+1;   
        while (l<r)
        {
            mid=(l+r)/2;
            fprintf(stderr,"l=%d,r=%d,mid=%d\n",l,r,mid); 
            if (Check(mid)) 
            {
                ans=mid;
                l=mid+1;
                fprintf(stderr,"now ans : %d\n",ans); 
            }
            else r=mid;
        }
        printf("%d\n",ans);
    }
    return 0;
}