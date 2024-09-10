void SystemTrayIconBase::showIcon(const TrayIconData &trayIconData) {
    
    
    if(!trayIconData.isNull()){
        return;
    }
    
    stop();
    
    this->m_currentData = trayIconData;  
    
    
    setIcon(trayIconData.getFirstIcon());
    setToolTip(trayIconData.getToolTip());
    
    
    QMenu *menu = trayIconData.getMenu();
    if (menu) {
        QMenu *trayMenu = contextMenu();
        if (!trayMenu) {
            setContextMenu(menu);
        } else {
            trayMenu->addMenu(menu);
        }
    }
    
     

    
}