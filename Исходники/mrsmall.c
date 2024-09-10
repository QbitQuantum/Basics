mr_small sqrmp(mr_small x,mr_small m)
{ /* square root mod a small prime by Shanks method  *
   * returns 0 if root does not exist or m not prime */
    mr_small z,y,v,w,t,q;
#ifdef MR_FP
    mr_small dres;
#endif
    int i,e,n,r;
    BOOL pp;
    x=MR_REMAIN(x,m);
    if (x==0) return 0;
    if (x==1) return 1;
    if (spmd(x,(mr_small)((m-1)/2),m)!=1) return 0;    /* Legendre symbol not 1   */
    if (MR_REMAIN(m,4)==3) return spmd(x,(mr_small)((m+1)/4),m);  /* easy case for m=4.k+3   */
    if (MR_REMAIN(m,8)==5)
    { /* also relatively easy */
        t=spmd(x,(mr_small)((m-1)/4),m);
        if (t==1) return spmd(x,(mr_small)((m+3)/8),m);
        if (t==(mr_small)(m-1))
        {
            muldiv((mr_small)4,x,(mr_small)0,m,&t);
            t=spmd(t,(mr_small)((m+3)/8),m);
            muldiv(t,(mr_small)((m+1)/2),(mr_small)0,m,&t);
            return t;
        }
        return 0;
    }
    q=m-1;
    e=0;
    while (MR_REMAIN(q,2)==0) 
    {
        q=MR_DIV(q,2);
        e++;
    }
    if (e==0) return 0;      /* even m */
    for (r=2;;r++)
    { /* find suitable z */
        z=spmd((mr_small)r,q,m);
        if (z==1) continue;
        t=z;
        pp=FALSE;
        for (i=1;i<e;i++)
        { /* check for composite m */
            if (t==(m-1)) pp=TRUE;
            muldiv(t,t,(mr_small)0,m,&t);
            if (t==1 && !pp) return 0;
        }
        if (t==(m-1)) break;
        if (!pp) return 0;   /* m is not prime */
    }
    y=z;
    r=e;
    v=spmd(x,(mr_small)((q+1)/2),m);
    w=spmd(x,q,m);
    while (w!=1)
    {
        t=w;
        for (n=0;t!=1;n++) muldiv(t,t,(mr_small)0,m,&t);
        if (n>=r) return 0;
        y=spmd(y,mr_shiftbits(1,r-n-1),m);
        muldiv(v,y,(mr_small)0,m,&v);
        muldiv(y,y,(mr_small)0,m,&y);
        muldiv(w,y,(mr_small)0,m,&w);
        r=n;
    }
    return v;
}