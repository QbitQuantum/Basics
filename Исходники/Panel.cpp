/**
*Rotates the boundary condition properties which are used in stability analysis with variable control positions.
*@param HA is the center of rotation
*@param Qt the quaternion which defines the 3D rotation
*/
void Panel::RotateBC(CVector const &HA, Quaternion &Qt)
{
//	Qt.Conjugate(Vortex);
	static CVector WTest;
	WTest.x = VortexPos.x - HA.x;
	WTest.y = VortexPos.y - HA.y;
	WTest.z = VortexPos.z - HA.z;
	Qt.Conjugate(WTest);
	VortexPos.x = WTest.x + HA.x;
	VortexPos.y = WTest.y + HA.y;
	VortexPos.z = WTest.z + HA.z;

	WTest.x = VA.x - HA.x;
	WTest.y = VA.y - HA.y;
	WTest.z = VA.z - HA.z;
	Qt.Conjugate(WTest);
	VA.x = WTest.x + HA.x;
	VA.y = WTest.y + HA.y;
	VA.z = WTest.z + HA.z;

	WTest.x = VB.x - HA.x;
	WTest.y = VB.y - HA.y;
	WTest.z = VB.z - HA.z;
	Qt.Conjugate(WTest);
	VB.x = WTest.x + HA.x;
	VB.y = WTest.y + HA.y;
	VB.z = WTest.z + HA.z;

	WTest.x = CtrlPt.x - HA.x;
	WTest.y = CtrlPt.y - HA.y;
	WTest.z = CtrlPt.z - HA.z;
	Qt.Conjugate(WTest);
	CtrlPt.x = WTest.x + HA.x;
	CtrlPt.y = WTest.y + HA.y;
	CtrlPt.z = WTest.z + HA.z;

	WTest.x = CollPt.x - HA.x;
	WTest.y = CollPt.y - HA.y;
	WTest.z = CollPt.z - HA.z;
	Qt.Conjugate(WTest);
	CollPt.x = WTest.x + HA.x;
	CollPt.y = WTest.y + HA.y;
	CollPt.z = WTest.z + HA.z;

	Qt.Conjugate(Vortex);
	Qt.Conjugate(Normal);
}