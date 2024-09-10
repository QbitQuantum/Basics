/**
 * paints the background for a switchbar item. It can paint aero, visual styles, skins or
 * classic buttons (depending on os and current plugin settings).
 *
 * @param hdc     HDC: target device context
 * @param rc      RECT*: target rectangle
 * @param stateId the state identifier (normal, pressed, hot, disabled etc.)
 */
void __fastcall CSideBar::m_DefaultBackgroundRenderer(const HDC hdc, const RECT *rc, const CSideBarButton *item)
{
	UINT  id = item->getID();
	int   stateId = item->m_buttonControl->stateId;
	bool  fIsActiveItem = (item->m_sideBar->getActiveItem() == item);

	if (CSkin::m_skinEnabled) {
		TContainerData *pContainer = const_cast<TContainerData *>(item->m_sideBar->getContainer());
		int ctrlId = stateId == PBS_PRESSED || fIsActiveItem ? ID_EXTBKBUTTONSPRESSED : (stateId == PBS_HOT ? ID_EXTBKBUTTONSMOUSEOVER : ID_EXTBKBUTTONSNPRESSED);
		CSkinItem *skinItem = &SkinItems[ctrlId];
		HWND hwnd = item->m_buttonControl->hwnd;

		CSkin::SkinDrawBG(hwnd, pContainer->hwnd, pContainer, const_cast<RECT *>(rc), hdc);
		CSkin::DrawItem(hdc, rc, skinItem);
	}
	else if (M.isAero() || PluginConfig.m_fillColor) {
		if (id == IDC_SIDEBARUP || id == IDC_SIDEBARDOWN) {
			if (M.isAero())
				::FillRect(hdc, const_cast<RECT *>(rc), CSkin::m_BrushBack);
			else
				CSkin::FillBack(hdc, const_cast<RECT *>(rc));

			if (stateId == PBS_HOT || stateId == PBS_PRESSED)
				DrawAlpha(hdc, const_cast<RECT *>(rc), 0xf0f0f0, 70, 0x000000, 0, 9,
					31, 4, 0);
			else
				DrawAlpha(hdc, const_cast<RECT *>(rc), 0xf0f0f0, 30, 0x707070, 0, 9,
					31, 4, 0);
		}
		else {
			if (PluginConfig.m_fillColor)
				FillTabBackground(hdc, stateId, item->getDat(), const_cast<RECT *>(rc));

			CSkin::m_switchBarItem->setAlphaFormat(AC_SRC_ALPHA,
				(stateId == PBS_HOT && !fIsActiveItem) ? 250 : (fIsActiveItem || stateId == PBS_PRESSED ? 250 : 230));
			CSkin::m_switchBarItem->Render(hdc, rc, true);
			if (stateId == PBS_HOT || stateId == PBS_PRESSED || fIsActiveItem) {
				RECT rcGlow = *rc;
				rcGlow.top += 1;
				rcGlow.bottom -= 2;

				CSkin::m_tabGlowTop->setAlphaFormat(AC_SRC_ALPHA, (stateId == PBS_PRESSED || fIsActiveItem) ? 180 : 100);
				CSkin::m_tabGlowTop->Render(hdc, &rcGlow, true);
			}
		}
	}
	else if (M.isVSThemed()) {
		RECT *rcDraw = const_cast<RECT *>(rc);
		if (id == IDC_SIDEBARUP || id == IDC_SIDEBARDOWN) {
			::FillRect(hdc, rc, stateId == PBS_HOT ? ::GetSysColorBrush(COLOR_HOTLIGHT) : ::GetSysColorBrush(COLOR_3DFACE));
			::InflateRect(rcDraw, -2, 0);
			::DrawEdge(hdc, rcDraw, EDGE_ETCHED, BF_SOFT | BF_RECT | BF_FLAT);
		}
		else {
			CSkin::FillBack(hdc, rcDraw);

			if (IsThemeBackgroundPartiallyTransparent(item->m_buttonControl->hThemeToolbar, TP_BUTTON, stateId))
				DrawThemeParentBackground(item->getHwnd(), hdc, rcDraw);

			if (M.isAero() || PluginConfig.m_WinVerMajor >= 6) {
				stateId = (fIsActiveItem ? PBS_PRESSED : PBS_HOT);
				DrawThemeBackground(item->m_buttonControl->hThemeToolbar, hdc, 8, RBStateConvert2Flat(stateId), rcDraw, rcDraw);
			}
			else {
				stateId = (fIsActiveItem ? PBS_PRESSED : PBS_HOT);
				DrawThemeBackground(item->m_buttonControl->hThemeToolbar, hdc, TP_BUTTON, TBStateConvert2Flat(stateId), rcDraw, rcDraw);
			}
		}
	}
	else {
		RECT *rcDraw = const_cast<RECT *>(rc);
		if (!(id == IDC_SIDEBARUP || id == IDC_SIDEBARDOWN)) {
			HBRUSH br = (stateId == PBS_HOT && !fIsActiveItem) ? ::GetSysColorBrush(COLOR_BTNSHADOW) : (fIsActiveItem || stateId == PBS_PRESSED ? ::GetSysColorBrush(COLOR_HOTLIGHT) : ::GetSysColorBrush(COLOR_3DFACE));
			::FillRect(hdc, rc, br);
			::DrawEdge(hdc, rcDraw, (stateId == PBS_HOT && !fIsActiveItem) ? EDGE_ETCHED : (fIsActiveItem || stateId == PBS_PRESSED) ? EDGE_BUMP : EDGE_ETCHED, BF_RECT | BF_SOFT | BF_FLAT);
		}
		else {
			::FillRect(hdc, rc, stateId == PBS_HOT ? ::GetSysColorBrush(COLOR_HOTLIGHT) : ::GetSysColorBrush(COLOR_3DFACE));
			::InflateRect(rcDraw, -2, 0);
			::DrawEdge(hdc, rcDraw, EDGE_ETCHED, BF_SOFT | BF_RECT | BF_FLAT);
		}
	}
}