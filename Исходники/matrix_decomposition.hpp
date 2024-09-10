    typename make_triangular_matrix<SymMatrix, boost::numeric::ublas::lower>::type
    cholesky_decomposition(SymMatrix const & A)
    {
        assert(A.size1() == A.size2());

        auto L = matrix_lower_trianle(A);

        for(size_t i = 0; i != A.size1(); ++ i)
        {
            for(size_t j = 0; j != i; ++ j)
            {
                for(size_t k = 0; k != j; ++ k)
                {
                    L(i, j) -= L(i, k) * L(j, k);
                }

                L(i, j) /= L(j, j);

                using ural::square;
                L(i, i) -= square(L(i, j));
            }

            assert(L(i, i) >= 0);

            using std::sqrt;
            L(i, i) = sqrt(L(i, i));
        }

        return L;
    }