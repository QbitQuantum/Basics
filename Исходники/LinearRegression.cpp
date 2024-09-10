bool LinearRegression::FitLinearModel(Matrix & X, Vector & y){
    Matrix Xt;
    Xt.Transpose(X);

    Matrix XtX;
    XtX.Product(Xt, X);
    if (!this->chol.TryDecompose(XtX))
        return false;
    chol.Decompose(XtX);
    chol.Invert();
    this->XtXinv = chol.inv;

    Vector tmp = y;
    tmp.Product(Xt, y);
    this->B.Product(this->XtXinv, tmp); // beta = (XtX)^{-1} Xt Y

    this->predict.Product(X, this->B);
    this->residuals = y;
    this->residuals.Subtract(this->predict);

    this->sigma2 = 0.0;
    for (int i = 0; i < this->residuals.Length(); i++){
        sigma2 += (this->residuals[i]) * (this->residuals[i]);
    }
    sigma2 /= y.Length(); // MLE estimates of sigma2

    this->covB = this->XtXinv;
    this->covB.Multiply(sigma2);
    return true;
}; 