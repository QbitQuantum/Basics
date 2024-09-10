bool CBone::Pick(float& dist, const Fvector& S, const Fvector& D, const Fmatrix& parent)
{
	Fvector start, dir;
    Fmatrix M; M.mul_43(parent,_LTransform());
    M.invert();
    M.transform_tiny(start,S);
    M.transform_dir(dir,D);
	switch (shape.type){
    case SBoneShape::stBox:		return shape.box.intersect		(start,dir,dist);		
    case SBoneShape::stSphere:  return shape.sphere.intersect	(start,dir,dist);
    case SBoneShape::stCylinder:return shape.cylinder.intersect	(start,dir,dist);
    default:
    	Fsphere S;
        S.P.set(0,0,0);
        S.R=0.025f;
        return S.intersect(start,dir,dist);
    }
}