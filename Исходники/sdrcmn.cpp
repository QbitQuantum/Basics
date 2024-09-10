/* mix local carrier -----------------------------------------------------------
* mix local carrier to data
* args   : char   *data     I   data
*          int    dtype     I   data type (0:real,1:complex)
*          double ti        I   sampling interval (s)
*          int    n         I   number of samples
*          double freq      I   carrier frequency (Hz)
*          double phi0      I   initial phase (rad)
*          short  *I,*Q     O   carrier mixed data I, Q component
* return : double               phase remainder
*-----------------------------------------------------------------------------*/
extern double mixcarr(const char *data, int dtype, double ti, int n, 
                      double freq, double phi0, short *II, short *QQ)
{
    const char *p;
    double phi,ps,prem;

#if !defined(SSE2_ENABLE)
    static short cost[CDIV]={0},sint[CDIV]={0};
    int i,index;

    /* initialize local carrier table */
    if (!cost[0]) { 
        for (i=0;i<CDIV;i++) {
            cost[i]=(short)floor((cos(DPI/CDIV*i)/CSCALE+0.5));
            sint[i]=(short)floor((sin(DPI/CDIV*i)/CSCALE+0.5));
        }
    }
    phi=phi0*CDIV/DPI;
    ps=freq*CDIV*ti; /* phase step */

    if (dtype==DTYPEIQ) { /* complex */
        for (p=data;p<data+n*2;p+=2,II++,QQ++,phi+=ps) {
            index=((int)phi)&CMASK;
            *II=cost[index]*p[0]-sint[index]*p[1];
            *QQ=sint[index]*p[0]+cost[index]*p[1];
        }
    }
    if (dtype==DTYPEI) { /* real */
        for (p=data;p<data+n;p++,II++,QQ++,phi+=ps) {
            index=((int)phi)&CMASK;
            *II=cost[index]*p[0];
            *QQ=sint[index]*p[0];
        }
    }
    prem=phi*DPI/CDIV;
    while(prem>DPI) prem-=DPI;
    return prem;
#else
    static char cost[16]={0},sint[16]={0};
    short I1[16]={0},I2[16]={0},Q1[16]={0},Q2[16]={0};
    int i;
    __m128d xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8,xmm9;
    __m128i dat1,dat2,dat3,dat4,ind1,ind2,xcos,xsin;
    __m128i zero=_mm_setzero_si128();
    __m128i mask4=_mm_set1_epi32(15);
    __m128i mask8=_mm_set1_epi16(255);

    if (!cost[0]) {
        for (i=0;i<16;i++) {
            cost[i]=(char)floor((cos(DPI/16*i)/CSCALE+0.5));
            sint[i]=(char)floor((sin(DPI/16*i)/CSCALE+0.5));
        }
    }
    phi=phi0/DPI*16-floor(phi0/DPI)*16;
    ps=freq*16*ti;
    xmm1=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm2=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm3=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm4=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm5=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm6=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm7=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm8=_mm_set_pd(phi+ps,phi); phi+=ps*2;
    xmm9=_mm_set1_pd(ps*16);
    xcos=_mm_loadu_si128((__m128i *)cost);
    xsin=_mm_loadu_si128((__m128i *)sint);

    if (dtype==DTYPEIQ) { /* complex */
        for (p=data;p<data+n*2;p+=32,II+=16,QQ+=16) {
            LOAD_INT8C(dat1,dat2,p   ,zero,mask8);
            LOAD_INT8C(dat3,dat4,p+16,zero,mask8);

            DBLTOINT16(ind1,xmm1,xmm2,xmm3,xmm4,mask4);
            DBLTOINT16(ind2,xmm5,xmm6,xmm7,xmm8,mask4);
            ind1=_mm_packus_epi16(ind1,ind2);
            MIX_INT8(I1,dat1,dat3,xcos,ind1,zero);
            MIX_INT8(I2,dat1,dat3,xsin,ind1,zero);
            MIX_INT8(Q1,dat2,dat4,xsin,ind1,zero);
            MIX_INT8(Q2,dat2,dat4,xcos,ind1,zero);
            for (i=0;i<16;i++) {
                II[i]=I1[i]-Q1[i];
                QQ[i]=I2[i]+Q2[i];
            }
            xmm1=_mm_add_pd(xmm1,xmm9);
            xmm2=_mm_add_pd(xmm2,xmm9);
            xmm3=_mm_add_pd(xmm3,xmm9);
            xmm4=_mm_add_pd(xmm4,xmm9);
            xmm5=_mm_add_pd(xmm5,xmm9);
            xmm6=_mm_add_pd(xmm6,xmm9);
            xmm7=_mm_add_pd(xmm7,xmm9);
            xmm8=_mm_add_pd(xmm8,xmm9);
        }
    }
    if (dtype==DTYPEI) { /* real */
        for (p=data;p<data+n;p+=16,II+=16,QQ+=16) {
            LOAD_INT8(dat1,dat2,p,zero);

            DBLTOINT16(ind1,xmm1,xmm2,xmm3,xmm4,mask4);
            DBLTOINT16(ind2,xmm5,xmm6,xmm7,xmm8,mask4);
            ind1=_mm_packus_epi16(ind1,ind2);
            MIX_INT8(II,dat1,dat2,xcos,ind1,zero);
            MIX_INT8(QQ,dat1,dat2,xsin,ind1,zero);
            xmm1=_mm_add_pd(xmm1,xmm9);
            xmm2=_mm_add_pd(xmm2,xmm9);
            xmm3=_mm_add_pd(xmm3,xmm9);
            xmm4=_mm_add_pd(xmm4,xmm9);
            xmm5=_mm_add_pd(xmm5,xmm9);
            xmm6=_mm_add_pd(xmm6,xmm9);
            xmm7=_mm_add_pd(xmm7,xmm9);
            xmm8=_mm_add_pd(xmm8,xmm9);
        }
    }
    prem=phi0+freq*ti*n*DPI;
    while(prem>DPI) prem-=DPI;
    return prem;
#endif
}