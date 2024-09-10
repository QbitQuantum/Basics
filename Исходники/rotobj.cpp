STDMETHODIMP CAdRotator::get_GetAdvertisement(BSTR bstrVirtualPath, BSTR * pVal)
{
	SCODE rc = E_FAIL;
    
	try
	{
		USES_CONVERSION;

		CContext cxt;
		rc = cxt.Init( CContext::get_Server );
		if ( !FAILED(rc) )
		{
			CComBSTR bstrPhysicalPath;
			// determine the physical path
			if ( ( rc = cxt.Server()->MapPath( bstrVirtualPath, &bstrPhysicalPath ) ) == S_OK )
			{
				_TCHAR* szPath = OLE2T( bstrPhysicalPath );

				CAdFilePtr pAdFile = AdFile( szPath );
				
				if ( pAdFile.IsValid() )
				{
					// refresh the ad file (make sure it's up to date)
					pAdFile->Refresh();

					// block all writers
					CReader rdr( *pAdFile );

					// if the border hasn't been set, use the default from the ad file
					short nBorder;
					if ( m_nBorder < 0 )
					{
						nBorder = pAdFile->Border();
					}
					else
					{
						nBorder = m_nBorder;
					}

					CAdDescPtr pAd = pAdFile->RandomAd();
					if ( pAd.IsValid() )
					{
						// write out the HTML line for this ad
						StringOutStream ss;

						if ( m_bClickable && ( pAd->m_strLink.size() > 1 ) )
						{
							// use the href format
							ss	<< _T("<A HREF=\"") << pAdFile->Redirector()
								<< _T("?url=") << pAd->m_strLink
								<< _T("&image=") << pAd->m_strGif
								<< _T("\" ") << m_strTargetFrame << _T(">");
						}
						
						// now fill in the rest
						ss	<< _T("<IMG SRC=\"") << pAd->m_strGif
							<< _T("\" ALT=\"") << pAd->m_strAlt
							<< _T("\" WIDTH=") << pAdFile->Width()
							<< _T(" HEIGHT=") << pAdFile->Height();

						if ( pAdFile->HSpace() != CAdFile::defaultHSpace )
						{
							ss << _T(" HSPACE=") << pAdFile->HSpace();
						}
						if ( pAdFile->VSpace() != CAdFile::defaultVSpace )
						{
							ss << _T(" VSPACE=") << pAdFile->VSpace();
						}

						ss << _T(" BORDER=") << nBorder << _T(">");

						if ( m_bClickable && ( pAd->m_strLink.size() > 1 ) )
						{
							// put the trailing tag on
							ss << _T("</A>");
						}

						String str = ss.toString();
						
						if ( pVal )
						{
							if ( *pVal )
							{
								::SysFreeString( *pVal );
							}
							*pVal = T2BSTR( str.c_str() );
							THROW_IF_NULL( *pVal );
							rc = S_OK;
						}
						else
						{
							rc = E_POINTER;
						}
					}
				}
			}
		}
		else
		{
			_ASSERT(0);
			RaiseException( IDS_ERROR_NOSVR );
		}   // end if got server
	}
	catch ( alloc_err& )
	{
		rc = E_OUTOFMEMORY;
	}
	catch ( ... )
	{
		rc = E_FAIL;
	}
	return rc;
}