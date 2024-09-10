//obtains the orientation matrix based on the unitary vector x, 
//the vector vv corrspondent to y. z is cw defined, and vv corrected
OrientationMatrix::OrientationMatrix(Vector3D vu, Vector3D vv)
{
	vu.normalize();
	Vector3D vw=vu.cross(vv);
	vw.normalize();
	vv=vw.cross(vu);
	mat[0][0]=vu[0];mat[1][0]=vu[1];mat[2][0]=vu[2];
	mat[0][1]=vv[0];mat[1][1]=vv[1];mat[2][1]=vv[2];
	mat[0][2]=vw[0];mat[1][2]=vw[1];mat[2][2]=vw[2];
}