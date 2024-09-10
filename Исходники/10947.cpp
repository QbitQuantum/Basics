int main(){

    freopen("in.txt","r",stdin);

    input.grabBuffer();

    int m,k;
    while (!input.bufEof() ){

        m=input.rInt();
        k=input.rInt();


        memset(vis,false,sizeof( vis) );
        memset(dp,-1,sizeof( dp ) );

        capacity=m*k;

        island[0].x=input.rInt();
        island[0].y=input.rInt();
        island[0].r=input.rInt();
        island[1].x=input.rInt();
        island[1].y=input.rInt();
        island[1].r=input.rInt();

        total=input.rInt();

        for (int i=0;i<total;++i){
            island[i+2].x=input.rInt();
            island[i+2].y=input.rInt();
            island[i+2].r=input.rInt();
        }
        total+=2;

        //printf("%d\n",checkDistance( 0 , 1 ) );

        DFS( 0 );
        if (vis[1])
            output.print("Larry and Ryan will escape!\n");
        else
            output.print("Larry and Ryan will be eaten to death.\n");

    }
    output.flushBuffer();
    return 0;

}