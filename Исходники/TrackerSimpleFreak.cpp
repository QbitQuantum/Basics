void btl::image::CTrackerSimpleFreak::track( const Eigen::Matrix3f& eimHomoInit_,
											 boost::shared_ptr<cv::gpu::GpuMat> acvgmShrPtrPyrBW_[4],
											 const cv::Mat& cvmMaskCurr_,
											 Eigen::Matrix3f* peimHomo_ ){
												 
	//from coarse to fine
	*peimHomo_ =  eimHomoInit_;
	cv::gpu::GpuMat cvgmMaskPrev; cvgmMaskPrev.upload(_cvmMaskPrev);
	cv::gpu::GpuMat cvgmMaskCurr; cvgmMaskCurr.upload(cvmMaskCurr_);
	cv::gpu::GpuMat cvgmBuffer;
	for (unsigned int uLevel = _uPyrHeight-1; uLevel >= -1; uLevel--){
		for (int n = 0; n < 5; n++){ //iterations
			btl::device::cudaFullFrame( *_acgvmShrPtrPyrBWPrev[uLevel], cvgmMaskPrev, *acvgmShrPtrPyrBW_[uLevel], cvgmMaskCurr, peimHomo_->data(), &cvgmBuffer);
			//solve out the delta homography
			Eigen::Matrix3f eimDeltaHomo; eimDeltaHomo.setZero();
			extractHomography(cvgmBuffer,&eimDeltaHomo);
			*peimHomo_ += eimDeltaHomo; 
		}//iterations
	}//for pyramid
	return;
}