int TestIntersionPlane(const Plane& plane,const TVector& position,const TVector& direction, double& lamda, TVector& pNormal)
{

    double DotProduct=direction.dot(plane._Normal);
	double l2;

    //determine if ray paralle to plane
    if ((DotProduct<ZERO)&&(DotProduct>-ZERO)) 
		return 0;

    l2=(plane._Normal.dot(plane._Position-position))/DotProduct;

    if (l2<-ZERO) 
		return 0;

    pNormal=plane._Normal;
	lamda=l2;
    return 1;

}