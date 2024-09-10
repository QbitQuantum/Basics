// Returns the point to be shaded in object coordinates.
Point3 SContext::PObj(void)
{
	SCDebugPrint("SContext::PObj\n");
	Matrix3 camToObj = Inverse(pInst->objToWorld * renderer->view.affineTM);
	return camToObj * P();
}