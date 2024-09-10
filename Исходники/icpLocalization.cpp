void ICPLocalization::addScanLineToPointCloud(Eigen::Affine3d body2Odo, Eigen::Affine3d body2World, Eigen::Affine3d laser2Body, const ::base::samples::LaserScan &scan_reading)
{

    if(scansWithTransforms.size() == 0) 
    {
	addLaserScan(body2Odo,body2World,laser2Body,scan_reading); 
	return;
    }
    
    /*
    double max_rotation =  1.5 * conf_point_cloud.lines_per_point_cloud * conf_point_cloud.min_rotation_for_new_line;
    double max_translation = 1.5 * conf_point_cloud.lines_per_point_cloud * conf_point_cloud.min_distance_travelled_for_new_line;
    double max_head_movement = 1.5 * conf_point_cloud.lines_per_point_cloud * conf_point_cloud.min_rotation_head_for_new_line; 
    */
    bool add_laser_scan = true; 
    for( uint i = 0; i < scansWithTransforms.size(); i++) 
    {
	Eigen::Affine3d diference( body2Odo.inverse() * scansWithTransforms.at(i).body2Odo );

	Vector3d Ylaser2Body = laser2Body * Vector3d::UnitY() - laser2Body.translation();
	Ylaser2Body.normalize();
	Vector3d YlastLaser2Body = scansWithTransforms.back().laser2Body * Vector3d::UnitY() - scansWithTransforms.at(i).laser2Body.translation();
	YlastLaser2Body.normalize();
	
	double laserChange = acos(Ylaser2Body.dot(YlastLaser2Body));
	double translation =  diference.translation().norm(); 
	double rotation = fabs(Eigen::AngleAxisd( diference.rotation() ).angle()) ; 
	
	add_laser_scan = add_laser_scan && ( rotation > conf_point_cloud.min_rotation_for_new_line || translation > conf_point_cloud.min_distance_travelled_for_new_line || laserChange >  conf_point_cloud.min_rotation_head_for_new_line);
	 
	//if  the distance is to big means the old laser scan is not consistent anymore. 
// 	if( rotation > max_rotation|| translation > max_translation || laserChange > max_head_movement)
// 	{
// 	    scansWithTransforms.erase(scansWithTransforms.begin() + i); 
// 	    scanCount--; 
// 	    std::cout << " IcpLocalization.cpp erasing old laser scan " << std::endl; 
// 	}

/*	std::cout <<" add new scan " << add_laser_scan << std::endl; 
	std::cout << "\t translation " << (translation > conf_point_cloud.min_distance_travelled_for_new_line)<< " "  << translation << " > " << conf_point_cloud.min_distance_travelled_for_new_line << std::endl;
	std::cout << "\t rotation " << (rotation > conf_point_cloud.min_rotation_for_new_line) << " "  << rotation * 180 / M_PI << " > " << conf_point_cloud.min_rotation_for_new_line * 180 / M_PI << std::endl;
	std::cout << "\t head " << (laserChange >  conf_point_cloud.min_rotation_head_for_new_line) << "  "<< laserChange * 180 / M_PI << " > " << conf_point_cloud.min_rotation_head_for_new_line * 180 / M_PI<< std::endl; */
	
	if (!add_laser_scan) 
	    break; 
    }
    
    if ( add_laser_scan )
    {
	addLaserScan(body2Odo,body2World,laser2Body,scan_reading); 
    }
    
    return; 
  
}