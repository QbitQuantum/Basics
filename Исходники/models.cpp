void CollisionModel::addLinkContacts(double dist_range, const std::string &link_name, const pcl::PointCloud<pcl::PointNormal>::Ptr &res,
                                     const KDL::Frame &T_W_L, const std::vector<ObjectModel::Feature > &ob_features,
                                     const KDL::Frame &T_W_O) {
    const double lambda = - std::log(0.01) / (dist_range * dist_range);
    std::list<std::pair<int, double> > link_pt;

    for (int poidx = 0; poidx < ob_features.size(); poidx++) {
        double min_dist = dist_range + 1.0;
        for (int pidx = 0; pidx < res->points.size(); pidx++) {
            KDL::Vector p1(res->points[pidx].x, res->points[pidx].y, res->points[pidx].z);
            const KDL::Vector &p2( ob_features[poidx].T_O_F_.p );
            double dist = (T_W_L * p1 - T_W_O * p2).Norm();
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        if (min_dist < dist_range) {
            link_pt.push_back( std::make_pair(poidx, min_dist) );
        }
    }
    if ( link_pt.size() > 0 ) {
        link_models_map_[link_name].features_.resize( link_pt.size() );
        std::vector<KDL::Frame > T_L_F_vec( link_pt.size() );
        col_link_names_.push_back(link_name);
        int fidx = 0;
        KDL::Vector col_pt;
        double sum_weight = 0.0;
        for (std::list<std::pair<int, double> >::const_iterator it = link_pt.begin(); it != link_pt.end(); it++, fidx++) {
            int poidx = it->first;
            link_models_map_[link_name].features_[fidx].pc1 = ob_features[poidx].pc1_;
            link_models_map_[link_name].features_[fidx].pc2 = ob_features[poidx].pc2_;
            KDL::Frame T_W_F = T_W_O * ob_features[poidx].T_O_F_;
            T_L_F_vec[fidx] = T_W_L.Inverse() * T_W_F;
            double dist = it->second;
            link_models_map_[link_name].features_[fidx].dist = dist;
            double weight = std::exp(-lambda * dist * dist);
            link_models_map_[link_name].features_[fidx].weight = weight;
            col_pt = col_pt + weight * T_L_F_vec[fidx].p;
            sum_weight += weight;
        }
        link_models_map_[link_name].T_L_C_ = KDL::Frame(col_pt / sum_weight);
        for (int fidx = 0; fidx < link_models_map_[link_name].features_.size(); fidx++) {
            link_models_map_[link_name].features_[fidx].T_C_F = link_models_map_[link_name].T_L_C_.Inverse() * T_L_F_vec[fidx];
            link_models_map_[link_name].features_[fidx].weight /= sum_weight;
        }
    }
}