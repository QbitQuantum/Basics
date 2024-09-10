void DepthFrame::getRegisteredAndReferencedPointCloud(pcl::PointCloud<pcl::PointXYZ>& cloud)
{
    pcl::PointXYZ regReferencePoint = getRegisteredReferencePoint();
    
    // Build a translation matrix to the registered reference the cloud after its own registration
    Eigen::Matrix4f E = Eigen::Matrix4f::Identity();
    E.col(3) = regReferencePoint.getVector4fMap(); // set translation column
    
    // Apply registration first and then referenciation (right to left order in matrix product)
    pcl::PointCloud<pcl::PointXYZ>::Ptr pCloudTmp (new pcl::PointCloud<pcl::PointXYZ>);
    getPointCloud(*pCloudTmp);
    
    pcl::transformPointCloud(*pCloudTmp, cloud, E.inverse() * m_T);
}