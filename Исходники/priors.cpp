void dart::ReportedJointsPrior::computeContribution(Eigen::SparseMatrix<float> & fullJTJ,
                             Eigen::VectorXf & fullJTe,
                             const int * modelOffsets,
                             const int priorParamOffset,
                             const std::vector<MirroredModel *> & models,
                             const std::vector<Pose> & poses,
                             const OptimizationOptions & opts)
{
    // get mapping of reported joint names and values
    std::map<std::string, float> rep_map;
    for(unsigned int i=0; i<_reported.getReducedArticulatedDimensions(); i++) {
        // apply lower and upper joint limits
        rep_map[_reported.getReducedName(i)] =
                std::min(std::max(_reported.getReducedArticulation()[i], _reported.getReducedMin(i)), _reported.getReducedMax(i));
    }

#ifdef LCM_DEBUG_GRADIENT
    std::vector<std::string> names;
#if FILTER_FIXED_JOINTS
    const bool pub_grad = (_skipped==GRADIENT_SKIP);
#endif
#endif

    // compute difference of reported to estimated joint value
    Eigen::VectorXf diff = Eigen::VectorXf::Zero(_estimated.getReducedArticulatedDimensions());
    for(unsigned int i=0; i<_estimated.getReducedArticulatedDimensions(); i++) {
        const std::string jname = _estimated.getReducedName(i);
#ifdef LCM_DEBUG_GRADIENT
#if FILTER_FIXED_JOINTS
        if(pub_grad)
            if( !(_estimated.getReducedMin(i)==0 && _estimated.getReducedMin(i)==0) )
#endif
                names.push_back(jname);
#endif
        float rep = rep_map.at(jname);
        float est = _estimated.getReducedArticulation()[i];
        diff[i] = rep_map.at(jname) - _estimated.getReducedArticulation()[i];
    }

    // set nan values to 0, e.g. comparison of nan values always yields false
    diff = (diff.array()!=diff.array()).select(0,diff);

    // get Gauss-Newton parameter for specific objective function
    Eigen::MatrixXf J = Eigen::MatrixXf::Zero(_estimated.getReducedArticulatedDimensions(), 1);
    Eigen::VectorXf JTe = Eigen::VectorXf::Zero(_estimated.getReducedArticulatedDimensions());
    std::tie(J,JTe) = computeGNParam(diff);

    const Eigen::MatrixXf JTJ = J.transpose()*J;

#ifdef LCM_DEBUG_GRADIENT
#if FILTER_FIXED_JOINTS
    if(pub_grad) {
#endif
        // publish gradient (JTe)
        bot_core::joint_angles_t grad;
        grad.num_joints = names.size();
        grad.joint_name = names;
        for(unsigned int i = 0; i<JTe.size(); i++) {
#if FILTER_FIXED_JOINTS
            if(!(_estimated.getReducedMin(i)==0 && _estimated.getReducedMin(i)==0))
#endif
                grad.joint_position.push_back(JTe[i]);
        }
        LCM_CommonBase::publish("DART_GRADIENT", &grad);
#if FILTER_FIXED_JOINTS
        _skipped=0;
    }
    else {
        _skipped++;
    }
#endif
#endif // LCM_DEBUG_GRADIENT

    for(unsigned int r=0; r<JTJ.rows(); r++)
        for(unsigned int c=0; c<JTJ.cols(); c++)
            if(JTJ(r,c)!=0)
                fullJTJ.coeffRef(modelOffsets[_modelID]+6+r, modelOffsets[_modelID]+6+c) += JTJ(r,c);

    for(unsigned int r=0; r<JTe.rows(); r++)
            if(JTe[r]!=0)
                fullJTe[modelOffsets[_modelID]+6+r] += JTe[r];
}