double double_multivariateNormal_density(const MatrixXd &x,
        const MatrixXd &Mu, const MatrixXd &Sigma) {
    double expTerm, o;
    using namespace std;
    MatrixXd err;
    err = (x - Mu);
    err*=Sigma.inverse();
    err *=(x - Mu).transpose();
    expTerm = exp(err(0));
    o = 1/sqrt(pow(2*M_PI, Mu.rows())*Sigma.determinant());
    return o*expTerm;
}