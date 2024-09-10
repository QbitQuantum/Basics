MStatus IFFimageReader::getDepth (int x, int y, float *d)
{
	if (NULL == fZBuffer || NULL == d)
		return MS::kFailure;
	int width,height;
	ILgetsize (fImage, &width, &height);
	if (x >= width || y >= height || x < 0 || y < 0)
		return MS::kFailure;
	float depth = fZBuffer [y * width + x];
	if (depth == 0.)
		*d = 0.;
	else
		*d = -1.0f/depth;
	return MS::kSuccess;
}