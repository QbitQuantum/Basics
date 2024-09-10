int ConeAngleManipCreateCallBack::proc(ViewExp *pVpt, int msg, int point, int flags,
                                       IPoint2 m, Matrix3& mat ) {
    float r;
    Point3 p1, center;

    if (msg == MOUSE_FREEMOVE)
    {
        pVpt->SnapPreview(m, m, NULL, SNAP_IN_3D);
    }


    if (msg==MOUSE_POINT||msg==MOUSE_MOVE) {
        switch(point) {
        case 0:  // only happens with MOUSE_POINT msg
//            ob->suspendSnap = TRUE;             
            sp0 = m;
            p0 = pVpt->SnapPoint(m, m, NULL, SNAP_IN_3D);
            mat.SetTrans(p0);
            break;
        case 1:
            mat.IdentityMatrix();
            p1 = pVpt->SnapPoint(m, m, NULL, SNAP_IN_3D);
            r = Length(p1-p0);
            mat.SetTrans(p0);

            mpManip->GetPBlock()->SetValue(kConeAngleDistance, 0, r);
            ConeAngleManipBlock.InvalidateUI();

            if (msg==MOUSE_POINT) {
                return (Length(m-sp0)<3)?CREATE_ABORT:CREATE_STOP;
            }
            break;                     
        }
    } else {
        if (msg == MOUSE_ABORT) return CREATE_ABORT;
    }

    return TRUE;
}