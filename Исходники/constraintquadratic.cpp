ConstraintQuadratic::ConstraintQuadratic(std::vector<VariablePtr> variables, DenseMatrix A, DenseMatrix b, double c, double lb, double ub)
    : Constraint(variables), A(A), b(b), c(c)
{
    assert(A.cols() == (int)variables.size());
    assert(A.rows() == b.rows());
    assert(b.cols() == 1);

    numConstraints = 1;

    this->lb.push_back(lb);
    this->ub.push_back(ub);

    jacobianCalculated = true;
    hessianCalculated = true;
    constraintLinear = false;
    constraintConvex = false;
    convexRelaxationAvailable = true;

    nnzJacobian = A.rows();
    nnzHessian = 0;

    constraintName = "Constraint Quadratic";

    //    // Check for parameters for NaN
    //    for (int i = 0; i < A.rows(); i++)
    //    {
    //        for (int j = 0; j < A.cols(); j++)
    //        {
    //            bool nanA = false;
    //            if (A(i,j) != A(i,j)) nanA = true;
    //            assert(nanA == false);
    //        }
    //        bool nanb = false;
    //        if (b(i) != b(i)) nanb = true;
    //        assert(nanb == false);
    //    }

    // Calculate and store Hessian
    H = A.transpose() + A;

    // H is symmetric so fill out lower left triangle only
    for (int row = 0; row < H.rows(); row++)
    {
        for (int col = 0; col <= row; col++)
        {
            if (H(row,col) != 0)
            {
                nnzHessian++;
            }
        }
    }

    // Check convexity using Hessian
    Eigen::EigenSolver<DenseMatrix> es(H);
    DenseVector eigs = es.eigenvalues().real();
    double minEigVal = 0;
    for (int i = 0; i < eigs.rows(); i++)
    {
        if (eigs(i) < minEigVal) minEigVal = eigs(i);
    }

    if (minEigVal >= 0 && lb <= -INF)
    {
        constraintConvex = true;
    }
    // Note could also check that max. eigen value <= 0 and ub = INF

    checkConstraintSanity();
}