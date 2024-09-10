//--------------------------------------------------------------------------------------------------------------------
void RDX11RenderHelper::RenderSphere(CVector3* pos, float radius)
{	
	XMMATRIX mtWorld = XMMatrixIdentity();

	mtWorld	= XMMatrixMultiply( mtWorld, XMMatrixScaling(radius, radius, radius) );
	mtWorld.r[3].x = pos->x;
	mtWorld.r[3].y = pos->y;
	mtWorld.r[3].z = pos->z;


	SetWorldTM(mtWorld);

	GLOBAL::ShaderMgr()->Begin(SHADER_POS_VS, SHADER_COLOR_PS);
	GLOBAL::RenderStateMgr()->SetRasterizer(RASTERIZER_WIRE);
	GLOBAL::RDevice()->GetRenderStrategy()->RenderGeometry(&m_Sphere);
}