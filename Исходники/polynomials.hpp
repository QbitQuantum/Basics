Eigen::Matrix<T, -1, 1> getPolynomialVariables(const Eigen::Matrix<T, -1, 1> &vars,
                                               const size_t & degree)
{


    typedef Eigen::Matrix<T, -1, 1> Vector;
    typedef Eigen::Matrix<T, -1, -1, Eigen::RowMajor> Matrix;

    auto expand_to_degree = [](const float &x, const int &degree)
    {
        Vector out(degree+1);

        for (int i = 0; i <= degree ; ++i)
            out(i)  = pow(x, i);

        return out;
    };


    Vector current (1);
    current << 1;

    for (int i = 0; i < vars.rows() ; ++i)
    {
        // we expand to the given degree the variable
        Vector expanded = expand_to_degree(vars(i), degree);

        Matrix mul = current * expanded.transpose();


        current.resize(mul.size());

        current = Eigen::Map<Vector> (mul.data(), mul.size());

    }

    return current;

}