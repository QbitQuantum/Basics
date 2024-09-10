void CPUTracker::ComputeQuadrantProfile(scalar_t* dst, int radialSteps, int angularSteps,
				int quadrant, float minRadius, float maxRadius, vector2f center ,float* radialWeights)
{
	const int qmat[] = {
		1, 1,
		-1, 1,
		-1, -1,
		1, -1 };
	int mx = qmat[2*quadrant+0];
	int my = qmat[2*quadrant+1];

	if (angularSteps < MIN_RADPROFILE_SMP_COUNT)
		angularSteps = MIN_RADPROFILE_SMP_COUNT;

	for (int i=0;i<radialSteps;i++)
		dst[i]=0.0f;

	scalar_t total = 0.0f;
	scalar_t rstep = (maxRadius - minRadius) / radialSteps;
	for (int i=0;i<radialSteps; i++) {
		scalar_t sum = 0.0f;
		scalar_t r = minRadius + rstep * i;

		int nPixels = 0;
		scalar_t angstepf = (scalar_t) quadrantDirs.size() / angularSteps;
		for (int a=0;a<angularSteps;a++) {
			int i = (int)angstepf * a;
			scalar_t x = center.x + mx*quadrantDirs[i].x * r;
			scalar_t y = center.y + my*quadrantDirs[i].y * r;

			bool outside;
			scalar_t v = Interpolate(srcImage,width,height, x,y, &outside);
			if (!outside) {
				sum += v;
				nPixels++;
				MARKPIXELI(x,y);
			}
		}

		dst[i] = nPixels>=MIN_RADPROFILE_SMP_COUNT ? sum/nPixels : mean;
		if (radialWeights) dst[i] *= radialWeights[i];
		total += dst[i];
	}
	#ifdef QI_DBG_EXPORT
	WriteImageAsCSV(SPrintf("qprof%d.txt", quadrant).c_str(), dst, 1, radialSteps);
	#endif
}