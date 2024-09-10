    void construct_SD(size_t rId, size_t cId) const
    {
        complex<REAL> sij(0,0);
        complex<REAL> dij(0,0);

        for(size_t gi = 0;gi < spec_->nGaussPts;++ gi)
        {
            // gaussian point --> tri[rId] center
            Vector3<REAL> r = spec_->triCenters[rId] - spec_->gaussPts[cId][gi];
            REAL lenr  = r.length();
            REAL lenr2 = lenr*lenr;                                 // r^2

            s_->derCacheS_[rId][cId][gi] = spec_->gaussWeights[cId][gi]*
                    s_->crho_ / (4.*M_PI*lenr);
            /* ik*c*rho*exp(ikr)/(4*PI*r)*/
            sij += complex<REAL>(0, s_->k_)*std::exp(complex<REAL>(0,s_->k_*lenr))*
                    s_->derCacheS_[rId][cId][gi];

            s_->derCacheD_[rId][cId][gi] = -spec_->gaussWeights[cId][gi] * 
                    r.dot(spec_->triNormals[cId]) / (4.*M_PI*lenr2*lenr);
            /* (-1+ikr)*exp(ikr)*-<r.n>/(4*PI*r^3) */
            dij += complex<REAL>(-1,s_->k_*lenr)*std::exp(complex<REAL>(0,s_->k_*lenr))*
                    s_->derCacheD_[rId][cId][gi];
        }
        s_->B_(rId,cId) = sij;
        s_->A_(rId,cId) = dij;
    }