// HighContrastOp Method Definitions
void HighContrastOp::Map(const float *y, int xRes, int yRes,
		float maxDisplayY, float *scale) const {
	// Find minimum and maximum image luminances
	float minY = y[0], maxY = y[0];
	for (int i = 0; i < xRes * yRes; ++i) {
		minY = min(minY, y[i]);
		maxY = max(maxY, y[i]);
	}
	float CYmin = C(minY), CYmax = C(maxY);
	// Build luminance image pyramid
	MIPMap<float> pyramid(xRes, yRes,
	                      y, false,
						  4.f, TEXTURE_CLAMP);
	// Apply high contrast tone mapping operator
	ProgressReporter progress(xRes*yRes, "Tone Mapping"); // NOBOOK
	for (int y = 0; y < yRes; ++y) {
		float yc = (float(y) + .5f) / float(yRes);
		for (int x = 0; x < xRes; ++x) {
			float xc = (float(x) + .5f) / float(xRes);
			// Compute local adaptation luminance at $(x,y)$
			float dwidth = 1.f / float(max(xRes, yRes));
			float maxWidth = 32.f / float(max(xRes, yRes));
			float width = dwidth, prevWidth = 0.f;
			float Yadapt;
			float prevlc = 0.f;
			const float maxLocalContrast = .5f;
			while (1) {
				// Compute local contrast at $(x,y)$
				float b0 = pyramid.Lookup(xc, yc, width,
				                          0.f, 0.f, width);
				float b1 = pyramid.Lookup(xc, yc, 2.f*width,
				                          0.f, 0.f, 2.f*width);
				float lc = fabsf((b0 - b1) / b0);
				// If maximum contrast is exceeded, compute adaptation luminance
				if (lc > maxLocalContrast) {
					float t = (maxLocalContrast - prevlc) / (lc - prevlc);
					float w = Lerp(t, prevWidth, width);
					Yadapt = pyramid.Lookup(xc, yc, w,
					                        0.f, 0.f, w);
					break;
				}
				// Increase search region and prepare to compute contrast again
				prevlc = lc;
				prevWidth = width;
				width += dwidth;
				if (width >= maxWidth) {
					Yadapt = pyramid.Lookup(xc, yc, maxWidth,
					                        0.f, 0.f, maxWidth);
					break;
				}
			}
			// Apply tone mapping based on local adaptation luminance
			scale[x + y*xRes] = T(Yadapt, CYmin, CYmax, maxDisplayY) /
				Yadapt;
		}
		progress.Update(xRes); // NOBOOK
	}
	progress.Done(); // NOBOOK
}