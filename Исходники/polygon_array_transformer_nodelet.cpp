void PolygonArrayTransformer::transformPolygon(const Eigen::Affine3d& transform,
        const geometry_msgs::PolygonStamped& polygon,
        geometry_msgs::PolygonStamped& result)
{
    result.header = polygon.header;
    result.header.frame_id = frame_id_;
    for (size_t i = 0; i < polygon.polygon.points.size(); i++) {
        Eigen::Vector4d point;
        point[0] = polygon.polygon.points[i].x;
        point[1] = polygon.polygon.points[i].y;
        point[2] = polygon.polygon.points[i].z;
        point[3] = 1;             // homogenious
        Eigen::Vector4d transformed_point_eigen = transform.inverse() * point;
        geometry_msgs::Point32 transformed_point;
        transformed_point.x = transformed_point_eigen[0];
        transformed_point.y = transformed_point_eigen[1];
        transformed_point.z = transformed_point_eigen[2];
        result.polygon.points.push_back(transformed_point);
    }
}