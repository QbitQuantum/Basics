double Frequency(int ** bits, int tailleCollection, int tailleMot)
{
    int Sn = 0;
    double Sobs = 0;
    for(int j = 0; j < tailleCollection; j++)
    {
        for(int i = 0; i < tailleMot; i ++)
        {
            if(bits[j][i] == 0)
            {
                Sn--;
            }
            else
            {
                Sn++;
            }
        }
    }
    Sobs = fabs(Sn)/ (double) sqrt(tailleCollection*tailleMot);

    double result = erfc((double)(Sobs/sqrt(2.0)));
    printf("Sn : %d\n", Sn);
    printf("Sobs : %lf\n", Sobs);
    printf("Pval : %lf\n", result);

    return result;
}