int Rsimp(int m, int n, double **A, double *b, double *c,
          double *x, int *basis, int *nonbasis,
          double **R, double **Q, double *t1, double *t2){
    int i,j,k,l,q,qv;
    int max_steps=20;
    double r,a,at;
    void GQR(int,int,double**,double**);
    max_steps=4*n;

    for(k=0; k<=max_steps;k++){
        /*
   ++ Step 0) load new basis matrix and factor it
   */
        for(i=0;i<m;i++)for(j=0;j<m;j++)R0(i,j)=AB0(i,j);
        GQR(m,m,Q,R);

        /*
   ++ Step 1) solving system  B'*w=c(basis)
   ++      a) forward solve R'*y=c(basis)
   */
        for(i=0;i<m;i++){
            Y0(i)=0.0;
            for(j=0;j<i;j++)Y0(i)+=R0(j,i)*Y0(j);
            if (R0(i,i)!=0.0) Y0(i)=(CB0(i)-Y0(i))/R0(i,i);
            else {
                printf("Warning Singular Matrix Found\n");
                return LP_FAIL;
            }
        }
        /*
   ++      b) find w=Q*y
   ++         note: B'*w=(Q*R)'*Q*y= R'*(Q'*Q)*y=R'*y=c(basis)
   */
        for(i=0;i<m;i++){
            W0(i)=0.0;
            for(j=0;j<m;j++)W0(i)+=Q0(i,j)*Y0(j);
        }

        /*
   ++ Step 2)find entering variable,
   ++ (use lexicographically first variable with negative reduced cost)
   */
        q=n;
        for(i=0;i<n-m;i++){
            /* calculate reduced cost */
            r=CN0(i);
            for(j=0;j<m;j++) r-=W0(j)*AN0(j,i);
            if (r<-zero_tol && (q==n || nonbasis0(i)<nonbasis0(q))) q=i;
        }

        /*
   ++ if ratios were all nonnegative current solution is optimal
   */
        if (q==n){
            if (verbose>0) printf("optimal solution found in %d iterations\n",k);
            return LP_OPT;
        }
        /*
   ++ Step 3)Calculate translation direction for q entering
   ++        by solving system  B*d=-A(:,nonbasis(q));
   ++   a) let y=-Q'*A(:,nonbasis(q));
   */
        for(i=0;i<m;i++){
            Y0(i)=0.0;
            for(j=0;j<m;j++) Y0(i)-=Q0(j,i)*AN0(j,q);
        }

        /*
   ++  b) back solve Rd=y  (d=R\y)
   ++     note B*d= Q*R*d=Q*y=Q*-Q'*A(:nonbasis(q))=-A(:,nonbasis(q))
   */
        for(i=m-1;i>=0;i--){
            D0(i)=0.0;
            for(j=m-1;j>=i+1;j--)D0(i)+=R0(i,j)*D0(j);
            if (R0(i,i)!=0.0) D0(i)=(Y0(i)-D0(i))/R0(i,i);
            else {
                printf("Warning Singular Matrix Found\n");
                return LP_FAIL;
            }
        }
        /*
   ++ Step 4 Choose leaving variable
   ++     (first variable to become negative, by moving in direction D)
   ++     (if none become negative, then objective function unbounded)
   */
        a=0;
        l=-1;
        for(i=0;i<m;i++){
            if (D0(i)<-zero_tol){
                at=-1*XB0(i)/D0(i);
                if (l==-1 || at<a){ a=at; l=i;}
            }
        }
        if (l==-1){
            if (verbose>0){
                printf("Objective function Unbounded (%d iterations)\n",k);
            }
            return LP_UNBD;
        }
        /*
   ++ Step 5) Update solution and basis data
   */
        XN0(q)=a;
        for(j=0;j<m;j++) XB0(j)+=a*D0(j);
        XB0(l)=0.0;             /* enforce strict zeroness of nonbasis variables */
        qv=nonbasis0(q);
        nonbasis0(q)=basis0(l);
        basis0(l)=qv;
    }
    if (verbose>=0){
        printf("Simplex Algorithm did not Terminate in %d iterations\n",k);
    }
    return LP_FAIL;
}