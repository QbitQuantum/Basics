int main(void)
{
    double i,e,roznica;
    double edbl = 0;
    long double eldbl = 0;
    long double el,roznical;
    for(i=0; i<19; i++)
    {
        edbl=edbl+((i+1)/silnia(i));
    }
    edbl=0.5*edbl;
    printf("Typ Double:  %.20f\n", edbl);
    e=exp(1);
    printf("EXP(1): %.20f\n",e);
    roznica=e-edbl;
    printf("ROZNICA: %.20g\n",roznica);

    for(i=0; i<22; i++)
    {
        eldbl=eldbl+((i+1)/silnia(i));
    }
    eldbl=0.5*eldbl;
    printf("Typ LDouble: %.20lf\n", eldbl);
    el=expl(1);
    printf("EXPL(1): %.20lf\n",el);
    roznical=el-eldbl;
    printf("ROZNICA: %.20lg\n",roznical);



}