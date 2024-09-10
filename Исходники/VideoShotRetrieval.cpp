float CalcDistanceToFeatureLine(Mat f1, Mat f2, Mat fx)
{
	Mat a = fx - f1;
	Mat b = f2 - f1;
	double numerator   = a.dot(b);
	double denominator = b.dot(b);
	
	float muy = (float)(numerator / denominator);
	Mat   px = f1 + muy*(f2 - f1);
	return CalcVectorMagnitude((fx - px));
}