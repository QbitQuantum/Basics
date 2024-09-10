// Variance Ratio
double getVR(Mat hist1,Mat hist2)
{
	Mat idx=Mat::zeros(hist1.rows,hist1.cols,CV_32FC1);
	for (int i=0;i<idx.rows;++i)
	{
		float* r_ptr=idx.ptr<float>(i);
		r_ptr[0]=(float)i;
	}
	double mean_idx=hist1.dot(idx);
	Mat temp=idx-mean_idx;
	temp=temp.mul(temp);
	double variance1=hist1.dot(temp);

	mean_idx=hist2.dot(idx);
	temp=idx-mean_idx;
	temp=temp.mul(temp);
	double variance2=hist2.dot(temp);

	Mat hist_mean=(hist1+hist2)*0.5;
	mean_idx=hist_mean.dot(idx);
	temp=idx-mean_idx;
	temp=temp.mul(temp);
	double variance_mean=hist_mean.dot(temp);

	return variance_mean/(variance1+variance2);
}