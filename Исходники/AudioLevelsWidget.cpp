void AudioLevelsWidget::setupMenus()
{
    this->contextMenuAudioLevelsDropdown = new QMenu(this);
    this->contextMenuAudioLevelsDropdown->setTitle("Dropdown");
    this->expandCollapseAction = this->contextMenuAudioLevelsDropdown->addAction(/*QIcon(":/Graphics/Images/Collapse.png"),*/ "Collapse", this, SLOT(toggleExpandCollapse()));

    QToolButton* toolButtonAudioLevelsDropdown = new QToolButton(this);
    toolButtonAudioLevelsDropdown->setObjectName("toolButtonAudioLevelsDropdown");
    toolButtonAudioLevelsDropdown->setMenu(this->contextMenuAudioLevelsDropdown);
    toolButtonAudioLevelsDropdown->setPopupMode(QToolButton::InstantPopup);
    this->tabWidgetAudioLevels->setCornerWidget(toolButtonAudioLevelsDropdown);
    //this->tabWidgetPreview->setTabIcon(0, QIcon(":/Graphics/Images/TabSplitter.png"));
}