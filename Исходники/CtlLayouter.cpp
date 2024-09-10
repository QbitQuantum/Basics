//! コントロール親ウィンドウのメッセージ処理時に呼び出す
void CCtlLayouter::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam) {
	if (m_pParent == NULL)
		return;

	// サイズ変更時に無効領域を登録する
	if (message == WM_SIZE) {
		m_pParent->Invalidate();
		m_bNeedLayout = true;
	}

	// 親ウィンドウがサイズ変更されたらコントロールもあらかじめ指定されている方法で再配置する
	if (message == WM_PAINT && m_bNeedLayout) {
		m_bNeedLayout = false;

		CRect rcClient;
		m_pParent->GetClientRect(&rcClient);

		std::vector<Item>::iterator it = m_Items.begin();
		std::vector<Item>::iterator end = m_Items.end();
		while (it != end) {
			CWnd* pCtl = it->pCtl;
			CRect rcCtl, rcCtlNew;

			pCtl->GetWindowRect(&rcCtl);
			m_pParent->ScreenToClient(&rcCtl);

			int w = rcCtl.Width();
			int h = rcCtl.Height();
			DWORD anchorFlags = it->AnchorFlags;

			if (anchorFlags & Anchor::Left) {
				rcCtlNew.left = rcClient.left + it->Left;
			} else {
				rcCtlNew.left = rcClient.right - it->Right - w;
			}

			if (anchorFlags & Anchor::Right) {
				rcCtlNew.right = rcClient.right - it->Right;
			} else {
				rcCtlNew.right = rcClient.left + it->Left + w;
			}

			if (anchorFlags & Anchor::Top) {
				rcCtlNew.top = rcClient.top + it->Top;
			} else {
				rcCtlNew.top = rcClient.bottom - it->Bottom - h;
			}

			if (anchorFlags & Anchor::Bottom) {
				rcCtlNew.bottom = rcClient.bottom - it->Bottom;
			} else {
				rcCtlNew.bottom = rcClient.top + it->Top + h;
			}

			// コントロール配置＆サイズ変更
			UINT nSwpFlags = SWP_NOZORDER;
			if (it->AnchorFlags & Anchor::NoRedraw)
				nSwpFlags |= SWP_NOREDRAW;
			pCtl->SetWindowPos(NULL, rcCtlNew.left, rcCtlNew.top, rcCtlNew.Width(), rcCtlNew.Height(), nSwpFlags);

			if (it->AnchorFlags & Anchor::Invalidate)
				pCtl->Invalidate();
			if (it->AnchorFlags & Anchor::Redraw)
				pCtl->RedrawWindow(); // サイズ変更無い場合に再描画されないものがあるのでフラグにより強制再描画

			it++;
		}

		//if (!(m_DefaultAnchorFlags & Anchor::NoRedraw))
		//	m_pParent->RedrawWindow();
		//if (m_DefaultAnchorFlags & Anchor::Invalidate)
		//	m_pParent->Invalidate();
	}
}