void denseFisherMetric::bounceP(const VectorXd& normal)
{
    
    mAuxVector = mGL.solve(normal);
    
    double C = -2.0 * mP.dot(mAuxVector);
    C /= normal.dot(mAuxVector);
    
    mP += C * normal;
    
}