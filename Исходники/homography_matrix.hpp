/**
 * @brief estimateHomography estimates an homography matrix H between image 1 to image 2
 * @param points0 is an array of points computed from image 1.
 * @param points1 is an array of points computed from image 2.
 * @return It returns the homography matrix H.
 */
PIC_INLINE Eigen::Matrix3d estimateHomography(std::vector< Eigen::Vector2f > &points0,
                                   std::vector< Eigen::Vector2f > &points1)
{
    Eigen::Matrix3d  H;

    if((points0.size() != points1.size()) || (points0.size() < 4)) {
        H.setZero();
        return H;
    }

    Eigen::Vector3f transform_0 = ComputeNormalizationTransform(points0);
    Eigen::Vector3f transform_1 = ComputeNormalizationTransform(points1);

    Eigen::Matrix3d mat_0 = getShiftScaleMatrix(transform_0);
    Eigen::Matrix3d mat_1 = getShiftScaleMatrix(transform_1);

    int n = int(points0.size());
    Eigen::MatrixXd A(n * 2, 9);

    //set up the linear system
    for(int i = 0; i < n; i++) {
        //transform coordinates for increasing stability of the system
        Eigen::Vector2f p0 = points0[i];
        Eigen::Vector2f p1 = points1[i];

        p0[0] = (p0[0] - transform_0[0]) / transform_0[2];
        p0[1] = (p0[1] - transform_0[1]) / transform_0[2];

        p1[0] = (p1[0] - transform_1[0]) / transform_1[2];
        p1[1] = (p1[1] - transform_1[1]) / transform_1[2];

        int j = i * 2;
        A(j, 0) = 0.0;
        A(j, 1) = 0.0;
        A(j, 2) = 0.0;
        A(j, 3) = p0[0];
        A(j, 4) = p0[1];
        A(j, 5) = 1.0;
        A(j, 6) = -p1[1] * p0[0];
        A(j, 7) = -p1[1] * p0[1];
        A(j, 8) = -p1[1];

        j++;

        A(j, 0) = p0[0];
        A(j, 1) = p0[1];
        A(j, 2) = 1.0;
        A(j, 3) = 0.0;
        A(j, 4) = 0.0;
        A(j, 5) = 0.0;
        A(j, 6) = -p1[0] * p0[0];
        A(j, 7) = -p1[0] * p0[1];
        A(j, 8) = -p1[0];
    }

    //solve the linear system
    Eigen::JacobiSVD< Eigen::MatrixXd > svd(A, Eigen::ComputeFullV);
    Eigen::MatrixXd V = svd.matrixV();

    n = int(V.cols()) - 1;

    //assign and transpose
    H(0, 0) = V(0, n);
    H(0, 1) = V(1, n);
    H(0, 2) = V(2, n);

    H(1, 0) = V(3, n);
    H(1, 1) = V(4, n);
    H(1, 2) = V(5, n);

    H(2, 0) = V(6, n);
    H(2, 1) = V(7, n);
    H(2, 2) = V(8, n);

    H = mat_1.inverse() * H * mat_0;
    return H / H(2, 2);
}