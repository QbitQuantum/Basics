//left-handed orthographic projection matrix
aMath::aMat aMath::getOrthMat(float wide,float height,float znear,float zfar)
{
	return XMMatrixOrthographicLH(wide,height,znear,zfar);

	//2/w  0    0           0
    //0    2/h  0           0
    //0    0    1/(zf-zn)   0
    //0    0   -zn/(zf-zn)  1
  
}