double energy( const dvecvec &q , const dvecvec &p )
{
    using checked_math::pow;
    using std::abs;
    const size_t N = q.size();
    double energy = 0.0;
    for( size_t i=0 ; i<N-1 ; ++i )
    {
        const size_t M = q[i].size();
        for( size_t j=0 ; j<M-1 ; ++j )
        {
            energy += 0.5*p[i][j]*p[i][j] + pow( q[i][j] , KAPPA ) / KAPPA
                + pow( abs(q[i][j]-q[i][j+1]) , LAMBDA ) / LAMBDA
                + pow( abs(q[i][j]-q[i+1][j]) , LAMBDA ) / LAMBDA;
        }
        energy += 0.5*p[i][M-1]*p[i][M-1] + pow( q[i][M-1] , KAPPA ) / KAPPA
            + pow( abs(q[i][M-1]-q[i+1][M-1]) , LAMBDA ) / LAMBDA;
    }
    const size_t M = q[N-1].size();
    for( size_t j=0 ; j<M-1 ; ++j )
    {
        energy += 0.5*p[N-1][j]*p[N-1][j] + pow( q[N-1][j] , KAPPA ) / KAPPA
            + pow( abs(q[N-1][j]-q[N-1][j+1]) , LAMBDA ) / LAMBDA;
    }
    energy += 0.5*p[N-1][M-1]*p[N-1][M-1] + pow( q[N-1][M-1] , KAPPA ) / KAPPA;
    return energy;
}