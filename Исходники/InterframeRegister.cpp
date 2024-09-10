/**
Calculates backprojection error and returns number of points within error tolerance
@param pL: Number of indices 
@param pR: Storage of the indices
@param numMatch: Number of Matches
@param H: Storage matrix used by RunRansac function
@param ind: array to store good matches
@param totErr: array to store error matches 
@param srcIm: Source Image 
@param dstIm: Destination Image
@return void
*/
int InterframeRegister::CalcErr(vector<Point2f> pL, vector<Point2f> pR, int numMatch, Mat H, vector<int>& ind, double *totErr) 
{
	//float err;
	Mat HInv(3,3,CV_64FC1);

	// check for singularity
	double matDet = invert(H,HInv,DECOMP_LU);
	if (abs(matDet)<0.00001)
	{
		*totErr = numMatch*MATCH_ERR_THRESH;
		return 0;
	}
	
	// compute error and number of matches
	int nGoodMatches = 0;
	Mat matLeft(3, 1, CV_64FC1);
	Mat matRight (3, 1, CV_64FC1);
	Mat matLeftEst (3, 1, CV_64FC1);
	Mat matRightEst (3, 1, CV_64FC1);
	Mat matLeftDiff (3, 1, CV_64FC1);
	Mat matRightDiff (3, 1, CV_64FC1);
	
	for (int cnt = 0; cnt < numMatch; cnt++)
	{
		matLeft = (Mat_<double>(3,1) << pL[cnt].x,pL[cnt].y,1.0);
		matRightEst = H * matLeft;
		
		matRight = (Mat_<double>(3,1) << pR[cnt].x,pR[cnt].y,1.0);

		matLeftEst = HInv * matRight;
		
		for(int i = 0; i < 3; i++)
		{
			matLeftEst.data[i] /= matLeftEst.data[2];
			matRightEst.data[i] /= matRightEst.data[2];
		}
		
		matLeftDiff = matLeftEst-matLeft;
		matRightDiff = matRightEst -matRight;

		double dLeftErr = norm(matLeftDiff);
		double dRightErr = norm(matRightDiff);
		double dErr = (dLeftErr * dLeftErr) + (dRightErr * dRightErr);
		

		if (dErr<MATCH_ERR_THRESH)
		{
			*totErr = *totErr+dErr;
			ind[nGoodMatches++] = cnt;			
		}
		else *totErr = *totErr+MATCH_ERR_THRESH;
	}
	
	return nGoodMatches;
}