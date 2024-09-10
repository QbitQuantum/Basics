// Based on a paper by Samuel R. Buss and Jin-Su Kim // TODO: Cite the paper properly
rk_result_t Robot::selectivelyDampedLeastSquaresIK_chain(const vector<size_t> &jointIndices, VectorXd &jointValues,
                                              const Isometry3d &target, const Isometry3d &finalTF)
{
    return RK_SOLVER_NOT_READY;
    // FIXME: Make this work


    // Arbitrary constant for maximum angle change in one step
    gammaMax = M_PI/4; // TODO: Put this in the constructor so the user can change it at a whim


    vector<Linkage::Joint*> joints;
    joints.resize(jointIndices.size());
    // FIXME: Add in safety checks
    for(int i=0; i<joints.size(); i++)
        joints[i] = joints_[jointIndices[i]];

    // ~~ Declarations ~~
    MatrixXd J;
    JacobiSVD<MatrixXd> svd;
    Isometry3d pose;
    AngleAxisd aagoal;
    AngleAxisd aastate;
    Vector6d goal;
    Vector6d state;
    Vector6d err;
    Vector6d alpha;
    Vector6d N;
    Vector6d M;
    Vector6d gamma;
    VectorXd delta(jointValues.size());
    VectorXd tempPhi(jointValues.size());
    // ~~~~~~~~~~~~~~~~~~

//    cout << "\n\n" << endl;

    tolerance = 1*M_PI/180; // TODO: Put this in the constructor so the user can set it arbitrarily
    maxIterations = 1000; // TODO: Put this in the constructor so the user can set it arbitrarily

    size_t iterations = 0;
    do {

        values(jointIndices, jointValues);

        jacobian(J, joints, joints.back()->respectToRobot().translation()+finalTF.translation(), this);

        svd.compute(J, ComputeFullU | ComputeThinV);

    //    cout <<  "\n\n" << svd.matrixU() << "\n\n\n" << svd.singularValues().transpose() << "\n\n\n" << svd.matrixV() << endl;

    //    for(int i=0; i<svd.matrixU().cols(); i++)
    //        cout << "u" << i << " : " << svd.matrixU().col(i).transpose() << endl;


    //    std::cout << "Joint name: " << joint(jointIndices.back()).name()
    //              << "\t Number: " << jointIndices.back() << std::endl;
        pose = joint(jointIndices.back()).respectToRobot()*finalTF;

    //    std::cout << "Pose: " << std::endl;
    //    std::cout << pose.matrix() << std::endl;

    //    AngleAxisd aagoal(target.rotation());
        aagoal = target.rotation();
        goal << target.translation(), aagoal.axis()*aagoal.angle();

        aastate = pose.rotation();
        state << pose.translation(), aastate.axis()*aastate.angle();

        err = goal-state;

    //    std::cout << "state: " << state.transpose() << std::endl;
    //    std::cout << "err: " << err.transpose() << std::endl;

        for(int i=0; i<6; i++)
            alpha[i] = svd.matrixU().col(i).dot(err);

    //    std::cout << "Alpha: " << alpha.transpose() << std::endl;

        for(int i=0; i<6; i++)
        {
            N[i] = svd.matrixU().block(0,i,3,1).norm();
            N[i] += svd.matrixU().block(3,i,3,1).norm();
        }

    //    std::cout << "N: " << N.transpose() << std::endl;

        double tempMik = 0;
        for(int i=0; i<svd.matrixV().cols(); i++)
        {
            M[i] = 0;
            for(int k=0; k<svd.matrixU().cols(); k++)
            {
                tempMik = 0;
                for(int j=0; j<svd.matrixV().cols(); j++)
                    tempMik += fabs(svd.matrixV()(j,i))*J(k,j);
                M[i] += 1/svd.singularValues()[i]*tempMik;
            }
        }

    //    std::cout << "M: " << M.transpose() << std::endl;

        for(int i=0; i<svd.matrixV().cols(); i++)
            gamma[i] = minimum(1, N[i]/M[i])*gammaMax;

    //    std::cout << "Gamma: " << gamma.transpose() << std::endl;

        delta.setZero();
        for(int i=0; i<svd.matrixV().cols(); i++)
        {
    //        std::cout << "1/sigma: " << 1/svd.singularValues()[i] << std::endl;
            tempPhi = 1/svd.singularValues()[i]*alpha[i]*svd.matrixV().col(i);
    //        std::cout << "Phi: " << tempPhi.transpose() << std::endl;
            clampMaxAbs(tempPhi, gamma[i]);
            delta += tempPhi;
    //        std::cout << "delta " << i << ": " << delta.transpose() << std::endl;
        }

        clampMaxAbs(delta, gammaMax);

        jointValues += delta;

        std::cout << iterations << " | Norm:" << delta.norm() << "\tdelta: "
                  << delta.transpose() << "\tJoints:" << jointValues.transpose() << std::endl;

        iterations++;
    } while(delta.norm() > tolerance && iterations < maxIterations);
}