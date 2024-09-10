    int findRTHough(const T2dPoints & points0, const T2dPoints & points1, const Eigen::Matrix3d & E_exact, const CMask & mask_exact, C3x3MatModel & model, CMask & mask) {

        for (int i = 0; i < NUM_HYPS; i++)
            aaHypotheses[0][i].reset();

        const TFloat NORMAL_LOCALISATION_ERR_SQ=sqr(0.0005);
        const int NUM_POINTS = points0.size();

        std::vector<T3Vec> ax;
        std::vector<TFullVec> axp;
        ax.reserve(NUM_POINTS);
        axp.reserve(NUM_POINTS);
        
        for (int i = 0; i < NUM_POINTS; i++) {
            T3Vec x;
            
            x(0) = points0[i].getX();
            x(1) = points0[i].getY();
            x(2) = 1;
            ax.push_back(x);
            
            TFullVec xp;
            xp.setZero();
            xp(0) = points1[i].getX();
            xp(1) = points1[i].getY();
            xp(2) = 1;
            
            axp.push_back(xp);
        }
        
        CEssentialMat_int E_test;
        bool bTest = true;
        if(bTest)
            E_test.init_test(E_exact);
        
        TFloat dMaxAngularError_sq = sqr(0.1); //Should set this so that on 1st iteration, about 2000 votes (100^0.8 * 50) for 50 points, 100 hyps.
        //TFloat dMaxAngularError_sq = sqr(0.15); //Should set this so that on 1st iteration, about 12500 votes (1000^0.8 * 50) for 50 points, 1000 hyps.
        
        for (int nIter = 0; nIter < MAX_ITERS; nIter++) {
            
            CEssentialMat_int * aHypotheses = aaHypotheses[nIter];
            
            const int NUM_POINTS = points0.size();

            for (int i = 0; i < NUM_POINTS; i++) {

                for (int nHyp = 0; nHyp < NUM_HYPS; nHyp++) {
                    aHypotheses[nHyp].observePoint(ax[i], axp[i], dMaxAngularError_sq);
                }
                
                if(bTest)
                    E_test.observePoint(ax[i], axp[i], dMaxAngularError_sq);
            }
            int nBestHyp = -1;
            double dBestVotes = 0, dTotalVotes = 0;
            for (int i = 0; i < NUM_HYPS; i++) {
                if (aHypotheses[i].votes() > dBestVotes) {
                    dBestVotes = aHypotheses[i].votes();
                    nBestHyp = i;
                }
                //cout << i << " " << aHypotheses[i].votes() << endl;
                //aHypotheses[i].pp();

                dTotalVotes += aHypotheses[i].votes();
            }
            
            aHypotheses[nBestHyp].setModel( model );
            for (int i = 0; i < (int)points0.size(); i++) {
                mask[i] = aHypotheses[nBestHyp].samsonsErr(ax[i], axp[i]) < dMaxAngularError_sq ? true : false;
            }

            aHypotheses[nBestHyp].pp(E_exact);
            mask.pp();
            
            /* //POOR indicator of best bin
             * TFloat dClosest = HUGE;
            int nCorrectHyp = -1;
            for (int i = 0; i < NUM_HYPS; i++) {
                TFloat dDist = aHypotheses[i].SSDFromBest(E_exact);
                if(dDist < dClosest)
                {
                    dClosest = dDist;
                    nCorrectHyp = i;
                }
            }*/
            
            cout << "Best bin has " << aHypotheses[nBestHyp].votes() << " votes" << endl;
            //cout << "Correct bin has " << aHypotheses[nCorrectHyp].votes() << " votes" << endl;
            
            if(bTest)
            {
                cout << "E_test bin has " << E_test.votes() << " votes" << endl;
                int nInliersInBest = 0;
                int nIntersection = 0;
                for (int i = 0; i < (int)points0.size(); i++) {
                    if(mask[i] && (E_test.samsonsErr(ax[i], axp[i]) < dMaxAngularError_sq))
                        nIntersection++;
                    
                    if(mask_exact[i] && mask[i])
                        nInliersInBest++;
                    
                }

                cout << "Intersection size: " << nIntersection << endl;
                cout << "InliersInBest: " << nInliersInBest << " " << ((TFloat)nInliersInBest/aHypotheses[nBestHyp].votes()) << endl;
                
                E_test.reset();
            }
            
            cout << "Average votes: " << dTotalVotes / NUM_HYPS << endl;
            
            if(nIter == MAX_ITERS-1 || NORMAL_LOCALISATION_ERR_SQ == dMaxAngularError_sq)
                break;            

            TFloat dTotalProb = 0;//, dNumInliers = 0.5 * (TFloat) NUM_POINTS;

            for (int i = 0; i < NUM_HYPS; i++) {
                dTotalProb += aHypotheses[i].computeProb(dTotalVotes, NUM_POINTS);
            }

            TFloat dTotalProb_inv = 1.0 / dTotalProb, dTotalProbSq = 0;
            dTotalProb = 0;
            for (int i = 0; i < NUM_HYPS; i++) {
                TFloat dProb = aHypotheses[i].normaliseProb(dTotalProb_inv, dTotalProb);
                dTotalProb += dProb;
                
                dTotalProbSq += sqr(dProb);
            }
            
            //Resample:
            int nOldHyp = 0;
            static const TFloat NUM_HYPS_inv = 1.0/NUM_HYPS;
            for (int i = 0; i < NUM_HYPS; i++) {
                double dThresh = (i+1)*NUM_HYPS_inv - 1e-8;
                
                while(aHypotheses[nOldHyp].cumulativeProb() < dThresh)
                    nOldHyp++;
                
                aHypotheses[nOldHyp].makeNewHyp(aaHypotheses[nIter+1][i], sqrt(dMaxAngularError_sq));
            }
            
            const TFloat dEffectiveNumParticles = 1.0/dTotalProbSq; //2* because otehrwise underestimates by about 2x
            
            TFloat reductionInVolume = dEffectiveNumParticles*NUM_HYPS_inv;
            TFloat reductionInRadius = pow(reductionInVolume, 2.0/5.0);
            
            dMaxAngularError_sq *= reductionInRadius;
            if(dMaxAngularError_sq < NORMAL_LOCALISATION_ERR_SQ)
                dMaxAngularError_sq = NORMAL_LOCALISATION_ERR_SQ; //About 3px, shouldn't go lower than this
        }

        return mask.countInliers();
    }