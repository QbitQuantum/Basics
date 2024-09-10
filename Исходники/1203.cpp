int main(){

    freopen("in.txt","r",stdin);

    input.grabBuffer();



    int kase;
    kase=input.rInt();
    int n;
    double PI=acos(-1);

    for (int kk=1;kase--;++kk){

        n=input.rInt();



        for (int i=0;i<n;++i){
            points[i].x=input.rInt();
            points[i].y=input.rInt();
        }

        if ( n< 3 ){
            printf("Case %d: %.7lf\n",kk,double(0));
            continue;
        }

        int m=convexHull(points,convexPoints,n);
        //cout<<m<<endl;
        /*
        for (int i=0;i<m;++i){
            cout<<points[i].x<<" "<<points[i].y<<endl;
        }
        */
        if ( m< 3 ){
            printf("Case %d: %.7lf\n",kk,double(0) );
            continue;
        }

        double deg= degree( convexPoints[m-1]-convexPoints[0] ,convexPoints[1]- convexPoints[0] )   ;
        //cout<<deg*180/PI<<endl;
        //continue;
        for (int i=1;i<=m;++i){
            deg=min( deg, degree( convexPoints[i-1]-convexPoints[i] ,convexPoints[ (i+1)%m ]- convexPoints[i] )  );
            //cout<<i<<" "<<deg*180/PI<<endl;
        }
        printf("Case %d: %.7lf\n",kk,deg*180/PI);

    }
    return 0;

}