void CCubicGrids::integrateFeatures( const pcl::device::Intr& cCam_, const Matrix3f& Rw_, const Vector3f& Tw_, int nFeatureScale_,
												  GpuMat& pts_curr_, GpuMat& nls_curr_,
												  GpuMat& gpu_key_points_curr_, const GpuMat& gpu_descriptor_curr_, const GpuMat& gpu_distance_curr_, const int nEffectiveKeypoints_,
												  GpuMat& gpu_inliers_, const int nTotalInliers_){

	using namespace btl::device;

	//Note: the point cloud int cFrame_ must be transformed into world before calling it, i.e. it integrate a VMap NMap in world to the volume in world
	//get VMap and NMap in world
	Matrix3f tmp = Rw_;
	pcl::device::Mat33& devRwCurTrans = pcl::device::device_cast<pcl::device::Mat33> ( tmp );	//device cast do the transpose implicitly because eimcmRwCur is col major by default.
	//Cw = -Rw'*Tw
	Eigen::Vector3f eivCwCur = - Rw_.transpose() * Tw_ ;
	float3& devCwCur = pcl::device::device_cast<float3> (eivCwCur);
	
	//locate the volume coordinate for each feature, if the feature falls outside the volume, just remove it.
	cuda_nonmax_suppress_n_integrate ( _intrinsics, devRwCurTrans, devCwCur, _VolumeResolution,
								_gpu_YXxZ_tsdf, _fVolumeSizeM, _fVoxelSizeM,
								_fFeatureVoxelSizeM, _nFeatureScale, _vFeatureResolution, _gpu_YXxZ_vg_idx,
								pts_curr_, nls_curr_, gpu_key_points_curr_, gpu_descriptor_curr_, gpu_distance_curr_, nEffectiveKeypoints_,
								gpu_inliers_, nTotalInliers_, &_gpu_feature_volume_coordinate, &_gpu_counter,
								&_vTotalGlobal, &_gpu_global_3d_key_points, &_gpu_global_descriptors);

	PRINT(_vTotalGlobal[0]);
	return;
}