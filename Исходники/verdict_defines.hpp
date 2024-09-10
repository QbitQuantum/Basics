inline double normalize_jacobian( double jacobi,
                                  VerdictVector& v1,
                                  VerdictVector& v2,
                                  VerdictVector& v3,
                                  int tet_flag = 0 )
{
    double return_value = 0.0;

    if ( jacobi != 0.0 )
    {

        double l1, l2, l3, length_product;
        // Note: there may be numerical problems if one is a lot shorter
        // than the others this way. But scaling each vector before the
        // triple product would involve 3 square roots instead of just
        // one.
        l1 = v1.length_squared();
        l2 = v2.length_squared();
        l3 = v3.length_squared();
        length_product = sqrt( l1 * l2 * l3 );

        // if some numerical scaling problem, or just plain roundoff,
        // then push back into range [-1,1].
        if ( length_product < fabs(jacobi) )
        {
            length_product = fabs(jacobi);
        }

        if( tet_flag == 1)
            return_value = v_sqrt_2 * jacobi / length_product;
        else
            return_value = jacobi / length_product;

    }
    return return_value;

}