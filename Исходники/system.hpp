    double energy( const StateIn &q , const StateIn &p )
    {
        using checked_math::pow;
        // q and dpdt are 2d
        const size_t N = q.size();
        double energy = 0.0;
#ifndef NO_OMP
#pragma omp parallel
        {
#pragma omp master
            {
                if( m_threads == 0 )
                    m_threads = omp_get_num_threads();
            }

#pragma omp for reduction(+:energy) schedule(runtime)
#endif //NO_OMP
            for( size_t i=0 ; i<N-1 ; ++i )
            {
                energy += p[i]*p[i] / 2.0
                    + pow( q[i] , m_kap ) / m_kap
                    + pow( q[i]-q[i+1] , m_lam ) / m_lam;
            }
        }
        return energy;
    }