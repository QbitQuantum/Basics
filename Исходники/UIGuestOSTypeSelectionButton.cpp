UIGuestOSTypeSelectionButton::UIGuestOSTypeSelectionButton(QWidget *pParent)
    : QIWithRetranslateUI<QPushButton>(pParent)
{
    /* Determine icon metric: */
    const int iIconMetric = QApplication::style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(iIconMetric, iIconMetric));

    /* We have to make sure that the button has strong focus, otherwise
     * the editing is ended when the menu is shown: */
    setFocusPolicy(Qt::StrongFocus);

    /* Create a signal mapper so that we not have to react to
     * every single menu activation ourself: */
    m_pSignalMapper = new QSignalMapper(this);
    if (m_pSignalMapper)
        connect(m_pSignalMapper, static_cast<void(QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped),
                this, &UIGuestOSTypeSelectionButton::setOSTypeId);

    /* Create main menu: */
    m_pMainMenu = new QMenu(pParent);
    if (m_pMainMenu)
        setMenu(m_pMainMenu);

    /* Apply language settings: */
    retranslateUi();
}