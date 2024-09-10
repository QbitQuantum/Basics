BOOL CPPageVideo::OnApply()
{
	UpdateData();

	AppSettings& s = AfxGetAppSettings();

	CRenderersSettings& renderersSettings                   = s.m_RenderersSettings;
	s.iDSVideoRendererType		                            = m_iDSVideoRendererType = m_iDSVideoRendererType_store = m_iDSVideoRendererTypeCtrl.GetItemData(m_iDSVideoRendererTypeCtrl.GetCurSel());
	s.iRMVideoRendererType		                            = m_iRMVideoRendererType;
	s.iQTVideoRendererType		                            = m_iQTVideoRendererType;
	renderersSettings.iAPSurfaceUsage	                    = m_iAPSurfaceUsage;
	renderersSettings.iDX9Resizer		                    = m_iDX9Resizer;
	renderersSettings.fVMRMixerMode							= !!m_fVMRMixerMode;
	renderersSettings.fVMRMixerYUV		                    = !!m_fVMRMixerYUV;

	renderersSettings.m_AdvRendSets.fVMR9AlterativeVSync	= m_fVMR9AlterativeVSync != 0;
	s.fD3DFullscreen			                            = m_fD3DFullscreen ? true : false;

	renderersSettings.fResetDevice = !!m_fResetDevice;

	if (!m_iEvrBuffers.IsEmpty()) {
		int Temp = 5;
		swscanf_s(m_iEvrBuffers.GetBuffer(), L"%d", &Temp);
		renderersSettings.iEvrBuffers = Temp;
	} else {
		renderersSettings.iEvrBuffers = 5;
	}

	renderersSettings.D3D9RenderDevice = m_fD3D9RenderDevice ? m_D3D9GUIDNames[m_iD3D9RenderDevice] : L"";

	return __super::OnApply();
}