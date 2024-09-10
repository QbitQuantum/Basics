//**************************************************************************
//
// get the whole matrix!
//==========================================================================
void ArcBallCam::getMatrix(HMatrix m) const
//==========================================================================
{
	Quat qAll = now * start;
	qAll = qAll.conjugate();   // since Ken does everything transposed
	qAll.toMatrix(m);
}