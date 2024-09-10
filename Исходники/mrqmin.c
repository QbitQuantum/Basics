void errcalc (double *sigma, double **alpha, int ma, int *ia, int mfit)
{
    void sortsig(double *sigma, int ma, int ia[], int mfit);
    float rootfind(float (*func)(float, float), float nu, float x1, float x2,
								float xacc);

    double *d, **v;
    int nrot, m, n;
    float delchi2;

    d = dvector (1, mfit);
    v = dmatrix (1, mfit, 1, mfit);

    for (m=1; m <= mfit; m++) {
	for (n=1; n <= mfit; n++)
	    v[n][m] = 0.;
    };

    jacobi (alpha, mfit, d, v, &nrot);  /* Find eigenvec and eigenval */

    /****************************************************************\
    *  This is the delta chi^2 contour that jointly bounds the 68%   *
    *  confidence region for all the mfit parameters, not just a     *
    *  single parameter.                                             *
    \****************************************************************/

/*    delchi2 = rootfind (&gammp, mfit, 0.8*mfit, mfit * 1.2, 0.05); */
    delchi2 = 1.;

    for (m=1; m<=mfit; m++) {
        sigma[m] = fabs(v[m][1]/sqrt(d[1]));
        for (n=1; n<=mfit; n++)
/*            sigma[m] += (fabs(v[m][n]) / sqrt(d[n])); */
            sigma[m] = FMAX(sigma[m], fabs(v[m][n]) / sqrt(d[n]));
    };

    /*****************************************************\
    *  Scale the uncertainties by the sqrt(delta chi^2).  *
    \*****************************************************/

    for (m=1; m<=mfit; m++)
        sigma[m] = sigma[m] * sqrt(delchi2);

    sortsig (sigma, ma, ia, mfit);
    free_dvector (d, 1, mfit);
    free_dmatrix(v, 1, mfit, 1, mfit);
}