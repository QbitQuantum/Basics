void compute_plane(Eigen::Vector4f& plane, const pcl::PointCloud<pcl::PointXYZ>& points, int* inds)
{
    Eigen::Vector3f first = points[inds[1]].getVector3fMap() - points[inds[0]].getVector3fMap();
    Eigen::Vector3f second = points[inds[2]].getVector3fMap() - points[inds[0]].getVector3fMap();
    Eigen::Vector3f normal = first.cross(second);
    normal.normalize();
    plane.segment<3>(0) = normal;
    plane(3) = -normal.dot(points[inds[0]].getVector3fMap());
}