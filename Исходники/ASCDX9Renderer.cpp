ASCMatrix4 
ASCDX9Renderer::CreateProjectionMatrix( FLOAT32 fFOV, FLOAT32 fAspect, FLOAT32 fNear, FLOAT32 fFar )
{
	//Assume a LH perspective matrix

	ASCMatrix4 matReturn;
	XMMATRIX matResult;

	//matResult = XMMatrixPerspectiveFovLH(  DegsToRad(fFOV), fAspect, fNear, fFar );
	matResult = XMMatrixOrthographicLH(  fFOV, fAspect, fNear, fFar );

	matReturn = *reinterpret_cast<ASCMatrix4*>(&matResult);

	return matReturn;
}