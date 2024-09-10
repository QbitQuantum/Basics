VBoxTrayIcon::VBoxTrayIcon (VBoxSelectorWnd* aParent, UIVMItemModel* aVMModel)
{
    mParent = aParent;
    mVMModel = aVMModel;

    mShowSelectorAction = new QAction (this);
    Assert (mShowSelectorAction);
    mShowSelectorAction->setIcon(UIIconPool::iconSet(":/VirtualBox_16px.png"));

    mHideSystrayMenuAction = new QAction (this);
    Assert (mHideSystrayMenuAction);
    mHideSystrayMenuAction->setIcon(UIIconPool::iconSet(":/exit_16px.png"));

    /* reuse parent action data */

    mVmConfigAction = new QAction (this);
    Assert (mVmConfigAction);
    mVmConfigAction->setIcon (mParent->vmConfigAction()->icon());

    mVmDeleteAction = new QAction (this);
    Assert (mVmDeleteAction);
    mVmDeleteAction->setIcon (mParent->vmDeleteAction()->icon());

    mVmStartAction = new QAction (this);
    Assert (mVmStartAction);
    mVmStartAction->setIcon (mParent->vmStartAction()->icon());

    mVmDiscardAction = new QAction (this);
    Assert (mVmDiscardAction);
    mVmDiscardAction->setIcon (mParent->vmDiscardAction()->icon());

    mVmPauseAction = new QAction (this);
    Assert (mVmPauseAction);
    mVmPauseAction->setCheckable (true);
    mVmPauseAction->setIcon (mParent->vmPauseAction()->icon());

    mVmRefreshAction = new QAction (this);
    Assert (mVmRefreshAction);
    mVmRefreshAction->setIcon (mParent->vmRefreshAction()->icon());

    mVmShowLogsAction = new QAction (this);
    Assert (mVmConfigAction);
    mVmShowLogsAction->setIcon (mParent->vmShowLogsAction()->icon());

    mTrayIconMenu = new QMenu (aParent);
    Assert (mTrayIconMenu);

    setIcon (QIcon (":/VirtualBox_16px.png"));
    setContextMenu (mTrayIconMenu);

    connect (mShowSelectorAction, SIGNAL (triggered()), mParent, SLOT (showWindow()));
    connect (mHideSystrayMenuAction, SIGNAL (triggered()), this, SLOT (trayIconShow()));
}