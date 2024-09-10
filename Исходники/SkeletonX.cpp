void 	get_pos_bones(const vertBoned2W &vert, Fvector& p, CKinematics* Parent )
{
	Fvector		P0,P1;
	
	Fmatrix& xform0			= Parent->LL_GetBoneInstance( vert.matrix0 ).mRenderTransform; 
	Fmatrix& xform1			= Parent->LL_GetBoneInstance( vert.matrix1 ).mRenderTransform; 
	xform0.transform_tiny	( P0, vert.P );
	xform1.transform_tiny	( P1, vert.P );
	p.lerp					( P0, P1, vert.w );
}