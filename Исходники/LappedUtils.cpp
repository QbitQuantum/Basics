void LappedUtils::assignSeedUV(PatchTri* seed, vec2<float> &v0st, vec2<float> &v1st, vec2<float> &v2st)
{
    float scale = .25;
    Vector4 A,B,C;
    A = seed->v0->pos;
    B = seed->v1->pos;
    C = seed->v2->pos;
    A.w = 1;
    B.w = 1;
    C.w = 1;

    Vector4 ctr = (A+B+C)/3.0;
    ctr.w=0;
    Vector4 Ap, Bp, Cp, Tp;
    Matrix4x4 transMat = getTransMat(-ctr);
    Ap = transMat*A;
    Bp = transMat*B;
    Cp = transMat*C;
    Ap.w=0;
    Bp.w=0;
    Cp.w=0;
    Vector4 norm = ((Bp-Ap).cross(Cp-Ap)).getNormalized();
    printVector4(norm);
    double angle = acos(norm.dot(Vector4(0,0,1.0,0)));
    //cout << "angle between normal and plane z=1: " << angle << endl;
    if (norm.cross(Vector4(0,0,1,0)).getMagnitude()>0.00001)
    {
        //cout << (norm.cross(Vector4(0,0,1,0))).getMagnitude() << endl;
        //cout << norm.cross(Vector4(0,0,1,0)) << endl;
        Matrix4x4 rotMat = getRotMat(Vector4(0,0,0,0),norm.cross(Vector4(0,0,1.0,0)).getNormalized(),angle);
        Ap.w = 1;
        Bp.w = 1;
        Cp.w = 1;
        Ap = rotMat*Ap;
        Bp = rotMat*Bp;
        Cp = rotMat*Cp;
        Tp = rotMat*seed->tangent;
    }
    else Tp=seed->tangent;

    Ap.w = 0;
    Bp.w = 0;
    Cp.w = 0;


    double avgLen = max(max((Ap-Cp).getMagnitude(),(Ap-Bp).getMagnitude()),(Cp-Bp).getMagnitude());
    Ap = Ap*scale/avgLen;
    Bp = Bp*scale/avgLen;
    Cp = Cp*scale/avgLen;
    Ap.w = 1;
    Bp.w = 1;
    Cp.w = 1;
    Tp.w = 0;

    seed->tangent = Tp;
    Tp.normalize();
    double tanAngle = acos(Vector4(0,1,0,0).dot(Tp));

    Matrix4x4 tanMat = getRotMat(Vector4(0,0,0,0),Vector4(0,1,0,0).cross(Tp),tanAngle);
    Ap = tanMat*Ap;
    Bp = tanMat*Bp;
    Cp = tanMat*Cp;
    Ap.w = 1;
    Bp.w = 1;
    Cp.w = 1;
    transMat = getTransMat(Vector4(.5,.5,0,0));
    Ap = transMat*Ap;
    Bp = transMat*Bp;
    Cp = transMat*Cp;


    v0st.x = Ap.x;
    v0st.y = Ap.y;
    v1st.x = Bp.x;
    v1st.y = Bp.y;
    v2st.x = Cp.x;
    v2st.y = Cp.y;
}