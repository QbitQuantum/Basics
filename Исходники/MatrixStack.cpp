void MatrixStack::Ortho(float width,float height,float znear,float zfar){
	m_Projection=XMMatrixOrthographicLH(width,height,znear,zfar);
}