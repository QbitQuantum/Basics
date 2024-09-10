void C_VGuiScreen::OnDataChanged( DataUpdateType_t type )
{
	BaseClass::OnDataChanged( type );

	if ((type == DATA_UPDATE_CREATED) || (m_nPanelName != m_nOldPanelName))
	{
		CreateVguiScreen( PanelName() );
		m_nButtonState = 0;
	}

	// Set up the overlay material
	if (m_nOldOverlayMaterial != m_nOverlayMaterial)
	{
		m_OverlayMaterial.Shutdown();

		const char *pMaterialName = GetMaterialNameFromIndex(m_nOverlayMaterial);
		if (pMaterialName)
		{
			m_OverlayMaterial.Init( pMaterialName, TEXTURE_GROUP_VGUI );
		}
		else
		{
			m_OverlayMaterial.Init( m_WriteZMaterial );
		}
	}
}