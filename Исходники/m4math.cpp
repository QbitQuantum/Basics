// Position and Rotation
const LLMatrix4&  	LLMatrix4::initRotTrans(const F32 angle, const F32 rx, const F32 ry, const F32 rz,
											const F32 tx, const F32 ty, const F32 tz)
{
	LLMatrix3	mat(angle, rx, ry, rz);
	LLVector3	translation(tx, ty, tz);
	initMatrix(mat);
	setTranslation(translation);
	return (*this);
}