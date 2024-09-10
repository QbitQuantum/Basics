void Refraction::setPostTransfoMat(const Mat4d& m)
{
	postTransfoMat=m;
	invertPostTransfoMat=m.inverse();
	postTransfoMatf.set(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
	invertPostTransfoMatf.set(invertPostTransfoMat[0], invertPostTransfoMat[1], invertPostTransfoMat[2], invertPostTransfoMat[3],
				  invertPostTransfoMat[4], invertPostTransfoMat[5], invertPostTransfoMat[6], invertPostTransfoMat[7],
				  invertPostTransfoMat[8], invertPostTransfoMat[9], invertPostTransfoMat[10], invertPostTransfoMat[11],
				  invertPostTransfoMat[12], invertPostTransfoMat[13], invertPostTransfoMat[14], invertPostTransfoMat[15]);
}