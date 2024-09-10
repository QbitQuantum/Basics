ngl::Mat4 Bvh::getRotationFromZ(ngl::Vec3 _vec) const
{
    ngl::Mat4 rotM;
    float x, y, z;
    // rotate negative z axis to _vec direction
    _vec.normalize();
    ngl::Vec3 nz(0,0,-1);
    float angle = acos(_vec.dot(nz));
    ngl::Vec3 norm = _vec.cross(nz);
    if(norm.length()<= 0.0001)
    {
        x= z = 0.0;
        y = 1.0;
    }
    else
    {
        norm.normalize();
        x = norm.m_x;
        y = norm.m_y;
        z = norm.m_z;
    }

    // Axis and Angle matrix rotation see
    // http://en.wikipedia.org/wiki/Rotation_matrix for more details
    float c = cos(angle);
    float s = sin(angle);
    float C=1-c;
    float xs  = x*s;  float  ys = y*s;  float  zs = z*s;
    float xC  = x*C;  float  yC = y*C;  float  zC = z*C;
    float xyC = x*yC; float yzC = y*zC; float zxC = z*xC;

    rotM.m_m[0][0]=x*xC+c;  rotM.m_m[0][1]= xyC-zs;  rotM.m_m[0][2]= zxC+ys;
    rotM.m_m[1][0]=xyC+zs;   rotM.m_m[1][1]=y*yC+c;  rotM.m_m[1][2]= yzC-xs;
    rotM.m_m[2][0]=zxC-ys;   rotM.m_m[2][1]=yzC+xs;  rotM.m_m[2][2]=z*zC+c;
    return rotM;
}