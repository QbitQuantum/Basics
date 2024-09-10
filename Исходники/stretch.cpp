StretchDeformer::StretchDeformer(TimeValue t, ModContext &mc,
                                 float stretch, float amplify, int naxis, 
                                 float from, float to, int doRegion,
                                 Matrix3& modmat, Matrix3& modinv) 
{
    Matrix3 mat;
    Interval valid;     
//    if (from==to) doRegion = FALSE;
    this->doRegion = doRegion;
    this->from = from;
    this->to   = to;
    time   = t; 

    tm = modmat;
    invtm = modinv;
    mat.IdentityMatrix();
        
    switch ( naxis ) {
    case 0: mat.RotateY( -HALFPI );      break; //X
    case 1: mat.RotateX( HALFPI );  break; //Y
    case 2: break;  //Z
    }
    SetAxis( mat );     
    assert (mc.box);
    bbox = *mc.box;
    CalcBulge(naxis, stretch, amplify);
} 