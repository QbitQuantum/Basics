void CMatrix4::SetUnit ()
{
	SetZero();
	mat[0][0]=1;
	mat[1][1]=1;
	mat[2][2]=1;
	mat[3][3]=1;
}