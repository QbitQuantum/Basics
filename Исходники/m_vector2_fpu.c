M_Real
M_VectorVecAngle2_FPU(M_Vector2 vOrig, M_Vector2 vOther)
{
	M_Vector2 vd;
	
	vd = M_VectorSub2p_FPU(&vOther, &vOrig);
	return (Atan2(vd.y, vd.x));
}