bool poseEstimationFunction(kuri_mbzirc_challenge_1_msgs::PES::Request  &req,
                            kuri_mbzirc_challenge_1_msgs::PES::Response &res)
{
    tf::Transform BaseToCamera;
    double imageWidth = 1228 ;
    double imagehight = 1027 ;
    BaseToCamera.setOrigin(tf::Vector3(0.0, 0.0, -0.045));
    //BaseToCamera.setRotation(tf::Quaternion(0.707, -0.707, 0.000, -0.000));
    BaseToCamera.setRotation(tf::Quaternion(0.9999060498015511, 0, 0, -0.013707354604664749));

    tf::Transform extrisic;
    cv::Mat P_Mat_G(3, 4, CV_64FC1);
    //cv::Mat P(3, 4, CV_64FC1);
    tfScalar extrisic_data[4 * 4];
    pcl::PointCloud<pcl::PointXYZRGB> Pointcloud;
    Pointcloud.header.frame_id = "/world";
    Pointcloud.height = imagehight;
    Pointcloud.width = imageWidth;
    Pointcloud.resize(imagehight * imageWidth);
    Pointcloud.is_dense = true;
    // cv::Mat cvimg = cv_bridge::toCvShare(img, "bgr8")->image.clone();
    //tf::poseMsgToTF(odom->pose.pose, tfpose);
    extrisic = BaseToCamera * tfpose.inverse();
    //to test if the tf is correct, create testframe_to_camera
    //br.sendTransform(tf::StampedTransform(extrisic, ros::Time::now(), "/testframe_to_camera", "/world"));
    //pinv of projection matrix...
    /*for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
        {
            P.at<double>(i, j) = cam_info.P.at(i * 4 + j);
            //  std::cout << "PP" << P  << std::endl ;
        }*/
    //however, this P is in camera coordinate..
    extrisic.getOpenGLMatrix(extrisic_data);
    cv::Mat E_MAT(4, 4, CV_64FC1, extrisic_data);
    P_Mat_G = P * (E_MAT.t());
    // now is the ground, namely, world coordinate
    double a[4], b[4], c[4];
    a[0] = P_Mat_G.at<double>(0, 0);
    a[1] = P_Mat_G.at<double>(0, 1);
    a[2] = P_Mat_G.at<double>(0, 2);
    a[3] = P_Mat_G.at<double>(0, 3);
    b[0] = P_Mat_G.at<double>(1, 0);
    b[1] = P_Mat_G.at<double>(1, 1);
    b[2] = P_Mat_G.at<double>(1, 2);
    b[3] = P_Mat_G.at<double>(1, 3);
    c[0] = P_Mat_G.at<double>(2, 0);
    c[1] = P_Mat_G.at<double>(2, 1);
    c[2] = P_Mat_G.at<double>(2, 2);
    c[3] = P_Mat_G.at<double>(2, 3);
    std::clock_t start;
    //double duration;
    start = std::clock();

    // ************************** find 3D point ******************** //

    // just for the detected point
    float B[2][2], bvu[2];
    B[0][0] = req.A  * c[0] - a[0];
    B[0][1] = req.A  * c[1] - a[1];
    B[1][0] = req.B  * c[0] - b[0];
    B[1][1] = req.B  * c[1] - b[1];
    bvu[0] = a[2] * Ground_Z + a[3] - req.A  * c[2] * Ground_Z - req.A  * c[3];
    bvu[1] = b[2] * Ground_Z + b[3] - req.B  * c[2] * Ground_Z - req.B  * c[3];
    float DomB = B[1][1] * B[0][0] - B[0][1] * B[1][0];
    //res.obj.pose.pose.position.x  = (B[1][1] * bvu[0] - B[0][1] * bvu[1]) / DomB ;
    //res.obj.pose.pose.position.y  = (B[0][0] * bvu[1] - B[1][0] * bvu[0]) / DomB ;
    res.X   = ((B[1][1] * bvu[0] - B[0][1] * bvu[1]) / DomB)  / 10000000 ;
    res.Y   = ((B[0][0] * bvu[1] - B[1][0] * bvu[0]) / DomB ) / 10000000;
    res.Z = 2 ;
    //res.obj.pose.pose.position.z = 0 ;
    //ROS_INFO("request: x=%ld, y=%ld", (long int)req.A, (long int)req.B);
    //ROS_INFO("sending back response: [%ld]", (long int)res.obj.pose.pose.position.x);
    //std::cout << "request " << req.A << "    " << req.B << std::endl ; 
    //std::cout << "response" << res.X << "    " << res.Y << std::endl ; 
    
    ROS_INFO("request: x=%f, y=%f", (float)req.A, (float)req.B);
    ROS_INFO("sending back response: x=%f, y=%f", (float)res.X , (float)res.Y);
    return true;
}