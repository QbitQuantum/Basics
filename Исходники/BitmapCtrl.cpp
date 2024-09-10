// Render the control
void CBitmapCtrl::Render ( HSURFACE hDestSurf )
{
	int state = GetState();
	if ((state == LGCS_DISABLED || !m_bEnabled) && m_sDisabledSurface[0])
	{
        m_pClientDE->DrawSurfaceToSurfaceTransparent(hDestSurf, g_pInterfaceResMgr->GetSharedSurface(m_sDisabledSurface), LTNULL, m_pos.x, m_pos.y, m_hTrans);
	}
	else if (state == LGCS_SELECTED && m_sSelectedSurface[0])
	{
        m_pClientDE->DrawSurfaceToSurfaceTransparent(hDestSurf, g_pInterfaceResMgr->GetSharedSurface(m_sSelectedSurface), LTNULL, m_pos.x, m_pos.y, m_hTrans);
	}

	else
	{
//		if (state == LGCS_SELECTED)
//		{
//          LTRect rect = {m_pos.x-2,m_pos.y-2,m_pos.x+m_nNormalWidth+2,m_pos.y+m_nNormalHeight+2};
//          g_pLTClient->FillRect(hDestSurf,&rect,SETRGB(255,255,255));
//		}
        m_pClientDE->DrawSurfaceToSurfaceTransparent(hDestSurf, g_pInterfaceResMgr->GetSharedSurface(m_sNormalSurface), LTNULL, m_pos.x, m_pos.y, m_hTrans);

		if (state == LGCS_SELECTED)
		{
			//left
            LTRect rectL(m_pos.x,m_pos.y,m_pos.x+kHighlightWidth,m_pos.y+m_nNormalHeight);

			//top
            LTRect rectT(m_pos.x,m_pos.y,m_pos.x+m_nNormalWidth,m_pos.y+kHighlightWidth);

			//right
            LTRect rectR(m_pos.x+m_nNormalWidth-kHighlightWidth,m_pos.y,m_pos.x+m_nNormalWidth,m_pos.y+m_nNormalHeight);

			//bottom
            LTRect rectB(m_pos.x,m_pos.y+m_nNormalHeight-kHighlightWidth,m_pos.x+m_nNormalWidth,m_pos.y+m_nNormalHeight);

            g_pLTClient->FillRect(hDestSurf,&rectL,kWhite);
            g_pLTClient->FillRect(hDestSurf,&rectT,kWhite);
            g_pLTClient->FillRect(hDestSurf,&rectR,kWhite);
            g_pLTClient->FillRect(hDestSurf,&rectB,kWhite);
		}
	}

}