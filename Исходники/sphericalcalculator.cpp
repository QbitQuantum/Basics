void SphericalCalculator::addFace(std::vector<Face> &faces,const Point &a,const Point &b,const Point &c)
{
    Face f;
    f.x[0][0]=a.x[0];
    f.x[0][1]=a.x[1];
    f.x[0][2]=a.x[2];

    f.x[1][0]=b.x[0];
    f.x[1][1]=b.x[1];
    f.x[1][2]=b.x[2];

    f.x[2][0]=c.x[0];
    f.x[2][1]=c.x[1];
    f.x[2][2]=c.x[2];

    QVector3D aa(f.x[0][0],f.x[0][1],f.x[0][2]);
    QVector3D bb(f.x[1][0],f.x[1][1],f.x[1][2]);
    QVector3D cc(f.x[2][0],f.x[2][1],f.x[2][2]);

    QVector3D nv;
    nv=-QVector3D::crossProduct(bb-aa,cc-aa);
    nv.normalize();
    f.n[0]=nv.x();
    f.n[1]=nv.y();
    f.n[2]=nv.z();
    
     faces.push_back(f);
    
}