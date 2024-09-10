QWidget*  TabWidget::removeTab(int index) {
    QMutexLocker l(&_tabWidgetStateMutex);
    if (index < 0 || index >= (int)_tabs.size()) {
        return NULL;
    }
    QWidget* tab = _tabs[index];
    _gui->unregisterTab(tab);
    _tabs.erase(_tabs.begin()+index);
    _tabBar->blockSignals(true);
    _tabBar->removeTab(index);
    _tabBar->blockSignals(false);
    if (_tabs.size() > 0) {
        l.unlock();
        makeCurrentTab(0);
        l.relock();
    } else {
        
        _currentWidget = 0;
        _mainLayout->addStretch();
        if (_isFloating && !_gui->isDraggingPanel()) {
            l.unlock();
            closeFloatingPane();
            l.relock();
        }
    }
    tab->setParent(NULL);
    return tab;
}