void ToolDockWidget::setToolMenu(QMenu *menu)
{
    QToolButton *btn = new QToolButton;
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setMenu(menu);

    m_toolBar->insertWidget(m_closeAct,btn);
}