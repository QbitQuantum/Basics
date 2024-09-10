DenseMatrix PSplineApproximant::computeCoefficients(const DataTable &samples) const
{
    // Assuming regular grid
    unsigned int numSamples = samples.getNumSamples();

    /* Setup and solve equations Lc = R,
     * L = B'*W*B + l*D'*D
     * R = B'*W*y
     * c = control coefficients or knot averages.
     * B = basis functions at sample x-values,
     * W = weighting matrix for interpolating specific points
     * D = second-order finite difference matrix
     * l = penalizing parameter (increase for more smoothing)
     * y = sample y-values when calculating control coefficients,
     * y = sample x-values when calculating knot averages
     */

    SparseMatrix L, W;

    // Weight matrix
    W.resize(numSamples, numSamples);
    W.setIdentity();

    // Basis function matrix
    SparseMatrix B = computeBasisFunctionMatrix(samples);

    // Second order finite difference matrix
    SparseMatrix D = getSecondOrderFiniteDifferenceMatrix();

    // Left-hand side matrix
    L = B.transpose()*W*B + lambda*D.transpose()*D;

    // Compute right-hand side matrices
    DenseMatrix By = controlPointEquationRHS(samples);
    //Rx = B.transpose()*W*Bx;
    DenseMatrix Ry = B.transpose()*W*By;

    // Matrices to store the resulting coefficients
    DenseMatrix Cy;

    int numEquations = L.rows();
    int maxNumEquations = pow(2,10);

    bool solveAsDense = (numEquations < maxNumEquations);

    if (!solveAsDense)
    {
#ifndef NDEBUG
        std::cout << "Computing B-spline control points using sparse solver." << std::endl;
#endif // NDEBUG

        SparseLU s;
        bool successfulSolve = s.solve(L,Ry,Cy);

        solveAsDense = !successfulSolve;
    }

    if (solveAsDense)
    {
#ifndef NDEBUG
        std::cout << "Computing B-spline control points using dense solver." << std::endl;
#endif // NDEBUG

        DenseMatrix Ld = L.toDense();
        DenseQR s;
        bool successfulSolve = s.solve(Ld, Ry, Cy);

        if (!successfulSolve)
        {
            throw Exception("PSpline::computeControlPoints: Failed to solve for B-spline coefficients.");
        }
    }

    return Cy.transpose();
}