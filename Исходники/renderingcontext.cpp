void CRenderingContext::RenderText(const tstring& sText, unsigned iLength, FTFont* pFont)
{
	TAssert(m_pShader);
	if (!m_pShader)
		return;

	CRenderContext& oContext = GetContext();

	if (iLength == -1)
		iLength = sText.length();

	TAssert(m_pShader->m_iPositionAttribute >= 0);
	TAssert(m_pShader->m_aiTexCoordAttributes[0] >= 0);

	if (!oContext.m_bProjectionUpdated)
		SetUniform("mProjection", oContext.m_mProjection);

	if (!oContext.m_bViewUpdated)
		SetUniform("mView", oContext.m_mView);

	// Take the position out and let FTGL do it. It looks sharper that way.
	Matrix4x4 mTransformations = oContext.m_mTransformations;
	Vector vecPosition = mTransformations.GetTranslation();
	mTransformations.SetTranslation(Vector());
	SetUniform("mGlobal", mTransformations);

	oContext.m_bProjectionUpdated = oContext.m_bViewUpdated = oContext.m_bTransformUpdated = true;

	ftglSetAttributeLocations(m_pShader->m_iPositionAttribute, m_pShader->m_aiTexCoordAttributes[0]);

	pFont->Render(sText.c_str(), iLength, FTPoint(vecPosition.x, vecPosition.y, vecPosition.z));
}