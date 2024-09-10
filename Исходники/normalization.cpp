bool normalizeOrientationAndTranslation(std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > &points, std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > &normals, Eigen::Affine3f &invTransform)
{
    if (points.empty())
        return false;

    // Perform PCA on input to determine a canoncial coordinate frame for the given point cloud.
    Eigen::Matrix3Xf::MapType pointsInMatrix(points.at(0).data(), 3, static_cast<int>(points.size()));
    const Eigen::Vector3f centroid = pointsInMatrix.rowwise().mean();
    pointsInMatrix = pointsInMatrix.colwise() - centroid;

    const Eigen::Matrix3f cov = pointsInMatrix * pointsInMatrix.transpose();
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eig(cov);
    const Eigen::Matrix3f rot = eig.eigenvectors().transpose();
    for (size_t i = 0; i < points.size(); ++i) {
        points[i] = rot * points[i];
        normals[i] = rot * normals[i];
    }

    invTransform = Eigen::Affine3f::Identity();
    invTransform = invTransform.rotate(rot).translate(-centroid); // applied in right to left order.
    invTransform = invTransform.inverse();

    return true;
}