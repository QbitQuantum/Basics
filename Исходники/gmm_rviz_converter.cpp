  void onGMM(const gaussian_mixture_model::GaussianMixture & mix)
  {
    visualization_msgs::MarkerArray msg;
    ROS_INFO("gmm_rviz_converter: Received message.");

    uint i;

    for (i = 0; i < mix.gaussians.size(); i++)
    {
      visualization_msgs::Marker marker;

      marker.header.frame_id = m_frame_id;
      marker.header.stamp = ros::Time::now();
      marker.ns = m_rviz_namespace;
      marker.id = i;
      marker.type = visualization_msgs::Marker::SPHERE;
      marker.action = visualization_msgs::Marker::ADD;
      marker.lifetime = ros::Duration();

      Eigen::Vector3f coords;
      for (uint ir = 0; ir < NUM_OUTPUT_COORDINATES; ir++)
        coords[ir] = m_conversion_mask[ir]->GetMean(m_conversion_mask,mix.gaussians[i]);
      marker.pose.position.x = coords.x();
      marker.pose.position.y = coords.y();
      marker.pose.position.z = coords.z();

      Eigen::Matrix3f covmat;
      for (uint ir = 0; ir < NUM_OUTPUT_COORDINATES; ir++)
        for (uint ic = 0; ic < NUM_OUTPUT_COORDINATES; ic++)
          covmat(ir,ic) = m_conversion_mask[ir]->GetCov(m_conversion_mask,mix.gaussians[i],ic);

      Eigen::EigenSolver<Eigen::Matrix3f> evsolver(covmat);

      Eigen::Matrix3f eigenvectors = evsolver.eigenvectors().real();
      if (eigenvectors.determinant() < 0.0)
        eigenvectors.col(0) = - eigenvectors.col(0);
      Eigen::Matrix3f rotation = eigenvectors;
      Eigen::Quaternionf quat = Eigen::Quaternionf(Eigen::AngleAxisf(rotation));

      marker.pose.orientation.x = quat.x();
      marker.pose.orientation.y = quat.y();
      marker.pose.orientation.z = quat.z();
      marker.pose.orientation.w = quat.w();

      Eigen::Vector3f eigenvalues = evsolver.eigenvalues().real();
      Eigen::Vector3f scale = Eigen::Vector3f(eigenvalues.array().abs().sqrt());
      if (m_normalize)
        scale.normalize();
      marker.scale.x = mix.weights[i] * scale.x() * m_scale;
      marker.scale.y = mix.weights[i] * scale.y() * m_scale;
      marker.scale.z = mix.weights[i] * scale.z() * m_scale;

      marker.color.a = 1.0;
      rainbow(float(i) / float(mix.gaussians.size()),marker.color.r,marker.color.g,marker.color.b);

      msg.markers.push_back(marker);
    }

    // this a waste of resources, but we need to delete old markers in some way
    // someone should add a "clear all" command to rviz
    // (using expiration time is not an option, here)
    for ( ; i < m_max_markers; i++)
    {
      visualization_msgs::Marker marker;
      marker.id = i;
      marker.action = visualization_msgs::Marker::DELETE;
      marker.lifetime = ros::Duration();
      marker.header.frame_id = m_frame_id;
      marker.header.stamp = ros::Time::now();
      marker.ns = m_rviz_namespace;
      msg.markers.push_back(marker);
    }

    m_pub.publish(msg);
    ROS_INFO("gmm_rviz_converter: Sent message.");
  }