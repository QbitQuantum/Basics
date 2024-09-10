// Return covariance of two sets of points along with gradients.
MatrixXd GPCMWhiteKernel::covarianceGrad(
    const MatrixXd* const *X1,              // First data matrix.
    const MatrixXd* const *X2,              // Second data matrix.
    MatrixXd &X2grad                        // Gradient.
    )
{
    assert(X1[0] != NULL); // Make sure we have at least one element.
    assert(X2[0] != NULL); // Make sure we have at least one element.

    X2grad.setZero(X1[0]->rows(),dims);

    return MatrixXd::Zero(X1[0]->rows(),X2[0]->rows())*(var(0,0)+constVar);
}