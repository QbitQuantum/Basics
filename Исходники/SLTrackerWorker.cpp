void SLTrackerWorker::trackPointCloud(PointCloudConstPtr pointCloud){

    // Recursively call self until latest event is hit
    busy = true;
    QCoreApplication::sendPostedEvents(this, QEvent::MetaCall);
    bool result = busy;
    busy = false;
    if(!result){
        std::cerr << "SLTrackerWorker: dropped point cloud!" << std::endl;
        return;
    }

    if(!referenceSet){
        tracker->setReference(pointCloud);
        referenceSet = true;
        return;
    }

    performanceTime.start();

    Eigen::Affine3f T;
    bool converged;
    float RMS;
    tracker->determineTransformation(pointCloud, T, converged, RMS);

    // Emit result
    if(converged)
        emit newPoseEstimate(T);

//    std::cout << "Pose: " << T.matrix() << std::endl;

    std::cout << "Tracker: " << performanceTime.elapsed() << "ms" << std::endl;

    if(writeToDisk){
        Eigen::Vector3f t(T.translation());
        Eigen::Quaternionf q(T.rotation());

        (*ofStream) << trackingTime.elapsed() << ",";
        (*ofStream) << t.x() << "," << t.y() << "," << t.z() << ",";
        (*ofStream) << q.w() << "," << q.x() << "," << q.y() << "," << q.z() << "," << RMS;
        (*ofStream) << std::endl;
    }


}