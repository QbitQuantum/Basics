void NuTo::ContinuumElementIGA<TDim>::CalculateNMatrixBMatrixDetJacobian(EvaluateDataContinuum<TDim>& rData,
                                                                         int rTheIP) const
{
    // calculate Jacobian
    const auto ipCoords = this->GetIntegrationType().GetLocalIntegrationPointCoordinates(rTheIP);
    const Eigen::MatrixXd& derivativeShapeFunctionsGeometryNatural =
            this->mInterpolationType->Get(Node::eDof::COORDINATES)
                    .DerivativeShapeFunctionsNaturalIGA(ipCoords, mKnotIDs);

    Eigen::Matrix<double, TDim, TDim> jacobian = this->CalculateJacobian(derivativeShapeFunctionsGeometryNatural,
                                                                         rData.mNodalValues[Node::eDof::COORDINATES]);

    // there are two mappings in IGA: 1) reference element <=> parametric space (knots) 2) parametric space <=> physical
    // space
    // the B-matrix only the invJac of mapping 2) is needed
    rData.mDetJacobian = jacobian.determinant();
    for (int i = 0; i < TDim; i++)
        rData.mDetJacobian *= 0.5 * (mKnots(i, 1) - mKnots(i, 0));

    if (rData.mDetJacobian == 0)
        throw Exception(std::string("[") + __PRETTY_FUNCTION__ +
                        "] Determinant of the Jacobian is zero, no inversion possible.");

    Eigen::Matrix<double, TDim, TDim> invJacobian = jacobian.inverse();

    // calculate shape functions and their derivatives
    for (auto dof : this->mInterpolationType->GetDofs())
    {
        if (dof == Node::eDof::COORDINATES)
            continue;
        const InterpolationBase& interpolationType = this->mInterpolationType->Get(dof);
        rData.mNIGA[dof] = interpolationType.MatrixNIGA(ipCoords, mKnotIDs);

        rData.mB[dof] = this->CalculateMatrixB(
                dof, interpolationType.DerivativeShapeFunctionsNaturalIGA(ipCoords, mKnotIDs), invJacobian);
    }
}