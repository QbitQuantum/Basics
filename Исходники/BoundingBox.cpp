void BoundingBox::computeOrientedBox(std::vector<Eigen::Vector3d>& positions)
{
    // compute mean
    Eigen::Vector3d cm;
    cm.setZero();
    for (size_t i = 0; i < positions.size(); i++) {
        cm += positions[i];
    }
    cm /= (double)positions.size();
    
    // adjust for mean and compute covariance matrix
    Eigen::Matrix3d covariance;
    covariance.setZero();
    for (size_t i = 0; i < positions.size(); i++) {
        Eigen::Vector3d pAdg = positions[i] - cm;
        covariance += pAdg * pAdg.transpose();
    }
    covariance /= (double)positions.size();
    
    // compute eigenvectors for covariance matrix
    Eigen::EigenSolver<Eigen::Matrix3d> solver(covariance);
    Eigen::Matrix3d eigenVectors = solver.eigenvectors().real();
    
    // set axes
    eigenVectors.transpose();
    xAxis = eigenVectors.row(0);
    yAxis = eigenVectors.row(1);
    zAxis = eigenVectors.row(2);
    
    // project min and max points on each principal axis
    double min1 = INF, max1 = -INF;
    double min2 = INF, max2 = -INF;
    double min3 = INF, max3 = -INF;
    double d = 0.0;
    for (size_t i = 0; i < positions.size(); i++) {
        d = xAxis.dot(positions[i]);
        if (min1 > d) min1 = d;
        if (max1 < d) max1 = d;
        
        d = yAxis.dot(positions[i]);
        if (min2 > d) min2 = d;
        if (max2 < d) max2 = d;
        
        d = zAxis.dot(positions[i]);
        if (min3 > d) min3 = d;
        if (max3 < d) max3 = d;
    }
    
    // set center and halflengths
    center = (xAxis*(min1 + max1) + yAxis*(min2 + max2) + zAxis*(min3 + max3)) /2;
    halfLx = (max1 - min1)/2; halfLy = (max2 - min2)/2; halfLz = (max3 - min3)/2;
}