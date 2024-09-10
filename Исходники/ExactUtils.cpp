std::pair<float,float> TwoMul(float a,float b)
{
	float res = a * b;
	float err = fmaf(a,b,-res);
	return std::make_pair(res,err);
}