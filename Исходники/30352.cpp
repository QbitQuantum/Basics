void get_graph(int N,int M){
    ne = 2;
    memset(head, 0, sizeof(head));
	int i,j,u,v,w,px,py;
     nn1=(N+1)*(M+1);
    scr1=1;sink1=nn1;vn1=nn1+(N*M);
    //½¨Í¼
    for(i=1;i<=N+1;i++)
    {
        for(j=1;j<=M;j++)
        {
            w=Scan();
            u=(i-1)*(M+1)+j;
            v=u+1;
            Insert(u,v,w);
            //Insert(v,u,w);
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M+1;j++)
        {
            //scanf("%d",&w);
            w=Scan();
            u=(i-1)*(M+1)+j;
            v=u+M+1;
            Insert(u,v,w);
            //Insert(v,u,w);
        }
    }
    for(i=1;i<=2*N;i++)
    {
        for(j=1;j<=2*M;j++)
        {
            //scanf("%d",&w);
            w=Scan();
            px=(i+1)>>1;
            py=(j+1)>>1;
            v=(px-1)*M+py+nn1;
            u=(px-1)*(M+1)+py;
            if((i%2)&&(j%2==0)) u++;
            else if((i%2==0)&&(j%2)) u+=(M+1);
            else if((i%2==0)&&(j%2==0)) u+=(M+2);
            Insert(u,v,w);
            //Insert(v,u,w);
        }
    }
}