Ps_Big operator*(Ps_Big& a,Ps_Big& b)
{
    Ps_Big prod;
    Big t;
    term_ps_big *aptr,*bptr,*pos;
    int ka,kb,i,pa,pb,d,deg,g;

    if (a.IsInt())
    {
        if (a.start==NULL) return prod;
        else return (a.start->an*b);
    }

    if (b.IsInt())
    {
        if (b.start==NULL) return prod;
        else return (b.start->an*a);
    }

    g=igcd(a.pwr,b.pwr);

    deg=psN/g;

#ifdef FFT
    if (deg>=FFT_BREAK_EVEN)
    { // use fast methods
        big *A,*B,*C;
        A=(big *)mr_alloc(deg,sizeof(big));
        B=(big *)mr_alloc(deg,sizeof(big));
        C=(big *)mr_alloc(deg,sizeof(big));
        char *memc=(char *)memalloc(deg);
        for (i=0;i<deg;i++) C[i]=mirvar_mem(memc,i);
       
        ka=a.pwr/g;
        a.decompress(ka);

        aptr=a.start;
        while (aptr!=NULL)
        {
            d=aptr->n;
            if (d >= deg) break;
            A[d]=(aptr->an).getbig();
            aptr=aptr->next;
        }
        kb=b.pwr/g;
        b.decompress(kb);
        bptr=b.start;
        while (bptr!=NULL)
        {
            d=bptr->n;
            if (d >= deg) break;
            B[d]=(bptr->an).getbig();
            bptr=bptr->next;
        }
        mr_ps_big_mul(deg,A,B,C);
        pos=NULL;
        for (d=0;d<deg;d++)
        {
            t=C[d];
            if (t.iszero()) continue;
            pos=prod.addterm(t,d*g,pos);
        }
        memkill(memc,deg);
        a.compress(ka); b.compress(kb);
        mr_free(C); mr_free(B); mr_free(A); 
    }
    else
    {
#endif
        bptr=b.start;

        while (bptr!=NULL)
        {
            aptr=a.start;
            pb=bptr->n*b.pwr-b.offset;
            pos=NULL;
            while (aptr!=NULL)
            {
                pa=aptr->n*a.pwr-a.offset;
                if (pb+pa>=psN) break;
                pos=prod.addterm(aptr->an*bptr->an,pa+pb,pos);
                aptr=aptr->next;
            }
            bptr=bptr->next;
        }
#ifdef FFT
    }
#endif

    if (prod.start!=NULL) prod.offset=a.offset+b.offset;
    return prod;
}