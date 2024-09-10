void visualizerShowCamera(const Matrix3f& R, const Vector3f& _t, float r, float g, float b, double s = 0.01 /*downscale factor*/, const std::string& name = "") {
	std::string name_ = name,line_name = name + "line";
	if (name.length() <= 0) {
		stringstream ss; ss<<"camera"<<iCamCounter++;
		name_ = ss.str();
		ss << "line";
		line_name = ss.str();
	}
	
	Vector3f t = -R.transpose() * _t;

	Vector3f vright = R.row(0).normalized() * s;
	Vector3f vup = -R.row(1).normalized() * s;
	Vector3f vforward = R.row(2).normalized() * s;

	Vector3f rgb(r,g,b);

	pcl::PointCloud<pcl::PointXYZRGB> mesh_cld;
	mesh_cld.push_back(Eigen2PointXYZRGB(t,rgb));
	mesh_cld.push_back(Eigen2PointXYZRGB(t + vforward + vright/2.0 + vup/2.0,rgb));
	mesh_cld.push_back(Eigen2PointXYZRGB(t + vforward + vright/2.0 - vup/2.0,rgb));
	mesh_cld.push_back(Eigen2PointXYZRGB(t + vforward - vright/2.0 + vup/2.0,rgb));
	mesh_cld.push_back(Eigen2PointXYZRGB(t + vforward - vright/2.0 - vup/2.0,rgb));

	//TODO Mutex acquire
	pcl::PolygonMesh pm;
	pm.polygons.resize(6); 
	for(int i=0;i<6;i++)
		for(int _v=0;_v<3;_v++)
			pm.polygons[i].vertices.push_back(ipolygon[i*3 + _v]);
	pcl::toROSMsg(mesh_cld,pm.cloud);
	bShowCam = true;
	cam_meshes.push_back(std::make_pair(name_,pm));
	//TODO mutex release

	linesToShow.push_back(std::make_pair(line_name,
		AsVector(Eigen2Eigen(t,rgb),Eigen2Eigen(t + vforward*3.0,rgb))
		));
}