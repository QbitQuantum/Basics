void BezierBoundarySolver::_IterateCurvatureReduction(BezierBoundaryProblem* pProblem,Eigen::Vector4d& params)
{
    double epsilon = 0.0001;
    //create a jacobian for the parameters by perturbing them
    Eigen::Vector4d Jt; //transpose of the jacobian
    BezierBoundaryProblem origProblem = *pProblem;
    double maxK = _GetMaximumCurvature(pProblem);
    for(int ii = 0; ii < 4 ; ii++){
        Eigen::Vector4d epsilonParams = params;
        epsilonParams[ii] += epsilon;
        _Get5thOrderBezier(pProblem,epsilonParams);
        _Sample5thOrderBezier(pProblem);
        double kPlus = _GetMaximumCurvature(pProblem);

        epsilonParams[ii] -= 2*epsilon;
        _Get5thOrderBezier(pProblem,epsilonParams);
        _Sample5thOrderBezier(pProblem);
        double kMinus = _GetMaximumCurvature(pProblem);
        Jt[ii] = (kPlus-kMinus)/(2*epsilon);
    }

    //now that we have Jt, we can calculate JtJ
    Eigen::Matrix4d JtJ = Jt*Jt.transpose();
    //thikonov regularization
    JtJ += Eigen::Matrix4d::Identity();

    Eigen::Vector4d deltaParams = JtJ.inverse() * Jt*maxK;
    params -= deltaParams;
    _Get5thOrderBezier(pProblem,params);
    _Sample5thOrderBezier(pProblem);
    //double finalMaxK = _GetMaximumCurvature(pProblem);

    //dout("2D Iteration took k from " << maxK << " to " << finalMaxK);
}