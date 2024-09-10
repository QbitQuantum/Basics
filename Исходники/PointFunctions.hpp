    void applyRandomRotTrans(MatrixBase<Derived> & points) {

        EIGEN_STATIC_ASSERT_MATRIX_SPECIFIC_SIZE(Derived,3, Eigen::Dynamic)
        Quaternion q;
        q.coeffs().setRandom();
        q.normalize();
        Matrix33 R = q.matrix();
        Vector3 trans;
        trans.setRandom();
        points = R*points;
        points.colwise() += trans;
    }