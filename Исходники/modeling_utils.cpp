AffExpr affFromValGrad(double y, const VectorXd& x, const VectorXd& dydx, const VarVector& vars) {
    AffExpr aff;
    aff.constant = y - dydx.dot(x);
    aff.coeffs = toDblVec(dydx);
    aff.vars = vars;
    aff = cleanupAff(aff);
    return aff;
}