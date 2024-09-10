    void operator() (std::size_t M, std::size_t N, RngType &rng,
            const double *weight, IntType *replication)
    {
        using std::modf;

        residual_.resize(M);
        integral_.resize(M);
        double *const rptr = &residual_[0];
        double *const iptr = &integral_[0];
        for (std::size_t i = 0; i != M; ++i)
            rptr[i] = modf(N * weight[i], iptr + i);
        double coeff = 1 / math::asum(M, rptr);
        math::scal(M, coeff, rptr);

        IntType R = 0;
        for (std::size_t i = 0; i != M; ++i)
            R += static_cast<IntType>(iptr[i]);
        std::size_t NN = N - static_cast<std::size_t>(R);
        U01SequenceSorted<RngType> u01seq(NN, rng);
        internal::inversion(M, NN, rptr, u01seq, replication);

        for (std::size_t i = 0; i != M; ++i)
            replication[i] += static_cast<IntType>(iptr[i]);
    }