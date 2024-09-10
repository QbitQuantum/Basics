int GSphereObjCreateCallBack::proc(ViewExp *vpt, int msg, int point, int flags, IPoint2 m, Matrix3& mat ) {

	if ( ! vpt || ! vpt->IsAlive() )
	{
		// why are we here
		DbgAssert(!_T("Doing proc() on invalid viewport!"));
		return FALSE;
	}

	Point3 p1, center;

	if (msg == MOUSE_FREEMOVE)
	{
		vpt->SnapPreview(m, m, NULL, SNAP_IN_3D);
	}


	if (msg==MOUSE_POINT||msg==MOUSE_MOVE) {
		switch(point) {
		case 0:  // only happens with MOUSE_POINT msg
			ob->suspendSnap = TRUE;				
			sp0 = m;
			p0 = vpt->SnapPoint(m, m, NULL, SNAP_IN_3D);
			mat.SetTrans(p0);
			break;
		case 1:
			mat.IdentityMatrix();
			p1 = vpt->SnapPoint(m, m, NULL, SNAP_IN_3D);
			center = (p0+p1)/float(2);
			mat.SetTrans(center);
			mat.SetTrans(center);
			container_param_blk.InvalidateUI();

			if (flags&MOUSE_CTRL) {
				float ang = (float)atan2(p1.y-p0.y, p1.x-p0.x);					
				mat.PreRotateZ(ob->ip->SnapAngle(ang));
			}

			if (msg==MOUSE_POINT) {
				ob->suspendSnap = FALSE;
				return (Length(m-sp0)<3)?CREATE_ABORT:CREATE_STOP;
			}
			break;					   
		}
	} else {
		if (msg == MOUSE_ABORT) return CREATE_ABORT;
	}

	return TRUE;
}