DenseVector Michalewicz::michalewiczFunction(DenseVector x)
{
    assert(x.rows() == 2);
    double pi = atan(1)*4;
    DenseVector y; y.setZero(1);
    y(0) = -sin(x(0))*pow(sin(x(0)*x(0)/pi), 20) -sin(x(1))*pow(sin(2*x(1)*x(1)/pi), 20);
    return y;
}