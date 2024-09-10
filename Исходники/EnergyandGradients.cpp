double dEda(const VectorXd &XY,
            const VectorXd &s0,
            const vector<spring> &springlist,
            const vector<vector<int>> &springpairs,
            double kappa,
            const double g11,
            const double g12,
            const double g22)
{  
    double out;
    out=s0.dot(HarmonicGradient(springlist,XY,g11,g12,g22)+BendingGrad(springpairs,springlist,XY,kappa,g11,g12,g22));
    return out;
}