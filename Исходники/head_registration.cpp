bool extractPCFromColorModel(const PCRGB::Ptr& pc_in, PCRGB::Ptr& pc_out,
                             Eigen::Vector3d& mean, Eigen::Matrix3d& cov, double std_devs)
{
    double hue_weight;
    ros::param::param<double>("~hue_weight", hue_weight, 1.0);
    printf("%f\n", hue_weight);

    Eigen::Vector3d x, x_m;
    Eigen::Matrix3d cov_inv = cov.inverse();
    for(uint32_t i=0;i<pc_in->size();i++) {
        extractHSL(pc_in->points[i].rgb, x(0), x(1), x(2));
        x_m = x - mean;
        x_m(0) *= hue_weight;
        double dist = std::sqrt(x_m.transpose() * cov_inv * x_m);
        if(dist <= std_devs) 
            pc_out->points.push_back(pc_in->points[i]);
    }
}