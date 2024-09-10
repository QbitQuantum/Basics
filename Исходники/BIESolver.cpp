    void operator() (const tbb::blocked_range<size_t>& range)
    {
        complex<REAL> localsum(0,0);
        const BIESpec* spec = s_->spec_;
        const complex<REAL> ik = complex<REAL>(0,s_->k_);

        for(size_t ii = range.begin(); ii != range.end(); ++ ii)
        {
            const complex<REAL>& P  = s_->x_(ii);
            const complex<REAL>& dP = spec->normalVel(ii)*ik*s_->crho_;

            // triangle ii
            for(size_t gi = 0; gi < spec->nGaussPts; ++ gi)
            {
                // gaussian point --> tri[rId] center
                Vector3<REAL> r  = pt_ - spec->gaussPts[ii][gi];
                const REAL lenr  = r.length();
                const REAL lenr2 = r.length_sqr();                              // r^2
                const complex<REAL> expikr = std::exp(complex<REAL>(0,s_->k_*lenr));

                localsum += expikr*dP * spec->gaussWeights[ii][gi] / (4.*M_PI*lenr);

                const REAL rdotny = r.dot(spec->triNormals[ii]);
                localsum += complex<REAL>(-1,s_->k_*lenr) * expikr * P * rdotny *
                            spec->gaussWeights[ii][gi] / (4.*M_PI*lenr2*lenr);
            }
        }

        this->ret = localsum;
    }