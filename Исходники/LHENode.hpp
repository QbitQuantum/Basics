void LHENode<ImageSigT>::executeNodeInfo()
{
	ImageSigT* input_img_sig = getInputImageSignal(INPUT_PORT_IMAGE_DATA);

	Matrix<PixelType> input_img = input_img_sig->img;
	PixelType min_val = AtomicTypeTrait<PixelType>::minval();
	PixelType max_val = AtomicTypeTrait<PixelType>::maxval();

	typedef NormalizeOperation<PixelType,float> FrontNormType;
	Matrix<float> img = input_img.transform(FrontNormType(min_val,max_val,0.0f,1.0f));

	Matrix<float> result;

	if ((m_hist_limit_ratio > 0.0f) && (m_hist_limit_ratio < 1.0f))
	{
		clheProcess(img,result);
	}
	else
	{
		lheProcess(img,result);
	}

	typedef NormalizeOperation<float,PixelType> BackNormType;
	Matrix<PixelType> output_img;
	output_img = result.transform(BackNormType(0.0f,1.0f,min_val,max_val));

	ImageSigT* output_img_sig = getOutputImageSignal(OUTPUT_PORT_LHE_RESULT_DATA);
	if (!output_img_sig)
	{
		EAGLEEYE_ERROR("sorry,output image is not correct\n");
		return;
	}

	output_img_sig->img = output_img;

	if ((m_hist_limit_ratio > 0.0f) && (m_hist_limit_ratio < 1.0f))
	{
		EAGLEEYE_INFO("finish CLHE ...\n");
	}
	else
	{
		EAGLEEYE_INFO("finish LHE ...\n");
	}
	
}