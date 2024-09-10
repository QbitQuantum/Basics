void multiKinectCalibration::getData()
{
    iterationStep = 0;
//    std::string relativeTo = listOfTFnames.at(0);
    kinect2kinectTransform.resize(listOfTFnames.size() - 1);
    ros::Rate r(2);
    
    Eigen::Transform<double,3,Eigen::Affine> kinectReference;
    ros::spinOnce();
    if (!useTFonly)
    {
        while ( iterationStep < listOfTFnames.size() && ros::ok())
        {
            std::cerr << "Waiting for point clouds... \n";
            r.sleep();
            ros::spinOnce();
        }
        showPCL();
        std::cerr << "Subscribe pcl done" << std::endl;
    }
    sleep(1.0);
    std::cerr << listener.allFramesAsString() << std::endl;
    // listen to all tf Frames
    
    // get the transformation between kinects
    for (std::size_t i = 0; i < listOfTFnames.size(); i++)
    {
        tf::StampedTransform transform;
        std::string parentFrame;
        listener.getParent(listOfTFnames.at(i),ros::Time(0),parentFrame);
        listOfPointCloudnameHeaders.push_back(parentFrame);
        
        std::cerr << "Lookup transform: "<< listOfTFnames.at(i) << " with parent: "<< parentFrame <<std::endl;
        listener.waitForTransform(parentFrame,listOfTFnames.at(i),ros::Time(0),ros::Duration(5.0));
        listener.lookupTransform(parentFrame,listOfTFnames.at(i),ros::Time(0),transform);
        Eigen::Transform<double,3,Eigen::Affine> tmpTransform;
        tf::transformTFToEigen(transform,tmpTransform);
        
//        geometry_msgs::TransformStamped msg;
//        transformStampedTFToMsg(transform, msg);
//        Eigen::Translation<float,3> translation(msg.transform.translation.x, msg.transform.translation.y, msg.transform.translation.z);
//        Eigen::Quaternion<float> rotation(msg.transform.rotation.w,
//                                          msg.transform.rotation.x,
//                                          msg.transform.rotation.y,
//                                          msg.transform.rotation.z);
//        std::cerr << "tmp:\n" << tmpTransform.matrix() << std::endl;

        if (i == 0) kinectReference = tmpTransform;
        else kinect2kinectTransform[i-1] = kinectReference * tmpTransform.inverse();
    }
//    std::cerr << "Kinect Ref:\n" << kinectReference.matrix() << std::endl;
}