std::vector< std::vector<Real> > ElectroIonicModel::getJac (const std::vector<Real>& v, Real h)
{
    std::vector< std::vector<Real> > J ( M_numberOfEquations, std::vector<Real> (M_numberOfEquations, 0.0) );
    std::vector<Real> f1 (M_numberOfEquations, 0.0);
    std::vector<Real> f2 (M_numberOfEquations, 0.0);
    std::vector<Real> y1 (M_numberOfEquations, 0.0);
    std::vector<Real> y2 (M_numberOfEquations, 0.0);

    for (int i = 0; i < M_numberOfEquations; i++)
    {
        for (int j = 0; j < M_numberOfEquations; j++)
        {
            y1[j] = v[j] + ( (double) (i == j) ) * h;
            y2[j] = v[j] - ( (double) (i == j) ) * h;
        }
        this->computeRhs (y1, f1);
        f1[0] += M_appliedCurrent;
        this->computeRhs (y2, f2);
        f2[0] += M_appliedCurrent;

        for (int j = 0; j < M_numberOfEquations; j++)
        {
            J[j][i] = (f1[j] - f2[j]) / (2.0 * h);
        }
    }

    return J;
}