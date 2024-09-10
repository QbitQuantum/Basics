void MarkerArrayVisualizer::drawEllipsoids(const char* ns, const std::vector<Eigen::Vector3d>& center, const std::vector<Eigen::Matrix3d>& A)
{
    visualization_msgs::MarkerArray marker_array;

    const int size = center.size();

    for (int i=0; i<size; i++)
    {
        visualization_msgs::Marker marker;

        marker.header.frame_id = "/world";
        marker.header.stamp = ros::Time::now();

        marker.ns = ns;
        marker.id = i;
        marker.type = visualization_msgs::Marker::SPHERE;
        marker.action = visualization_msgs::Marker::ADD;

        // axis: eigenvectors
        // radius: eigenvalues
        Eigen::JacobiSVD<Eigen::MatrixXd> svd(A[i], Eigen::ComputeThinU | Eigen::ComputeThinV);
        const Eigen::VectorXd& r = svd.singularValues();
        Eigen::Matrix3d Q = svd.matrixU();

        // to make determinant 1
        if (Q.determinant() < 0)
            Q.col(2) *= -1.;
        const Eigen::Quaterniond q(Q);

        marker.pose.position.x = center[i](0);
        marker.pose.position.y = center[i](1);
        marker.pose.position.z = center[i](2);
        marker.pose.orientation.x = q.x();
        marker.pose.orientation.y = q.y();
        marker.pose.orientation.z = q.z();
        marker.pose.orientation.w = q.w();

        marker.scale.x = 2. * r(0);
        marker.scale.y = 2. * r(1);
        marker.scale.z = 2. * r(2);

        marker.color.r = 1.0;
        marker.color.g = 0.0;
        marker.color.b = 0.0;
        marker.color.a = 0.2;

        marker.lifetime = ros::Duration();

        marker_array.markers.push_back(marker);
    }

    publish(marker_array);
}