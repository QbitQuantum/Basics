void LiftingLine::solve_for_best_gamma(double cL)
{
    int matsize = this->segments.size() + 1;
    Eigen::MatrixXd matrix;
    Eigen::VectorXd rhs;
    Eigen::VectorXd result;
    matrix.resize(matsize, matsize);
    matrix.setZero();
    rhs.resize(matsize);
    rhs.setZero();
    result.resize(matsize);
    result.setZero();
    //   adding the main min-function
    for (int i = 0; i < (matsize - 1); i++)
    {
        for (int j = 0; j < (matsize - 1); j++)
        {
            matrix(i, j) += this->segments[i].b() * this->segments[j].ind_influence(this->segments[i]);
            matrix(i, j) += this->segments[j].b() * this->segments[i].ind_influence(this->segments[j]);
        }
    //     adding lagrange multiplicator
        matrix(i, matsize - 1) += this->segments[i].lift_factor;
    }
    for (int i = 0; i < (matsize -1); i++)
    {
        matrix(matsize - 1, i) += this->segments[i].lift_factor;
    }
    rhs(matsize - 1) += cL;
    
    result = matrix.fullPivHouseholderQr().solve(rhs);
    for (int i = 0; i < matsize - 1; i++)
    {
        this->segments[i].best_gamma = result[i];
    }
}