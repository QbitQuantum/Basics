    KUKADU_SHARED_PTR<Dmp> GeneralDmpLearner::fitTrajectories() {

        int dataPointsNum = joints.n_rows;

        vec g(degFreedom);
        vec y0(degFreedom);
        vec dy0(degFreedom);
        vec ddy0(degFreedom);

        vector<vec> dmpCoeffs;
        vector<vec> sampleYs;
        vector<vec> fitYs;

        vector<mat> designMatrices;
        vec timeVec = joints.col(0);

        mat all_y;
        mat all_dy;
        mat all_ddy;

        // retrieve all columns for different degrees of freedom
        vector<vec> trajectories;
        for(int i = 1; i <= degFreedom; ++i) {

            vec trajectory = joints.col(i);
            trajectories.push_back(trajectory);

            vec vec_dy = computeDiscreteDerivatives(timeVec, trajectory);
            vec vec_ddy = computeDiscreteDerivatives(timeVec, vec_dy);

            all_y = join_rows(all_y, trajectory);
            all_dy = join_rows(all_dy, vec_dy);
            all_ddy = join_rows(all_ddy, vec_ddy);

        }

        vector<trajectory_learner_internal> dmpResAll = fitTrajectory(timeVec, all_y, all_dy, all_ddy);

        for(int i = 0; i < dmpResAll.size(); ++i) {

            trajectory_learner_internal dmpRes = dmpResAll.at(i);
            vec dmpCoeff = dmpRes.coeff;
            vec fity = dmpRes.fity;

            g(i) = (all_y.col(i))(dataPointsNum - 1);
            y0(i) = all_y.col(i)(0);
            dy0(i) = all_dy.col(i)(0);
            ddy0(i) = all_ddy.col(i)(0);
            dmpCoeffs.push_back(dmpCoeff);

            fitYs.push_back(fity);
            designMatrices.push_back(dmpRes.desMat);

        }

        for (int i = 0; i < all_y.n_cols; ++i) sampleYs.push_back(all_y.col(i));
        return createDmpInstance(timeVec, sampleYs, fitYs, dmpCoeffs, dmpBase, designMatrices, tau, az, bz, ax);

    }