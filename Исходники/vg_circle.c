static float
PointProximity(void *p, VG_View *vv, VG_Vector *vPt)
{
	VG_Circle *vc = p;
	VG_Vector vCenter = VG_Pos(vc->p);
	float theta = Atan2(vPt->y - vCenter.y,
	                    vPt->x - vCenter.x);
	VG_Vector vNear;
	float d;

	vNear.x = vCenter.x + vc->r*Cos(theta);
	vNear.y = vCenter.y + vc->r*Sin(theta);
	d = VG_Distance(*vPt, vNear);
	*vPt = vNear;
	return (d);
}