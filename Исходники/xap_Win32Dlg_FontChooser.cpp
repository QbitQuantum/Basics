void XAP_Win32Dialog_FontChooser::runModal(XAP_Frame * pFrame)
{
	UT_return_if_fail(pFrame);

	XAP_Win32App * pApp = static_cast<XAP_Win32App *>(XAP_App::getApp());
	UT_return_if_fail(pApp);
	const XAP_EncodingManager *pEncMan = pApp->getEncodingManager();
	UT_return_if_fail(pEncMan);
    UT_Win32LocaleString family;

	UT_DEBUGMSG(("FontChooserStart: Family[%s] Size[%s] Weight[%s] Style[%s] Color[%s] Underline[%d] StrikeOut[%d]\n",
				 m_sFontFamily.c_str(),
				 m_sFontSize.c_str(),
				 m_sFontWeight.c_str(),
				 m_sFontStyle.c_str(),
				 m_sColor.c_str(),
				 m_bUnderline,
				 m_bStrikeout));

	m_bWin32Overline   = m_bOverline;
	m_bWin32Hidden     = m_bHidden;
	m_bWin32SuperScript = m_bSuperScript;
	m_bWin32SubScript = m_bSubScript;
	

	/*
	   WARNING: any changes to this function should be closely coordinated
	   with the equivalent logic in Win32Graphics::FindFont()
	*/
	LOGFONTW lf;
	memset(&lf, 0, sizeof(lf));

	CHOOSEFONTW cf;
	memset(&cf, 0, sizeof(cf));
	cf.lStructSize = sizeof(cf);
	cf.hwndOwner = static_cast<XAP_Win32FrameImpl*>(pFrame->getFrameImpl())->getTopLevelWindow();
	cf.lpLogFont = &lf;
	cf.Flags = CF_SCREENFONTS |
               CF_EFFECTS |
               CF_ENABLEHOOK |
               CF_ENABLETEMPLATE |
               CF_INITTOLOGFONTSTRUCT;
    cf.lpTemplateName = MAKEINTRESOURCEW(XAP_RID_DIALOG_FONT);
    cf.lpfnHook = (LPCFHOOKPROC) s_hookProc;
	cf.lCustData = (LPARAM) this;
	cf.hInstance = pApp->getInstance();

	if (!m_sFontFamily.empty())
    {
        family.fromUTF8 (m_sFontFamily.c_str());
		lstrcpynW(lf.lfFaceName,family.c_str(),LF_FACESIZE);
    }
	else
		cf.Flags |= CF_NOFACESEL;

	if (!m_sFontSize.empty())
	{
		UT_ASSERT(sizeof(char) == sizeof(gchar));
		lf.lfHeight = (long) -(UT_convertToPoints(m_sFontSize.c_str()))*4/3;
	}
	else
		cf.Flags |= CF_NOSIZESEL;

	if (!m_sFontWeight.empty())
	{
		if (g_ascii_strcasecmp(m_sFontWeight.c_str(),"bold") == 0)
			lf.lfWeight = 700;
		// TODO do we need any others here...
	}
	else
		cf.Flags |= CF_NOSTYLESEL;

	if (!m_sFontStyle.empty())
	{
		if (g_ascii_strcasecmp(m_sFontStyle.c_str(),"italic") == 0)
			lf.lfItalic = TRUE;
	}
	else
		cf.Flags |= CF_NOSTYLESEL;

	if (!m_sColor.empty())
	{
		UT_RGBColor c;
		UT_parseColor(m_sColor.c_str(),c);
		cf.rgbColors = RGB(c.m_red,c.m_grn,c.m_blu);
	}

	if (m_bUnderline)
		lf.lfUnderline = TRUE;
	if (m_bStrikeout)
		lf.lfStrikeOut = TRUE;

	// run the actual dialog...
	m_answer = (ChooseFontW(&cf) ? a_OK : a_CANCEL);
	// Convert the font name returned by the Windows Font Chooser
	// to UTF-8.
	family.fromLocale (lf.lfFaceName);
	UT_UTF8String family_utf = family.utf8_str();
	const char *szFontFamily = family_utf.utf8_str();

	if (m_answer == a_OK)
	{
		if(!m_sFontFamily.empty())
		{
			if((g_ascii_strcasecmp(szFontFamily, m_sFontFamily.c_str()) != 0))
			{
				m_bChangedFontFamily = true;
				m_sFontFamily = szFontFamily;
			}
		}
		else
		{
			if(szFontFamily[0])
			{
				m_bChangedFontFamily = true;
				m_sFontFamily = szFontFamily;
			}
		}

		bool bIsSizeValid = ((cf.Flags & CF_NOSIZESEL) == 0);
		bool bWasSizeValid = !m_sFontSize.empty();
		char bufSize[10];
		if (bIsSizeValid)
			sprintf(bufSize,"%dpt",(cf.iPointSize/10));
		else
			bufSize[0] = 0;

		// why? let's see
		if (bIsSizeValid && (g_ascii_strcasecmp(bufSize,m_sFontSize.c_str()) != 0))			
		{
			m_bChangedFontSize = true;
			m_sFontSize = bufSize;
		}
		else
		{
			/* nothing changed */			
		}

		bool bIsBold = ((cf.nFontType & BOLD_FONTTYPE) != 0);
		bool bWasBold = (g_ascii_strcasecmp(m_sFontWeight.c_str(),"bold") == 0);
		bool bIsNormal = ((cf.nFontType & REGULAR_FONTTYPE) != 0);
		bool bWasNormal = (m_sFontWeight.empty() || (g_ascii_strcasecmp(m_sFontWeight.c_str(),"normal") != 0));
		if ((bIsBold != bWasBold) || (bIsNormal != bWasNormal))
		{
			m_bChangedFontWeight = true;
			if( bIsBold )
				m_sFontWeight = "bold";
			else
				m_sFontWeight = "normal";
		}

		bool bIsItalic = ((cf.nFontType & ITALIC_FONTTYPE) != 0);
		bool bWasItalic = (g_ascii_strcasecmp(m_sFontStyle.c_str(),"italic") == 0);
		if (bIsItalic != bWasItalic)
		{
			m_bChangedFontStyle = true;
			if( bIsItalic )
				m_sFontStyle = "italic";
			else
				m_sFontStyle = "normal";
		}

		char bufColor[10];
		sprintf(bufColor,"%02x%02x%02x",GetRValue(cf.rgbColors),
				GetGValue(cf.rgbColors),GetBValue(cf.rgbColors));
		bool bWasColorValid = !m_sColor.empty();

		if ( m_bChangedColor &&  ((bWasColorValid && (g_ascii_strcasecmp(bufColor,m_sColor.c_str()) != 0))
								  || (!bWasColorValid && (g_ascii_strcasecmp(bufColor,"000000") != 0))))
		{
			m_sColor = bufColor;
		}

		m_bChangedUnderline  = ((lf.lfUnderline == TRUE) != m_bUnderline);
		m_bChangedStrikeOut  = ((lf.lfStrikeOut == TRUE) != m_bStrikeout);
		m_bChangedOverline   = (m_bWin32Overline   != m_bOverline);
		if (m_bChangedUnderline ||
            m_bChangedStrikeOut ||
            m_bChangedOverline)
			setFontDecoration( (lf.lfUnderline == TRUE),
                                m_bWin32Overline,
                                (lf.lfStrikeOut == TRUE), NULL, NULL);

		m_bChangedHidden = (m_bWin32Hidden != m_bHidden);
		m_bChangedSuperScript = (m_bWin32SuperScript != m_bSuperScript);
		m_bChangedSubScript = (m_bWin32SubScript != m_bSubScript);
		
		if(m_bChangedHidden)
			setHidden(m_bWin32Hidden);
			
		if(m_bChangedSuperScript)
			setSuperScript(m_bWin32SuperScript);
			
		if(m_bChangedSubScript)
			setSubScript(m_bWin32SubScript);			
	}

	UT_DEBUGMSG(("FontChooserEnd: Family[%s%s] Size[%s%s] Weight[%s%s] Style[%s%s] Color[%s%s] Underline[%d%s] StrikeOut[%d%s]\n",
				 m_sFontFamily.c_str(),	((m_bChangedFontFamily) ? "(chg)" : ""),
				 m_sFontSize.c_str(),	((m_bChangedFontSize) ? "(chg)" : ""),
				 m_sFontWeight.c_str(),	((m_bChangedFontWeight) ? "(chg)" : ""),
				 m_sFontStyle.c_str(),	((m_bChangedFontStyle) ? "(chg)" : ""),
				 m_sColor.c_str(),		((m_bChangedColor) ? "(chg)" : ""),
				 m_bUnderline,			((m_bChangedUnderline) ? "(chg)" : ""),
				 m_bStrikeout,			((m_bChangedStrikeOut) ? "(chg)" : "")));

	// the caller can get the answer from getAnswer().

	m_pWin32Frame = NULL;
}