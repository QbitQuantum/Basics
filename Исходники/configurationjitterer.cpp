    /// \brief jitters the current configuration and sets a new configuration on the environment
    ///
    int Sample(std::vector<dReal>& vnewdof, IntervalType interval=IT_Closed)
    {
        RobotBase::RobotStateSaver robotsaver(_probot, KinBody::Save_LinkTransformation|KinBody::Save_ActiveDOF);
        _InitRobotState();
        const dReal linkdistthresh = _linkdistthresh;
        const dReal linkdistthresh2 = _linkdistthresh2;

        vector<AABB> newLinkAABBs;
        bool bCollision = false;
        bool bConstraintFailed = false;
        bool bConstraint = !!_neighstatefn;

        // have to test with perturbations since very small changes in angles can produce collision inconsistencies
        std::vector<dReal> perturbations;
        if( _perturbation > 0 ) {
            perturbations.resize(3,0);
            perturbations[0] = _perturbation;
            perturbations[1] = -_perturbation;
        }
        else {
            perturbations.resize(1,0);
        }
        vnewdof.resize(GetDOF());
        int numNeighStateFailed = 0;
        FOREACH(itperturbation,perturbations) {
            if( bConstraint ) {
                FOREACH(it,_deltadof) {
                    *it = *itperturbation;
                }
                vnewdof = _curdof;
                if( !_neighstatefn(vnewdof,_deltadof,0) ) {
                    _probot->SetActiveDOFValues(_curdof);
//                    if( setret != 0 ) {
//                        // state failed to set, this could mean the initial state is just really bad, so resume jittering
//                        bCollision = true;
//                        break;
//                    }
                    ++numNeighStateFailed;
                    continue;
                }
            }
            else {
                for(size_t i = 0; i < vnewdof.size(); ++i) {
                    vnewdof[i] = _curdof[i]+*itperturbation;
                    if( vnewdof[i] > _upper.at(i) ) {
                        vnewdof[i] = _upper.at(i);
                    }
                    else if( vnewdof[i] < _lower.at(i) ) {
                        vnewdof[i] = _lower.at(i);
                    }
                }
            }

            // don't need to set state since CheckPathAllConstraints does it
            _probot->SetActiveDOFValues(vnewdof);

            if( !!_pConstraintToolDirection && !!_pmanip ) {
                if( !_pConstraintToolDirection->IsInConstraints(_pmanip->GetTransform()) ) {
                    bConstraintFailed = true;
                    break;

                }
            }
            if( !!_pConstraintToolPosition && !!_pmanip ) {
                if( !_pConstraintToolPosition->IsInConstraints(_pmanip->GetTransform()) ) {
                    bConstraintFailed = true;
                    break;

                }
            }
            if( GetEnv()->CheckCollision(_probot, _report) || _probot->CheckSelfCollision(_report) ) {
                bCollision = true;
                break;
            }
        }