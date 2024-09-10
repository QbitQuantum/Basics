///////////////////////////////////
//time x y z qx qy qz qw - all floating points
void read_poses_csv(std::string poses_files, std::vector<Isometry3dTime>& poses){
  int counter=0;
  string line;
  ifstream myfile (poses_files.c_str());
  if (myfile.is_open()){
    while ( myfile.good() ){
      getline (myfile,line);
      if (line.size() > 4){
	double quat[4];
	double pos[3];
	
	int64_t dtime;
 	sscanf(line.c_str(),"%ld,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
           &dtime,
           &pos[0],&pos[1],&pos[2],
   	   &quat[1],&quat[2],&quat[3],&quat[0]); // NBNBN: note the order
	
	Eigen::Quaterniond quat2(quat[0],quat[1],quat[2],quat[3]);
	Eigen::Isometry3d pose;
	pose.setIdentity();
	pose.translation()  << pos[0] ,pos[1],pos[2];
	pose.rotate(quat2);
	
	 Isometry3dTime poseT(dtime, pose);

	counter++;
 	poses.push_back(poseT);
      }
    }
    myfile.close();
  } else{
    printf( "Unable to open poses file\n%s",poses_files.c_str());
    return;
  }    
}