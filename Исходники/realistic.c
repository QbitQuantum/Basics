RealisticCamera::RealisticCamera(const AnimatedTransform &cam2world,
				 float hither, float yon, 
				 float sopen, float sclose, 
				 float filmdistance, float aperture_diameter, string specfile, 
				 float filmdiag, Film *f)
	: Camera(cam2world, sopen, sclose, f) // pbrt-v2 doesnot specify hither and yon
{
	// YOUR CODE HERE -- build and store datastructures representing the given lens
	// and film placement.

	this->hither = hither, this->yon = yon, this->aperture_diameter = aperture_diameter;
	this->filmdistance = filmdistance, this->filmdiag = filmdiag;
	
	// read lens spec file
	this->distToBack = ReadSpecFile(specfile);

	// compute transform: raster to camera, film to camera
	float diag = hypotf(f->xResolution, f->yResolution);
	float scale = filmdiag / diag;
	float X = scale * f->xResolution * 0.5f;
	float Y = scale * f->yResolution * 0.5f;
	RasterToCamera = Translate(Vector(0.f, 0.f, -(this->filmdistance + this->distToBack))) * 
					 Translate(Vector(X, -Y, 0.f)) *
					 Scale(-scale, scale, 1);
}