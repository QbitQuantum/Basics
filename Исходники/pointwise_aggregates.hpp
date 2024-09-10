        pointwise_aggregates(const Matrix &A, const params &prm, unsigned min_aggregate)
            : count(0)
        {
            typedef typename backend::value_type<Matrix>::type value_type;
            typedef typename math::scalar_of<value_type>::type scalar_type;
            if (prm.block_size == 1) {
                plain_aggregates aggr(A, prm);

                remove_small_aggregates(A.nrows, 1, min_aggregate, aggr);

                count = aggr.count;
                strong_connection.swap(aggr.strong_connection);
                id.swap(aggr.id);
            } else {
                strong_connection.resize( nonzeros(A) );
                id.resize( rows(A) );

                auto ap = backend::pointwise_matrix(A, prm.block_size);
                backend::crs<scalar_type> &Ap = *ap;

                plain_aggregates pw_aggr(Ap, prm);

                remove_small_aggregates(
                        Ap.nrows, prm.block_size, min_aggregate, pw_aggr);

                count = pw_aggr.count * prm.block_size;

#pragma omp parallel
                {
                    std::vector<ptrdiff_t> j(prm.block_size);
                    std::vector<ptrdiff_t> e(prm.block_size);

#pragma omp for
                    for(ptrdiff_t ip = 0; ip < static_cast<ptrdiff_t>(Ap.nrows); ++ip) {
                        ptrdiff_t ia = ip * prm.block_size;

                        for(unsigned k = 0; k < prm.block_size; ++k, ++ia) {
                            id[ia] = prm.block_size * pw_aggr.id[ip] + k;

                            j[k] = A.ptr[ia];
                            e[k] = A.ptr[ia+1];
                        }

                        for(ptrdiff_t jp = Ap.ptr[ip], ep = Ap.ptr[ip+1]; jp < ep; ++jp) {
                            ptrdiff_t cp = Ap.col[jp];
                            bool      sp = (cp == ip) || pw_aggr.strong_connection[jp];

                            ptrdiff_t col_end = (cp + 1) * prm.block_size;

                            for(unsigned k = 0; k < prm.block_size; ++k) {
                                ptrdiff_t beg = j[k];
                                ptrdiff_t end = e[k];

                                while(beg < end && A.col[beg] < col_end) {
                                    strong_connection[beg] = sp && A.col[beg] != (ia + k);
                                    ++beg;
                                }

                                j[k] = beg;
                            }
                        }
                    }
                }
            }
        }