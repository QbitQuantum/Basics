int __kernel_rem_pio2f(float *x, float *y, int e0, int nx, int prec, const __int32_t *ipio2)
{
    __int32_t jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
    float z,fw,f[20],fq[20],q[20];

    /* initialize jk*/
    jk = init_jk[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx-1;
    jv = (e0-3)/8;
    if(jv<0) jv=0;
    q0 =  e0-8*(jv+1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv-jx;
    m = jx+jk;
    for(i=0; i<=m; i++,j++) f[i] = (j<0)? zero : (float) ipio2[j];

    /* compute q[0],q[1],...q[jk] */
    for (i=0; i<=jk; i++) {
        for(j=0,fw=0.0; j<=jx; j++) fw += x[j]*f[jx+i-j];
        q[i] = fw;
    }

    jz = jk;
recompute:
    /* distill q[] into iq[] reversingly */
    for(i=0,j=jz,z=q[jz]; j>0; i++,j--) {
        fw    =  (float)((__int32_t)(twon8* z));
        iq[i] =  (__int32_t)(z-two8*fw);
        z     =  q[j-1]+fw;
    }

    /* compute n */
    z  = scalbnf(z,(int)q0);	/* actual value of z */
    z -= (float)8.0*floorf(z*(float)0.125);	/* trim off integer >= 8 */
    n  = (__int32_t) z;
    z -= (float)n;
    ih = 0;
    if(q0>0) {	/* need iq[jz-1] to determine n */
        i  = (iq[jz-1]>>(8-q0));
        n += i;
        iq[jz-1] -= i<<(8-q0);
        ih = iq[jz-1]>>(7-q0);
    }