Sphere Sphere::fit_sphere(const MatrixX3f& points)
{
    const VectorXf& x = points.col(0);
    const VectorXf& y = points.col(1);
    const VectorXf& z = points.col(2);

    VectorXf point_means = points.colwise().mean();

    VectorXf x_mean_free = x.array() - point_means(0);
    VectorXf y_mean_free = y.array() - point_means(1);
    VectorXf z_mean_free = z.array() - point_means(2);

    Matrix3f A;
    A << (x.cwiseProduct(x_mean_free)).mean(), 2*(x.cwiseProduct(y_mean_free)).mean(), 2*(x.cwiseProduct(z_mean_free)).mean(),
                                            0,   (y.cwiseProduct(y_mean_free)).mean(), 2*(y.cwiseProduct(z_mean_free)).mean(),
                                            0,                                      0,   (z.cwiseProduct(z_mean_free)).mean();

    Matrix3f A_T = A.transpose();
    A += A_T;

    Vector3f b;
    VectorXf sq_sum = x.array().pow(2)+y.array().pow(2)+z.array().pow(2);
    b << (sq_sum.cwiseProduct(x_mean_free)).mean(),
         (sq_sum.cwiseProduct(y_mean_free)).mean(),
         (sq_sum.cwiseProduct(z_mean_free)).mean();

    Vector3f center = A.ldlt().solve(b);

    MatrixX3f tmp(points.rows(),3);
    tmp.col(0) = x.array() - center(0);
    tmp.col(1) = y.array() - center(1);
    tmp.col(2) = z.array() - center(2);

    float r = sqrt(tmp.array().pow(2).rowwise().sum().mean());

    return Sphere(center, r);
}