DBOOL CLaserBeamFX::CreateObject(CClientDE *pClientDE)
{
	if (!pClientDE ) return DFALSE;
	m_pClientDE = pClientDE;

	ObjectCreateStruct	ocStruct;
	INIT_OBJECTCREATESTRUCT(ocStruct);

	ocStruct.m_ObjectType = OT_MODEL;
	ocStruct.m_Flags = FLAG_VISIBLE;

	if(m_hstrModel)		_mbscpy((unsigned char*)ocStruct.m_Filename, (const unsigned char*)m_hstrModel);
		else			_mbscpy((unsigned char*)ocStruct.m_Filename, (const unsigned char*)"Models\\Ammo\\beam.abc");

	if(m_hstrTexture)	_mbscpy((unsigned char*)ocStruct.m_SkinName, (const unsigned char*)m_hstrTexture);
		else			_mbscpy((unsigned char*)ocStruct.m_SkinName, (const unsigned char*)"Skins\\Ammo\\beamred.dtx");

	m_hObject = pClientDE->CreateObject(&ocStruct);

	// Gouraud shade and make full bright...
	DDWORD dwFlags = pClientDE->GetObjectFlags(m_hObject);
	pClientDE->SetObjectFlags(m_hObject, dwFlags | FLAG_MODELGOURAUDSHADE | FLAG_NOLIGHT);

	DFLOAT	r, g, b, a;
	pClientDE->GetObjectColor(m_hObject, &r, &g, &b, &a);
	m_pClientDE->SetObjectColor(m_hObject, r, g, b, m_fAlpha);

	return DTRUE;
}