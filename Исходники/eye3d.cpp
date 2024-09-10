float
Eye3D::dynamic_EMD(const PointCloudPtr target, const vector<float> &wInput,
        PointCloudPtr source, const vector<float> &wOutput)
{
    _viz->clear();
    float radiusArg = 0.5;
    IterativeClosestPoint<PointT, PointT> icp;
    icp.setInputCloud(source);
    icp.setInputWeight(wInput);
    icp.setInputTarget(target);
    icp.setOutputWeight(wOutput);
    pcl::PointCloud<PointT> result;
    // Set the transformation epsilon (criterion 2)
    icp.setMaximumIterations (150);
    icp.setMaxCorrespondenceDistance (100);
    icp.setTransformationEpsilon (1e-11);
    // Set the euclidean distance difference epsilon (criterion 3)
    icp.setEuclideanFitnessEpsilon (1e-11);
    icp.setRANSACIterations(0); 
    icp.align(result);
    if (!icp.hasConverged()) {
        std::cout << "ICP failed to converged!"<<std::endl;
        return -1;
    }
    if (visualize_EMD) {
        /// visualize the align result
        int size = result.points.size();
        // rank the weights
        std::map<float, int> w2rank;
        std::vector<float> wInputRank;
        m_util::rank(wInput, &w2rank);
        for(float w: wInput){
            wInputRank.push_back(w2rank[w] + 1);
        }
        w2rank.clear();
        std::vector<float> wOutputRank;
        m_util::rank(wOutput, &w2rank);
        for(float w: wOutput){
            wOutputRank.push_back(w2rank[w] + 1);
        }
        int f = 50;
        for (int i = 0; i < size; i++) {
            _viz->add_sphere(target->points[i].x/f,target->points[i].y/f,
                    target->points[i].z/f, wInputRank[i]* radiusArg, 0, 255, 0);

            //        _viz->add_sphere(source->points[i].x/f, source->points[i].y/f,
            //                source->points[i].z/f, wOutputRank[i]* radiusArg, 0, 0, 255);

            _viz->add_sphere(result.points[i].x/f, result.points[i].y/f,
                    result.points[i].z, wOutputRank[i] * radiusArg, 255, 0, 0);
        }
        //    icp.visualize_correspondence(_viz,0);
        _viz->reset_camera();
    }
    return icp.best_EMD_;
}