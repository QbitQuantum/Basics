int main(){

    FRO

    input.grabBuffer();

    int kase;
    kase=input.rInt();

    for (int kk=1;kase--;++kk){

        output.print("Case ");
        output.print(kk);
        output.print(":\n");
        //printf("Case %d:\n",kk);

        int n,m,ss;
        n=input.rInt();
        m=input.rInt();
        ss=input.rInt();

        for (int i=0;i<=n;++i){
            out[i].clear();
        }
        w.clear();
        qq.clear();

        int u,v,tmp;
        for (int i=0;i<m;++i){
            u=input.rInt();
            v=input.rInt();
            tmp=input.rInt();

            out[u].PB( v );
            out[v].PB( u );

            qq.PB( make_pair( u,v ) );

            cost[ u ][ v ] =cost[ v ][ u ] = 0;

            w.PB( tmp );
        }

        sort( w.begin(),w.end() );


        cnt = 0;
        bfs(ss);

        for (int i=0;i<m;++i){

            output.print(qq[i].first);;
            output.print(' ');
            output.print(qq[i].second);
            output.print(' ');
            if ( cost[ qq[i].first ][ qq[i].second ] == 0 ){
                output.print(w[cnt++]);
            }else{
                output.print(cost[ qq[i].first ][ qq[i].second ]);
            }
            output.print('\n');
        }
    }

    output.flushBuffer();


    return 0;
}