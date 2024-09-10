void Walker::nudgeHips( Hubo_Control &hubo, zmp_traj_element_t &elem,
            nudge_state_t &state, balance_gains_t &gains, double dt )
{
    bool debug = false;
    double kP, kD;  //!< Proportional and derivative gains
    int side;    //!< variable for stance leg
    // Figure out if we're in single or double support stance and which leg
    switch(elem.stance)
    {
        case SINGLE_LEFT:
            side = LEFT;
            kP = gains.single_support_hip_nudge_kp;
            kD = gains.single_support_hip_nudge_kd;
            break;
        case SINGLE_RIGHT:
            side = RIGHT;
            kP = gains.single_support_hip_nudge_kp;
            kD = gains.single_support_hip_nudge_kd;
            break;
        case DOUBLE_LEFT:
        case DOUBLE_RIGHT:
            side = 100;
            kP = gains.double_support_hip_nudge_kp;
            kD = gains.double_support_hip_nudge_kd;
            break;
        default:
            return;
    }

    // Store leg joint angels for current trajectory timestep
    std::vector<Vector6d, Eigen::aligned_allocator<Vector6d> > qPrev(2);
    qPrev[LEFT](HY) = elem.angles[LHY],
    qPrev[LEFT](HR) = elem.angles[LHR],
    qPrev[LEFT](HP) = elem.angles[LHP],
    qPrev[LEFT](KN) = elem.angles[LKN],
    qPrev[LEFT](AP) = elem.angles[LAP],
    qPrev[LEFT](AR) = elem.angles[LAR];

    qPrev[RIGHT](HY) = elem.angles[RHY],
    qPrev[RIGHT](HR) = elem.angles[RHR],
    qPrev[RIGHT](HP) = elem.angles[RHP],
    qPrev[RIGHT](KN) = elem.angles[RKN],
    qPrev[RIGHT](AP) = elem.angles[RAP],
    qPrev[RIGHT](AR) = elem.angles[RAR];

    // Skew matrix for torque reaction logic
    Eigen::Matrix3d skew; 
    skew << 0, 1, 0,
           -1, 0, 0,
            0, 0, 0;

    // Proportional gain matrix for ankle roll and pitch
    Eigen::Matrix3d shiftGainsKp;
    shiftGainsKp << kP,  0, 0,
                     0, kP, 0,
                     0,  0, 0;

    // Derivative gain matrix for ankle roll and pitch
    Eigen::Matrix3d shiftGainsKd;
    shiftGainsKd << kD,  0, 0,
                     0, kD, 0,
                     0,  0, 0;

    // Get rotation matrix for each hip yaw
    std::vector< Eigen::Matrix3d, Eigen::aligned_allocator<Eigen::Matrix3d> > yawRot(2);
    yawRot[LEFT] = Eigen::AngleAxisd(hubo.getJointAngle(LHY), Eigen::Vector3d::UnitZ()).toRotationMatrix();
    yawRot[RIGHT]= Eigen::AngleAxisd(hubo.getJointAngle(RHY), Eigen::Vector3d::UnitZ()).toRotationMatrix();

    // TF for body to each foot
    std::vector< Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d> > footTF(2);
    // New joint angles for both legs
    std::vector< Vector6d, Eigen::aligned_allocator<Vector6d> > qNew(2);
    // Ankle torque error XYZ (ie. Roll/Pitch/Yaw), but just setting Z to zero.
    Vector3d torqueErr[2];

    // Determine how much we need to nudge to hips over to account for
    // error in ankle torques about the x- and y- axes.
    // If Roll torque is positive (ie. leaning left) we want hips to go right (ie. negative y-direction)
    // If Pitch torque is positive (ie. leaning back) we want hips to go forward (ie. positive x-direction)
    // Get TFs for feet
    hubo.huboLegFK( footTF[LEFT], qPrev[LEFT], LEFT ); 
    hubo.huboLegFK( footTF[RIGHT], qPrev[RIGHT], RIGHT );

    std::cout << "foot is supposedly at " << footTF[LEFT].translation().transpose() << "\n";

    // Averaged torque error in ankles (roll and pitch) (yaw is always zero)
    //FIXME The version below is has elem.torques negative b/c hubomz computes reaction torque at ankle
    // instead of torque at F/T sensor
    torqueErr[LEFT](0) = (-elem.torque[LEFT][0] - hubo.getLeftFootMx());
    torqueErr[LEFT](1) = (-elem.torque[LEFT][1] - hubo.getLeftFootMy());
    torqueErr[LEFT](2) = 0;
    
    torqueErr[RIGHT](0) = (-elem.torque[RIGHT][0] - hubo.getRightFootMx());
    torqueErr[RIGHT](1) = (-elem.torque[RIGHT][1] - hubo.getRightFootMy());
    torqueErr[RIGHT](2) = 0;

    // Feet position errors (x,y)
    Vector3d instantaneousFeetOffset;

    // Check if we're on the ground, if not set instantaneous feet offset
    // to zero so integrated feet offset doesn't change, but we still apply it.
    const double forceThreshold = 20; // Newtons
    if(hubo.getLeftFootFz() + hubo.getRightFootFz() > forceThreshold)
    {
        std::cout << "Fzs = " << hubo.getLeftFootFz() << ", " << hubo.getRightFootFz() << "\n";
        if (side != LEFT && side != RIGHT)
        {
            instantaneousFeetOffset = (dt*shiftGainsKp * (yawRot[LEFT]*skew*torqueErr[LEFT] + yawRot[RIGHT]*skew*torqueErr[RIGHT])/2)
                                      - (shiftGainsKd * (yawRot[LEFT]*skew*(torqueErr[LEFT] - state.prevTorqueErr[LEFT])
                                         + yawRot[RIGHT]*skew*(torqueErr[RIGHT] - state.prevTorqueErr[RIGHT]))/2);
        }
        else
        {
            instantaneousFeetOffset = (dt*shiftGainsKp * yawRot[side]*skew*torqueErr[side])
                                      - (shiftGainsKd * yawRot[side]*skew*(torqueErr[side] - state.prevTorqueErr[side]));
        }
    }
    else
        instantaneousFeetOffset.setZero();

    // Decay the integratedFeetOffset
    state.integratedFeetOffset -= gains.decay_gain[LEFT]*state.integratedFeetOffset;

    // Add the instantaneous feet offset to the integrator
    state.integratedFeetOffset += instantaneousFeetOffset;

    const double integratedFeetOffsetTol = 0.06;
    double n = state.integratedFeetOffset.norm();
    if (n > integratedFeetOffsetTol) {
      state.integratedFeetOffset *= integratedFeetOffsetTol/n;
    }

    // Pretranslate feet TF by integrated feet error translation vector
    footTF[LEFT].pretranslate(state.integratedFeetOffset);
    footTF[RIGHT].pretranslate(state.integratedFeetOffset);
    // Run IK on the adjusted feet TF to get new joint angles
    bool ok = true;
    ok = hubo.huboLegIK(qNew[LEFT], footTF[LEFT], qPrev[LEFT], LEFT);
    if(ok)
        ok = hubo.huboLegIK(qNew[RIGHT], footTF[RIGHT], qPrev[RIGHT], RIGHT);
    // TODO: FIXME: MZ doesn't like the above code, he will explain

    hubo.huboLegFK( footTF[LEFT], qNew[LEFT], LEFT ); 
    std::cout << "now foot is supposedly at " << footTF[LEFT].translation().transpose() << "\n";

    if(debug)
    {
        std::cout //<< " K: " << kP
                  //<< " TdL: " << -elem.torque[LEFT][0] << ", " << -elem.torque[LEFT][1]
                  //<< " TdR: " << -elem.torque[RIGHT][0] << ", " << -elem.torque[RIGHT][1]
                  //<< " MyLR: " << hubo.getLeftFootMy() << ", " << hubo.getRightFootMy()
                  //<< " MxLR: " << hubo.getLeftFootMx() << ", " << hubo.getRightFootMx()
                  //<< " Te: " << torqueErr.transpose()
                  //<< " Fte: " << instantaneousFeetOffset.transpose()
                  //<< " qDfL: " << (qNew[LEFT] - qPrev[LEFT]).transpose()
                  << " FeetE: " << state.integratedFeetOffset.transpose()
                  << "\tqDfR: " << qNew[RIGHT].transpose()
                  << "\n";
    }

    //ok = false;

    // Set leg joint angles for current timestep of trajectory
    if(ok)
    {
        elem.angles[LHY] = qNew[LEFT](HY);
        elem.angles[LHR] = qNew[LEFT](HR);
        elem.angles[LHP] = qNew[LEFT](HP);
        elem.angles[LKN] = qNew[LEFT](KN);
        elem.angles[LAP] = qNew[LEFT](AP);
        elem.angles[LAR] = qNew[LEFT](AR);

        elem.angles[RHY] = qNew[RIGHT](HY);
        elem.angles[RHR] = qNew[RIGHT](HR);
        elem.angles[RHP] = qNew[RIGHT](HP);
        elem.angles[RKN] = qNew[RIGHT](KN);
        elem.angles[RAP] = qNew[RIGHT](AP);
        elem.angles[RAR] = qNew[RIGHT](AR);
    }
    else
        std::cout << "IK Invalid\n";

    // Save current force torque readings for next iteration
    for(int i=0; i<2; i++)
        state.prevTorqueErr[i] = torqueErr[i];
}