void CUDABuildLinearSystemRGBD::applyBL(CameraTrackingInput cameraTrackingInput, Eigen::Matrix3f& intrinsics, CameraTrackingParameters cameraTrackingParameters, float3 anglesOld, float3 translationOld, unsigned int imageWidth, unsigned int imageHeight, unsigned int level, Matrix6x7f& res, LinearSystemConfidence& conf) 
{
	unsigned int localWindowSize = 12;
	if(level != 0) localWindowSize = max(1, localWindowSize/(4*level));

	const unsigned int blockSize = 64;
	const unsigned int dimX = (unsigned int)ceil(((float)imageWidth*imageHeight)/(localWindowSize*blockSize));

	Eigen::Matrix3f intrinsicsRowMajor = intrinsics.transpose(); // Eigen is col major / cuda is row major
	computeNormalEquations(imageWidth, imageHeight, d_output, cameraTrackingInput, intrinsicsRowMajor.data(), cameraTrackingParameters, anglesOld, translationOld, localWindowSize, blockSize);

	cutilSafeCall(cudaMemcpy(h_output, d_output, sizeof(float)*30*dimX, cudaMemcpyDeviceToHost));

	// Copy to CPU
	res = reductionSystemCPU(h_output, dimX, conf);
}