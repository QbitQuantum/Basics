int main(){

    //freopen("in.txt","r",stdin);

    input.grabBuffer();

    int a,b,c,m,k;


    while (true){
        n=input.rInt();

        if ( !n )return 0;

        m=input.rInt();

        for (int i=1;i<=n;++i)
            G[i].clear();


        k=input.rInt();

        while(k--){
            a=input.rInt();
            b=input.rInt();
            c=input.rInt();
            G[b].push_back(n+c);

        }
        printf("%d\n",hopcroft_karp());

    }
    return 0;

}