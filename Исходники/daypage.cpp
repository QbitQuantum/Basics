void DayPage::setMenu(QMenu *menu)
{
    // Add softkey for symbian
    QAction* optionsSoftKey = new QAction("Options", this);
    optionsSoftKey->setSoftKeyRole(QAction::PositiveSoftKey);
    optionsSoftKey->setMenu(menu);
    addAction(optionsSoftKey);
}