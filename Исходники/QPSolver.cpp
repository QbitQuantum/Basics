void simpleQPSolve(Matrix G, Vector vd, Matrix Astar, Vector vBstar,   // in
                   Vector vXtmp, Vector vLambda)                       // out
{
    Astar.setNLine(Astar.nLine()+1);
    Matrix thisG, At=Astar.transpose();
    Astar.setNLine(Astar.nLine()-1);
    Vector minusvd=vd.clone();
    minusvd.multiply(-1.0); vBstar.multiply(-1.0);
    int m=Astar.nLine(), me=0, mmax=Astar.nLine()+1, n=vd.sz(), nmax=n,
        mnn=m+n+n, iout=0, ifail, iprint=0, lwar=3*nmax*nmax/2 + 10*nmax+ 2*mmax+1,
        liwar=n;
    if (G==Matrix::emptyMatrix) { 
        thisG.setSize(n,n); thisG.diagonal(1.0); }
    else thisG=G;
    double *c=*((double**)thisG), *d=minusvd, *a=*((double**)At), *b=vBstar; 
    Vector vxl(n),vxu(n), temp(lwar);
    VectorInt itemp(liwar);
    vLambda.setSize(mnn);
    double *xl=vxl, *xu=vxu, *x=vXtmp, *u=vLambda, *war=temp, eps1=1e-20;
    int *iwar=itemp;

    int dim=n; while (dim--) { xl[dim]=-INF; xu[dim]=INF; }
    iwar[0]=0;

    ql0001_(&m,&me,&mmax,&n,&nmax,&mnn,c,d,a,b,xl,xu,x,u,&iout,&ifail,
            &iprint,war,&lwar,iwar,&liwar,&eps1);

    vLambda.setSize(m);
}