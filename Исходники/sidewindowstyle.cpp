void SideDockWidget::createMenu(Qt::DockWidgetArea /*area*/)
{
//    QMenu *moveMenu = new QMenu(tr("Move To"),this);
//    QAction *act = new QAction(tr("OutputBar"),this);
//    act->setData(area);
//    moveMenu->addAction(act);
//    connect(act,SIGNAL(triggered()),this,SLOT(moveAction()));

    m_menu = new QMenu(this);

    QToolButton *btn = new QToolButton(m_toolBar);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setIcon(QIcon("icon:images/movemenu.png"));
    btn->setMenu(m_menu);
    btn->setText(tr("SideBar"));
    btn->setToolTip(tr("Show SideBar"));
    btn->setStyleSheet("QToolButton::menu-indicator {image: none;}");
    m_toolBar->insertWidget(m_closeAct,btn);
}