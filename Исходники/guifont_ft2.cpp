	//------------------------------------------------------------------------------
	void IGUIFont_ft2::DrawString(IGUIInterfaceRender* pRender, 
		const CGUIStringRender& rString, 
		const CGUIRect&	rStringRect,
		ETextAlignmentHorz uTextAlignmentHorz,
		ETextAlignmentVert uTextAlignmentVert,
		real fAlpha,
		int32 nStartPos,
		int32 nEndPos)
	{
		if( rString.m_strContent.empty())
		{
			//empty string
			return;
		}

		const CGUIStringRenderInfo& rInfo = rString.m_aStringInfo;
		CGUIFontData_ft2* pFontData = GetFontData( rInfo.m_uFontID );
		real fScaledStringWidth = GetStringWidth(rString);
		real fScaledStringHeight = pFontData->GetFontSize() * rInfo.m_fFontScale;

		CGUIVector2 aPos;
		switch( uTextAlignmentHorz )
		{
		case eTextAlignment_Horz_Left:
			aPos.x = rStringRect.m_fLeft;
			break;
		case eTextAlignment_Horz_Right:
			aPos.x = rStringRect.m_fRight-fScaledStringWidth;
			break;
		case eTextAlignment_Horz_Center:
		default:
			aPos.x = floor(rStringRect.m_fLeft+(rStringRect.GetWidth()-fScaledStringWidth)/2);
			break;
		}

		switch( uTextAlignmentVert )
		{
		case eTextAlignment_Vert_Up:
			aPos.y = rStringRect.m_fTop;
			break;
		case eTextAlignment_Vert_Down:
			aPos.y = rStringRect.m_fBottom - fScaledStringHeight;
			break;
		case eTextAlignment_Vert_Center:
		default:
			aPos.y = ceil(rStringRect.m_fTop + (rStringRect.GetHeight() - fScaledStringHeight) / 2);
			break;
		}
		aPos.y += fScaledStringHeight;

		if( nEndPos < 0 || nEndPos >int32( rString.m_strContent.size()))
		{
			nEndPos = rString.m_strContent.size();
		}

		for( int32 i= nStartPos; i<nEndPos; ++i)
		{
			SCharData_ft2 * pCharData = pFontData->GetCharData( rString.m_strContent[i] );

			if( pCharData->m_pTexture)
			{
				CGUIRect aCharRect(
					CGUIVector2(aPos.x+pCharData->m_fBearingX*rInfo.m_fFontScale, aPos.y-pCharData->m_fBearingY*rInfo.m_fFontScale),
					CGUISize(pCharData->m_fBitmapWidth*rInfo.m_fFontScale,pCharData->m_fBitmapHeight*rInfo.m_fFontScale));

				//dest area size
				CGUIColor aColor(rInfo.m_aColor);
				aColor.SetAlpha(aColor.GetAlpha()*fAlpha);
				pRender->DrawTile( 
					aCharRect,
					0, 
					pCharData->m_pTexture,
					pCharData->m_aUV, 
					eImageOrientation_Normal,
					aColor,
					aColor,
					aColor,
					aColor);
			}

			aPos.x+=pCharData->m_aSize.m_fWidth*rInfo.m_fFontScale;
		}
	}