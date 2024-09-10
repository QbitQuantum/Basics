int main(){

    FRO

    input.grabBuffer();

    int kase;
    kase=input.rInt();

    for ( int kk=1;kase--;++kk ){


        n=input.rInt();
        m=input.rInt();

        for (int i=0;i<n;++i){
            win[i].X=input.rInt();
            win[i].Y=input.rInt();
        }
        for (int i=0;i<m;++i){
            ans[i].ind=input.rInt();
            ans[i].num= i;
            ans[i].ans = 0;
        }


        sort( win,win+n, sss );

        cnt = 0;
        int lim = win[0].Y;
        mm[ cnt++ ] = win[0];
        for (int i=0;i<n;++i){
            if ( win[i].Y > lim ){
                mm[ cnt++ ] = win[i];
                lim=win[i].Y;
            }
        }

        sort( ans,ans+m  , cmp );

        //cout<<score( 1,9 )<<endl;


        int le = 0,save;
        for (int i=0;i<m;){
            //cout<<le<<' '<<i<<' '<<score( le,ans[i].ind )<<endl;
            save=score( le,ans[i].ind );
            if (  save == 0 ){
                if ( mm[le].Y < ans[i].ind && le+1<cnt ){
                    le++;
                    continue;
                }
            }

            if ( score( le+1,ans[i].ind ) > save ){
                le++;
            }else{
                ans[ i ].ans = save;
                //cout<<ans[i].ind<<' '<<ans[i].ans<<' '<<le<<endl;;
                i++;
            }

        }

        sort( ans,ans+m, ccc  );
        output.print("Case ");
        output.print(kk);
        output.print(":\n");
        //printf("Case %d:\n",kk);
        for (int i=0;i<m;++i){
            //printf("%d\n",ans[i].ans);
            output.print(ans[i].ans);
            output.print('\n');
        }
    }


    output.flushBuffer();

    return 0;
}