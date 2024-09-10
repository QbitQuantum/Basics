int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_to_laser_scan");
    ros::NodeHandle n;
    
    ros::Rate loop_rate(2);   
    
    //Subscribe to the message we need
    ros::Subscriber s_image = n.subscribe("image_stat", 1, &imageCallback);

    //Advertise our message
    p_laserScan = n.advertise<sensor_msgs::LaserScan>("/laser_scan", 5);
    p_laserScanImage = n.advertise<sensor_msgs::Image>("/laser_scan_image", 5);
    
    ros::spin();
    
    s_image.shutdown();
    p_laserScan.shutdown();
    
    return 0;
}