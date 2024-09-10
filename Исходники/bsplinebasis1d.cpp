// Old implementation of first derivative of basis functions
DenseVector BSplineBasis1D::evaluateFirstDerivative(double x) const
{
    DenseVector values;
    values.setZero(numBasisFunctions());

    supportHack(x);

    std::vector<int> supportedBasisFunctions = indexSupportedBasisfunctions(x);

    for(int i : supportedBasisFunctions)
    {
        // Differentiate basis function
        // Equation 3.35 in Lyche & Moerken (2011)
        double b1 = deBoorCox(x, i, degree-1);
        double b2 = deBoorCox(x, i+1, degree-1);

        double t11 = knots.at(i);
        double t12 = knots.at(i+degree);
        double t21 = knots.at(i+1);
        double t22 = knots.at(i+degree+1);

        (t12 == t11) ? b1 = 0 : b1 = b1/(t12-t11);
        (t22 == t21) ? b2 = 0 : b2 = b2/(t22-t21);

        values(i) = degree*(b1 - b2);
    }

    return values;
}