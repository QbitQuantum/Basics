void prtaawapap2(aaw_c *aawc, aaw_c *aawc2) /* print aaw As Pure As Possible */
{
    int i, ii, j, k, ppi=0;
    for(i=1;i<aawc->numl;++i) {
        ii=1+i/2;
        /* order fo tabs and space will be messed up sure, but usually it will be one or the other. */
        for(j=5;j<aawc->aaw[i]->al;++j) {
            for(k=0;k<aawc->aaw[i]->aw[j]->lp1-1; k++)
                putwchar(aawc->aaw[i]->aw[j]->w[k]);
            if(j==aawc->aaw[i]->al-1)
                putwchar('\n');
            else
                putwchar(' ');
        }
        for(j=3;j<aawc2->aaw[ii]->al;++j) {
            for(k=0;k<aawc2->aaw[ii]->aw[j]->lp1-1; k++)
                putwchar(aawc2->aaw[ii]->aw[j]->w[k]);
            if(j==aawc2->aaw[ii]->al-1)
                printf("\n\n"); 
            else
                putwchar(' ');
        }
    }
}