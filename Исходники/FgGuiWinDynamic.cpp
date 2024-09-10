 virtual void
 updateIfChanged()
 {
     if (g_gg.dg.update(m_api.updateFlagIdx)) {
         // This function is only called by the parent if this window is visible:
         m_win->destroy();
         m_win = m_api.getWin()->getInstance();
         m_win->create(m_hwndParent,0,m_store,NULL,true);
         // Must tell the panels what size to be before they can be displayed:
         m_win->moveWindow(m_lastMoveLo,m_lastMoveSz);
     }
     m_win->updateIfChanged();
 }