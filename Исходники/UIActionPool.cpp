/* UIActionMenu stuff: */
UIActionMenu::UIActionMenu(QObject *pParent, const QString &strIcon, const QString &strIconDis)
    : UIAction(pParent, UIActionType_Menu)
{
    if (!strIcon.isNull())
        setIcon(UIIconPool::iconSet(strIcon, strIconDis));
    setMenu(new UIMenu);
}