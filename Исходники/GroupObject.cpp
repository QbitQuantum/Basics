void CGroupObject::NumSetRotation(const Fvector& rot)
{
	Fvector old_r;
    FTransformR.getXYZ(old_r);
	inherited::NumSetRotation(rot);
    Fmatrix prev; prev.invert(FTransform);
    UpdateTransform(true);

    Fvector dr; dr.sub(FRotation,old_r);
	for (ObjectIt it=m_Objects.begin(); it!=m_Objects.end(); it++){
    	Fvector r=(*it)->PRotation; r.add(dr); (*it)->PRotation=r;
    	Fvector v=(*it)->PPosition;
        prev.transform_tiny(v);
        FTransform.transform_tiny(v);
    	(*it)->PPosition=v;
    }
}