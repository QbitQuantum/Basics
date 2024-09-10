    void UpdateMinSize() {
        m_min_size = GG::Pt(GG::X0, GG::Y0);

        m_min_size += m_wnd.Size() - m_wnd.ClientSize();

        // The rest of this function could use m_tabs->MinUsableSize instead of
        // dealing with the children of m_tabs directly, but that checks the
        // MinUsableSize of _all_ child windows, not just the currently
        // selected one.
        if (GraphicalSummaryWnd* graphical_wnd =
               dynamic_cast<GraphicalSummaryWnd*>(m_tabs->CurrentWnd())) {
            m_min_size += graphical_wnd->MinUsableSize();
        } else {
            // The log uses the GG::Layout which incorrectly reports
            // the current size as the minimum size. So use an arbitrary
            // minimum size of 20 characters by 1 line height
            // m_min_size += m_log_scroller->MinUsableSize();
            m_min_size += GG::Pt(ClientUI::GetFont()->SpaceWidth()*20, ClientUI::GetFont()->Height());
        }

        std::list<GG::Wnd*>::const_iterator layout_begin =
            m_tabs->GetLayout()->Children().begin();
        // First object in the layout should be the tab bar.
        if (layout_begin != m_tabs->GetLayout()->Children().end()) {
            GG::Pt tab_min_size = (*layout_begin)->MinUsableSize();
            m_min_size.x = std::max(tab_min_size.x, m_min_size.x);
            // TabBar::MinUsableSize does not seem to return the correct
            // height, so extra height is added here.
            m_min_size.y += tab_min_size.y + GG::Y(14);
        }

        // Leave space for the resize tab.
        m_min_size.y += GG::Y(INNER_BORDER_ANGLE_OFFSET);

        // If the window is currently too small, re-validate its size.
        if (m_wnd.Width() < m_min_size.x || m_wnd.Height() < m_min_size.y) {
            m_wnd.Resize(m_wnd.Size());
        }
    }