int
FogCreateCallBack::proc(ViewExp *vpt,int msg, int point, int flags,
                               IPoint2 m, Matrix3& mat)
{	
    if ( ! vpt || ! vpt->IsAlive() )
		{
			// why are we here?
			DbgAssert(!"Doing proc() on invalid view port!");
			return FALSE;
		}
		
		Point3 p1,center;

    switch ( msg ) {
    case MOUSE_POINT:
    case MOUSE_MOVE:
        switch ( point ) {
        case 0:  // only happens with MOUSE_POINT msg
            sp0 = m;
            p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
            mat.SetTrans(p0);
            break;
        case 1:
            mat.IdentityMatrix();
            p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
            mat.SetTrans(p0);
            float radius = Length(p1-p0);
            fogObject->pblock->SetValue(PB_FOG_SIZE,
                                               fogObject->
                                               iObjParams->GetTime(), radius);
            fogObject->pmapParam->Invalidate();										
            if (flags&MOUSE_CTRL) {
                float ang = (float)atan2(p1.y-p0.y,p1.x-p0.x);
                mat.PreRotateZ(fogObject->iObjParams->SnapAngle(ang));
            }

            if (msg==MOUSE_POINT) {
                return (Length(m-sp0)<3)?CREATE_ABORT:CREATE_STOP;
            }
            break;					   
        }			
        break;
    case MOUSE_ABORT:
        return CREATE_ABORT;
    }
	
    return TRUE;
}