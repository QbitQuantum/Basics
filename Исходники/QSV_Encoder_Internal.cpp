QSV_Encoder_Internal::QSV_Encoder_Internal(mfxIMPL& impl, mfxVersion& version) :
	m_pmfxENC(NULL),
	m_nSPSBufferSize(100),
	m_nPPSBufferSize(100),
	m_nTaskPool(0),
	m_pTaskPool(NULL),
	m_nTaskIdx(0),
	m_nFirstSyncTask(0)
{
	mfxIMPL tempImpl;
	mfxStatus sts;

	m_bIsWindows8OrGreater = IsWindows8OrGreater();
	m_bUseD3D11 = false;

	if (m_bIsWindows8OrGreater) {
		tempImpl = impl | MFX_IMPL_VIA_D3D11;
		sts = m_session.Init(tempImpl, &version);
		if (sts == MFX_ERR_NONE) {
			m_session.QueryVersion(&version);
			m_session.Close();

			// Use D3D11 surface
			// m_bUseD3D11 = ((version.Major > 1) ||
			//	(version.Major == 1 && version.Minor >= 8));
			m_bUseD3D11 = true;
			if (m_bUseD3D11)
				blog(LOG_INFO, "\timpl:           D3D11\n"
				               "\tsurf:           D3D11");
			else
				blog(LOG_INFO, "\timpl:           D3D11\n"
				               "\tsurf:           SysMem");

			m_impl = tempImpl;
			m_ver = version;
			return;
		}
	}

	// Either windows 7 or D3D11 failed at this point.
	tempImpl = impl | MFX_IMPL_VIA_D3D9;
	sts = m_session.Init(tempImpl, &version);
	if (sts == MFX_ERR_NONE) {
		m_session.QueryVersion(&version);
		m_session.Close();

		blog(LOG_INFO, "\timpl:           D3D09\n"
		               "\tsurf:           SysMem");

		m_impl = tempImpl;
		m_ver = version;
	}

}