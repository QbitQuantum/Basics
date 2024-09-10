VectorXf param_sensitivity_widget::computeSensitivity(
    MatrixXf &parameterMatrix, VectorXf &responseVector)
{
    MatrixXf Ctemp = parameterMatrix.transpose()*parameterMatrix;
    MatrixXf C;
    C = Ctemp.inverse();

    VectorXf b = C*parameterMatrix.transpose()*responseVector;

    VectorXf Y_hat = parameterMatrix*b;

    int p = b.rows();

    VectorXf sigma2Vec = responseVector-Y_hat;

    float sigma2 = sigma2Vec.squaredNorm();
    sigma2= sigma2/(parameterMatrix.rows() - p);

    Ctemp = C*sigma2;

    MatrixXf denominator = Ctemp.diagonal();

    // Do element-wise division
    VectorXf t = b;
    for (int i = 0; i < b.rows(); i++)
    {
        t(i) = abs(b(i)/sqrt(denominator(i)));
    }

    return t;
}