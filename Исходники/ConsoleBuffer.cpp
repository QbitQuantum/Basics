void CConsoleBuffer::OnFrameRender(IDirect3DDevice9 *pd3dDevice, LPD3DXFONT font, RECT rct){
	int height = rct.bottom - rct.top; // The height of one line in the buffer
	float left = (float) rct.left - 4, 
		right = (float) rct.right + 4, 
		top = (float) rct.top - 4;
	SVertex bverts[] = 
	{
		{ left,		top + (height * (int)m_iMaxLines) + 8,	0.0f,	1.0f,	0x11ffffff },
		{ left,		top,									0.0f,	1.0f,	0x11ffffff },
		{ right,	top,									0.0f,	1.0f,	0x11ffffff },
		{ right,	top + (height * (int)m_iMaxLines) + 8,	0.0f,	1.0f,	0x11ffffff },
		{ left,		top + (height * (int)m_iMaxLines) + 8,	0.0f,	1.0f,	0x11ffffff }
	};
	pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, bverts, sizeof(SVertex));

	SVertex verts[] = 
	{
		{ left,		top + (height * (int)m_iMaxLines) + 8,	0.0f,	1.0f,	0xccffffff },
		{ left,		top,									0.0f,	1.0f,	0xccffffff },
		{ right,	top,									0.0f,	1.0f,	0xccffffff },
		{ right,	top,									0.0f,	1.0f,	0xcc888888 },
		{ right,	top + (height * (int)m_iMaxLines) + 8,	0.0f,	1.0f,	0xcc888888 },
		{ left,		top + (height * (int)m_iMaxLines) + 8,	0.0f,	1.0f,	0xcc888888 }
	};
	pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, verts, sizeof(SVertex));
	
	if (m_vLines.empty())
		return;

	for (UINT i = m_start; i <= m_end; i++){
		font->DrawTextA(NULL, m_vLines[i]->GetText(), -1, &rct, DT_LEFT, D3DCOLOR_ARGB(255,255,255,255) );
		rct.top = rct.top + height;
		rct.bottom = rct.top + height;
	}
}