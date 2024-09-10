VectorXd Tetra10::Give_weights()
{
    VectorXd w;
    w.setZero(ngauss);

    w(0) = 0.0416666666666667;
    w(1) = 0.0416666666666667;
    w(2) = 0.0416666666666667;
    w(3) = 0.0416666666666667;
    return w;
}