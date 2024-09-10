void setTrackerTarget(){
    initTracking();
    Eigen::Vector4f c;
    Eigen::Affine3f trans = Eigen::Affine3f::Identity ();
    pcl::compute3DCentroid<PointT>(*object_to_track,c);
    trans.translation().matrix() = Eigen::Vector3f(c[0],c[1],c[2]);
    tracker_->setTrans (trans);

    pcl::PointCloud<PointT>::Ptr tmp_pc(new pcl::PointCloud<PointT>);
    pcl::transformPointCloud<PointT> (*object_to_track, *tmp_pc, trans.inverse());

    tracker_->setReferenceCloud(tmp_pc);
    tracker_->setInputCloud(cloud);

    tracked_object_centroid->clear();
    tracked_object_centroid->push_back(PointT(c[0],c[1],c[2]));

}