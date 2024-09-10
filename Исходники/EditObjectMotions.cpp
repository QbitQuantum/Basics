//----------------------------------------------------
// Skeletal motion
//----------------------------------------------------
static void CalculateAnim(CBone* bone, CSMotion* motion, Fmatrix& parent)
{
    Flags8 flags; flags.zero();
    if (motion) flags 	= motion->GetMotionFlags(bone->SelfID);

    Fmatrix& M 		= bone->_MTransform();
    Fmatrix& L 		= bone->_LTransform();
    
    const Fvector& r = bone->_Rotate();
    if (flags.is(st_BoneMotion::flWorldOrient)){
        M.setXYZi	(r.x,r.y,r.z);
        M.c.set		(bone->_Offset());
        L.mul		(parent,M);
        L.i.set		(M.i);
        L.j.set		(M.j);
        L.k.set		(M.k);

        Fmatrix		 LI; LI.invert(parent);
        M.mulA_43	(LI);
    }else{
        M.setXYZi	(r.x,r.y,r.z);
        M.c.set		(bone->_Offset());
        L.mul		(parent,M);
    }
	bone->_RenderTransform().mul_43(bone->_LTransform(),bone->_RITransform());
    
    // Calculate children
    for (BoneIt b_it=bone->children.begin(); b_it!=bone->children.end(); b_it++)
    	CalculateAnim	(*b_it,motion,bone->_LTransform());
}