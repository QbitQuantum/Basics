/**
 * This function computes the square of a weighted norm of a step
 * vector for one domain.
 *
 * @param x     Solution vector for this domain.
 * @param step  Newton step vector for this domain.
 * @param r     Object representing the domain. Used to get tolerances,
 *              number of components, and number of points.
 *
 * The return value is
 * \f[
 *    \sum_{n,j} \left(\frac{s_{n,j}}{w_n}\right)^2
 * \f]
 * where the error weight for solution component \f$n\f$ is given by
 * \f[
 *     w_n = \epsilon_{r,n} \frac{\sum_j |x_{n,j}|}{J} + \epsilon_{a,n}.
 * \f]
 * Here \f$\epsilon_{r,n} \f$ is the relative error tolerance for
 * component n, and multiplies the average magnitude of
 * solution component n in the domain. The second term,
 * \f$\epsilon_{a,n}\f$, is the absolute error tolerance for component
 * n.
 *
 */
doublereal norm_square(const doublereal* x,
                       const doublereal* step, Domain1D& r) {
    doublereal f, ewt, esum, sum = 0.0;
    int n, j;
    doublereal f2max = 0.0;
    int nmax = 0;
    int jmax = 0;
    int nv = r.nComponents();
    int np = r.nPoints();

    for (n = 0; n < nv; n++) {
        esum = 0.0;
        for (j = 0; j < np; j++) esum += fabs(x[nv*j + n]);
        ewt = r.rtol(n)*esum/np + r.atol(n);
        for (j = 0; j < np; j++) {
            f = step[nv*j + n]/ewt;
            sum += f*f;
            if (f*f > f2max) {
                jmax = j;
                nmax = n;
                f2max = f*f;
            }
        }
    }
#undef DEBUG_NORM
#ifdef DEBUG_NORM
    cout << "max step in domain " << r.id() << ": " << f2max << endl <<
         " for component " << r.componentName(nmax) << "  at point " << jmax << endl;
#endif
    return sum;
}