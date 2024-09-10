// The plane primitive command was called
void CRegionView::OnCreatePrimitivePlane() 
{
	// The sphere primitive dialog
	CPlanePrimitiveDlg dlg;

	//load all the defaults from the registry
	dlg.m_fWidth				= (float)::GetApp()->GetOptions().GetDWordValue("DefaultPlaneWidth", 64);
	dlg.m_fHeight				= (float)::GetApp()->GetOptions().GetDWordValue("DefaultPlaneHeight", 64);
	dlg.m_nOrientation			= ::GetApp()->GetOptions().GetDWordValue("DefaultPlaneOr", 0);
	dlg.m_nType					= ::GetApp()->GetOptions().GetDWordValue("DefaultPlaneType", 0);


	// Create the sphere primitive dialog	
	if (dlg.DoModal() == IDOK)
	{
		//determine our up and right vectors for each orientation
		LTVector vOrUp[6], vOrNormal[6];

		vOrNormal[0].Init(1.0f, 0.0f, 0.0f);	vOrUp[0].Init(0.0f, 1.0f, 0.0f);
		vOrNormal[1].Init(-1.0f, 0.0f, 0.0f);	vOrUp[1].Init(0.0f, 1.0f, 0.0f);
		vOrNormal[2].Init(0.0f, 1.0f, 0.0f);	vOrUp[2].Init(0.0f, 0.0f, 1.0f);
		vOrNormal[3].Init(0.0f, -1.0f, 0.0f);	vOrUp[3].Init(0.0f, 0.0f, 1.0f);
		vOrNormal[4].Init(0.0f, 0.0f, 1.0f);	vOrUp[4].Init(0.0f, 1.0f, 0.0f);
		vOrNormal[5].Init(0.0f, 0.0f, -1.0f);	vOrUp[5].Init(0.0f, 1.0f, 0.0f);

		//form the right vector
		LTVector vUp	= vOrUp[dlg.m_nOrientation];
		LTVector vRight = vUp.Cross(vOrNormal[dlg.m_nOrientation]);

		//now form the basis point
		LTVector vBasis = GetRegion()->m_vMarker - vRight * dlg.m_fWidth / 2.0f - vUp * dlg.m_fHeight / 2.0f;

		//determine the base point
		DoCreatePrimitivePlane(vBasis, vRight, vUp, dlg.m_fWidth, dlg.m_fHeight, (dlg.m_nType == 1));

		//save the options back out
		::GetApp()->GetOptions().SetDWordValue("DefaultPlaneWidth", (uint32)dlg.m_fWidth);
		::GetApp()->GetOptions().SetDWordValue("DefaultPlaneHeight", (uint32)dlg.m_fHeight);
		::GetApp()->GetOptions().SetDWordValue("DefaultPlaneOr", dlg.m_nOrientation);
		::GetApp()->GetOptions().SetDWordValue("DefaultPlaneType", dlg.m_nType);
	}
}