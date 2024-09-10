//assumes that the Vectors are normalized
hsBool ThreePlaneIntersect(const NxVec3& norm0, const NxVec3& point0, 
                         const NxVec3& norm1, const NxVec3& point1, 
                         const NxVec3& norm2, const NxVec3& point2, NxVec3& loc)
{
    //need to make sure these planes aren't parallel
    hsBool suc=0;
    NxVec3 cross=norm1.cross( norm2);
    float denom=norm0.dot(cross);
    if(abs(denom)<0.0001) return 0;//basically paralell
    // if we are here there must be a point in 3 space
    try{
        float d1,d2,d3;
        d1=norm0.dot(point0);
        d2=norm1.dot(point1);
        d3=norm2.dot(point2);
        NxVec3 n1Xn2=norm1.cross(norm2);
        NxVec3 n2Xn0=norm2.cross(norm0);
        NxVec3 n0Xn1=norm0.cross(norm1);
        NxVec3 pos=(d1*n1Xn2+ d2*n2Xn0  + d3*n0Xn1)/(denom);
        loc.x=pos.x;
        loc.y=pos.y;
        loc.z=pos.z;
        suc= 1;
    }
    catch(...)
    {
        suc=0;
    }

    return suc;

}