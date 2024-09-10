bool MyPointCloud::alignPointClouds(std::vector<Matrix3frm>& Rcam, std::vector<Vector3f>& tcam, MyPointCloud *globalPreviousPointCloud, device::Intr& intrinsics, int globalTime) {
	Matrix3frm Rprev = Rcam[globalTime - 1]; //  [Ri|ti] - pos of camera, i.e.
	Vector3f tprev = tcam[globalTime - 1]; //  tranfrom from camera to global coo space for (i-1)th camera pose
	Matrix3frm Rprev_inv = Rprev.inverse(); //Rprev.t();
	
	device::Mat33& device_Rprev_inv = device_cast<device::Mat33> (Rprev_inv);
	float3& device_tprev = device_cast<float3> (tprev);

	Matrix3frm Rcurr = Rprev; // tranform to global coo for ith camera pose
	Vector3f tcurr = tprev;
	
  #pragma omp parallel for
	for(int level = LEVELS - 1; level >= 0; --level) {
	
		int iterations = icpIterations_[level];

    #pragma omp parallel for
		for(int iteration = 0; iteration < iterations; ++iteration) {
      {
        printf("        ICP level %d iteration %d", level, iteration);
        pcl::ScopeTime time("");
			  device::Mat33& device_Rcurr = device_cast<device::Mat33> (Rcurr);
			  float3& device_tcurr = device_cast<float3>(tcurr);
		
			  Eigen::Matrix<float, 6, 6, Eigen::RowMajor> A;
			  Eigen::Matrix<float, 6, 1> b;

			  if(level == 2 && iteration == 0)			
			  	error_.create(rows_ * 4, cols_);

			  device::estimateCombined (device_Rcurr, device_tcurr, vmaps_[level], nmaps_[level], device_Rprev_inv, device_tprev, intrinsics (level),
                            globalPreviousPointCloud->getVertexMaps()[level], globalPreviousPointCloud->getNormalMaps()[level], distThres_, angleThres_, 
			  			  gbuf_, sumbuf_, A.data (), b.data (), error_);

			  //checking nullspace
			  float det = A.determinant ();

			  if (fabs (det) < 1e-15 || !pcl::device::valid_host (det)) {
			  	// printf("ICP failed at level %d, iteration %d (global time %d)\n", level, iteration, globalTime);
			  	return (false);
			  } //else printf("ICP succeed at level %d, iteration %d (global time %d)\n", level, iteration, globalTime);

			  Eigen::Matrix<float, 6, 1> result = A.llt ().solve (b);
			  //Eigen::Matrix<float, 6, 1> result = A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b);

			  float alpha = result (0);
			  float beta  = result (1);
			  float gamma = result (2);

			  Eigen::Matrix3f Rinc = (Eigen::Matrix3f)AngleAxisf (gamma, Vector3f::UnitZ ()) * AngleAxisf (beta, Vector3f::UnitY ()) * AngleAxisf (alpha, Vector3f::UnitX ());
			  Vector3f tinc = result.tail<3> ();

			  //compose
			  tcurr = Rinc * tcurr + tinc;
			  Rcurr = Rinc * Rcurr;
      }
		}
	
	}

	//save tranform
	Rcam[globalTime] = Rcurr;
	tcam[globalTime] = tcurr;
	return (true);

}