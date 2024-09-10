double distPtTri(Vector3d p, Matrix4d m){
    /// compute distance between a triangle and a point
    double s[4];
    Vector3d a,b,c,n;
    a << m(0,0), m(0,1), m(0,2);
    b << m(1,0), m(1,1), m(1,2);
    c << m(2,0), m(2,1), m(2,2);
    n << m(3,0), m(3,1), m(3,2);
    double k=(n-a).dot(a-p);
    if(k<0) return HUGE_VALF;
    s[0]=distPtLin(p,a,b);
    s[1]=distPtLin(p,b,c);
    s[2]=distPtLin(p,c,a);
    Matrix3d A;
    A << b(0)-a(0), c(0)-a(0), n(0)-a(0),
    b(1)-a(1), c(1)-a(1), n(1)-a(1),
    b(2)-a(2), c(2)-a(2), n(2)-a(2);
    Vector3d v = A.inverse()*(p-a);
    if(v(0)>0 && v(1)>0 && v(0)+v(1)<1){
        s[3]=k*k;
    }else{
        s[3] = HUGE_VALF;
    }
    return min(min(min(s[0],s[1]),s[2]),s[3]);
}