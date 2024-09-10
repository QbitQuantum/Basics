void CGraphic::Draw3DPlane(ITexture* pTexture, CVector3f *vec3d, DWORD Color, ERenderStyle RS, CVector2f *tex_uv)
{
	if ( pTexture )
	{
		VerColorTex vs[4] =
		{
			VerColorTex( vec3d[0].x, vec3d[0].y, vec3d[0].z, Color, tex_uv[0].x, tex_uv[0].y),
			VerColorTex( vec3d[1].x, vec3d[1].y, vec3d[1].z, Color, tex_uv[1].x, tex_uv[1].y),
			VerColorTex( vec3d[2].x, vec3d[2].y, vec3d[2].z, Color, tex_uv[2].x, tex_uv[2].y),
			VerColorTex( vec3d[3].x, vec3d[3].y, vec3d[3].z, Color, tex_uv[3].x, tex_uv[3].y),
		};
		VerColorTex* pVB;
		RenderState * pRS;

		CMatrix view;
		CCamera *pCamera = m_pActiveTarget->GetCamera();
		CMatrix	matBillboard;
		view = pCamera->getViewMatrix();
		matBillboard.Identity();
		matBillboard._11 = view._11;
		matBillboard._12 = view._12;
		matBillboard._13 = view._13;
		matBillboard._21 = view._21;
		matBillboard._22 = view._22;
		matBillboard._23 = view._23;
		matBillboard._31 = view._31;
		matBillboard._32 = view._32;
		matBillboard._33 = view._33;
		matBillboard.Invert();

		CMatrix *m_Mat = GetRenderStack( RS, pTexture, NULL, PT_TRIANGLESTRIP, 4, 2,
			VerColorTex::Format , sizeof(VerColorTex), (void**)&pVB, NULL, (void**)&pRS );
		m_Mat->Identity();
		m_Mat->_11 = matBillboard._11;
		m_Mat->_12 = matBillboard._12;
		m_Mat->_13 = matBillboard._13;
		m_Mat->_21 = matBillboard._21;
		m_Mat->_22 = matBillboard._22;
		m_Mat->_23 = matBillboard._23;
		m_Mat->_31 = matBillboard._31;
		m_Mat->_32 = matBillboard._32;
		m_Mat->_33 = matBillboard._33;
		m_Mat->_41 = vec3d[4].x;
		m_Mat->_42 = vec3d[4].y;
		m_Mat->_43 = vec3d[4].z;

		pRS->m_TexOP_S0 = TOP_SELECTARG1;
		pRS->m_TexArg1_S0 = TA_TEXTURE;
		memcpy(pVB,vs,sizeof(vs));
	}

}