bool CameraPoseFinderICP::minimizePointToPlaneErrFunc(unsigned level,Eigen::Matrix<float, 6, 1> &six_dof,const Mat44& cur_transform,const Mat44& last_transform_inv)
{
	cudaCalPointToPlaneErrSolverParams( level,cur_transform,last_transform_inv, _camera_params_pyramid[level],AppParams::instance()->_icp_params.fDistThres,
			AppParams::instance()->_icp_params.fNormSinThres);
	CudaMap1D<float> buf=(CudaDeviceDataMan::instance()->rigid_align_buf_reduced).clone(CPU);
	int shift = 0;
	Eigen::Matrix<float, 6, 6, Eigen::RowMajor> ATA;
	Eigen::Matrix<float, 6, 1> ATb;
	for (int i = 0; i < 6; ++i)  //rows
	{
		for (int j = i; j < 7; ++j)    // cols + b
		{
			float value = buf.at(shift++);
			if (j == 6)
			{
				ATb(i) = value;
			}
			else
			{
				ATA(i, j) = value;
				ATA(j, i) = value;
			}
		}
	}
	//cout<<ATb<<endl;
	if (ATA.determinant()<1E-10)
	{
		return false;
	}

	six_dof = ATA.llt().solve(ATb).cast<float>();
	return true;
}