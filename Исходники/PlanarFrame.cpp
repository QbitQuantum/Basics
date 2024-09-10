PlanarFrame::~PlanarFrame()
{
	if (y != NULL) { _aligned_free(y); y = NULL; }
	if (u != NULL) { _aligned_free(u); u = NULL; }
	if (v != NULL) { _aligned_free(v); v = NULL; }
}