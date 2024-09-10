WeightedLeastSquares::VectorialImageTensorType::Pointer  WeightedLeastSquares::ComputeDelSim(TensorImageType::Pointer tensorImage)
{
	ScalarImageIterator itHRMask(m_HRmask, m_HRmask->GetLargestPossibleRegion());
	
	TensorImageType::Pointer delSim = TensorImageType::New();
	CopyImage cpImage;
	cpImage.CopyTensorImage(tensorImage, delSim);
	
	TensorImageIterator itDelSim(delSim, delSim->GetLargestPossibleRegion());

	int numOfImages = m_DWIListHR.size();

	//ComputePredictedImage;
	ImageListType PredImageList = ComputePredictedImage(tensorImage);

	//ComputeDifferenceImageList
	ImageListType DiffImageList = ComputeDifferenceImage(PredImageList);

	ScalarImageType::IndexType tempIndex;
	tempIndex[0] = 70; 
	tempIndex[1] = 109;
	tempIndex[2] = 81;

	VectorialImageTensorType::Pointer DelSim = VectorialImageTensorType::New();
	DelSim->SetOrigin(m_HRmask->GetOrigin());
	DelSim->SetDirection(m_HRmask->GetDirection());
	DelSim->SetSpacing(m_HRmask->GetSpacing());
	DelSim->SetRegions(m_HRmask->GetLargestPossibleRegion());
	DelSim->Allocate();
	
	VectorialTensorType  ZeroVecTensor; ZeroVecTensor.Fill(0);
	DelSim->FillBuffer(ZeroVecTensor);	
	
	for(itHRMask.GoToBegin(), itDelSim.GoToBegin(); !itHRMask.IsAtEnd(), !itDelSim.IsAtEnd() ; ++itHRMask, ++itDelSim)
	{
	
	 if (itHRMask.Get() != 0)
	{
		vnl_matrix<double> W; W.set_size(numOfImages, 7);
		vnl_vector<double> S_vec; S_vec.set_size(numOfImages);
		vnl_diag_matrix<double> S;
		vnl_vector<double> r;
		r.set_size(numOfImages);	
		DiffusionTensorType D = tensorImage->GetPixel(itHRMask.GetIndex());
		vnl_matrix<double> J = ComputeJacobian(D);		

		 for(int i=0; i < numOfImages; i++)
		{
			
			//Create W 
			vnl_vector<double> W_row_i = ComputeWeightMatrixRow(m_GradList[i]->GetPixel(itHRMask.GetIndex()));
			W.set_row(i, W_row_i);		
		
			// Create S
			S_vec[i] = PredImageList[i]->GetPixel(itHRMask.GetIndex());
			//Create r
			r[i] = DiffImageList[i]->GetPixel(itHRMask.GetIndex());	
				
		}
			vnl_vector<double> delF; 
			S.set(S_vec);
			delF = W.transpose()*S*r;
			VectorialTensorType tempDelF;
			tempDelF.SetVnlVector(delF);
			DelSim->SetPixel(itHRMask.GetIndex(), tempDelF);
	
	}
	}
	
	return DelSim;
}