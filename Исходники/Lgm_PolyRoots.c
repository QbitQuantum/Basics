/**
 *  \brief
 *      Returns the three roots of the cubic equation with real coefficients.
 *
 *  \details
 *      Returns the three roots of the cubic equation;
 *
 *              \f[z^3 + b z^2 + c z + d = 0,\f]
 *
 *      where \f$b, c, d\f$ are real coefficients, and the coefficient on the
 *      \f$x^3\f$ term is assumed to be 1.
 *
 *      \param[in]      b   Real coefficient of the \f$z^2\f$ term.
 *      \param[in]      c   Real coefficient of the \f$z\f$ term.
 *      \param[in]      d   Real constant term.
 *      \param[out]     z1  First real root.
 *      \param[out]     z2  Second (possibly complex) root.
 *      \param[out]     z3  Third (possibly complex) root.
 *
 *      \return         The number of real roots
 *
 *      \author         Mike Henderson
 *      \date           2011
 *
 */
int  Lgm_CubicRoots( double b, double c, double d, double *z1, double complex *z2, double complex *z3 ){

    int     nReal;
    double  b2, Q, R, D2, D, RpD, RmD, S, T, Theta, SqrtNQ, f, g, h;

    b2 = b*b;

    Q  = (3.0*c - b2)/9.0;
    R  = (9.0*b*c - 27.0*d - 2.0*b2*b)/54.0;
    D2 = Q*Q*Q + R*R;

    if (D2 == 0){
        // All 3 roots are real and at least two are equal.
        if ( R > 0.0) {
            f = cbrt( R );
            *z1 = 2.0*f - b/3.0;
            *z2 = *z3 = -f - b/3.0;
        } else {
            f = -cbrt( -R );
            *z1 = 2.0*f - b/3.0;
            *z2 = *z3 = -f - b/3.0;
        }
        nReal = 3;
    } else if ( D2 > 0 ) {
        // only one real root exists. The other two are complex conjugates.
        D = sqrt(D2); RpD = R+D; RmD = R-D;
        S = (RpD > 0.0) ? cbrt( RpD ) : -cbrt( -RpD );
        T = (RmD > 0.0) ? cbrt( RmD ) : -cbrt( -RmD);
        f = S+T;
        g = sqrt(3.0)/2.0*(S-T);
        h = b/3.0;
        *z1 = f - h;
        *z2 = -0.5*f - h + g*I;
        *z3 = -0.5*f - h - g*I;
        nReal = 1;

    } else if ( D2 < 0 ) {
        // All three roots are real and unequal.
        // This uses the simplest of the alternative trig forms.
        SqrtNQ = sqrt(-Q);
        Theta = acos( R/(SqrtNQ*fabs(Q)) );
        *z1 = 2.0*SqrtNQ*cos(Theta/3.0) - b/3.0; // real (returned as real double z1)
        *z2 = 2.0*SqrtNQ*cos( (Theta + 2.0*M_PI)/3.0 ) - b/3.0; // real (but returned as double complex z2)
        *z3 = 2.0*SqrtNQ*cos( (Theta + 4.0*M_PI)/3.0 ) - b/3.0; // real (but returned as double complex z3)
        nReal = 3;

    }

    return( nReal );

}