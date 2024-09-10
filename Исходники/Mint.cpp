void Mint::EnableIME(bool bEnable)
{
	_ASSERT(GetHWND());
	if ( (bEnable == true) && MEvent::GetIMESupport()) {
		if (m_hImc) {
			ImmAssociateContext(GetHWND(), m_hImc);
			m_hImc = NULL;	// EnableIME(false) ÇÒ¶§ ´Ù½Ã ¼ÂÆÃµÈ´Ù
			::SetFocus(GetHWND());
		}
		m_bEnableIME = true;
	} else {
		// HIMC¸¦ m_hImc¿¡ ÀÓ½Ã º¸°üÇØ µ×´Ù°¡, Enable¶§ º¹±¸ÇÑ´Ù.
		m_hImc = ImmGetContext(GetHWND());
		if (m_hImc) {
			ImmAssociateContext(GetHWND(), NULL);
			ImmReleaseContext(GetHWND(), m_hImc);
			::SetFocus(GetHWND());
		}
		//ImmDisableIME(0);
		m_bEnableIME = false;
	}

	// CompositionÁßÀÎ ¹®ÀÚ¿­ Á¦°Å
	HIMC hImc = ImmGetContext(GetInstance()->GetHWND());
	if(hImc!=NULL){
		ImmNotifyIME(hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
		ImmReleaseContext(GetInstance()->GetHWND(), hImc);
	}
}