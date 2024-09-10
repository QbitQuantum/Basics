void WindowList::showMenu(bool onlyCurrentDesktop)
{
    QList<WId> windows = KWindowSystem::windows();
    QList<QAction*> actionList;
    QList< QList<QAction*> > windowList;
    int amount = 0;
    int number = 0;

    qDeleteAll(m_listMenu->actions());
    //m_listMenu->clear();

    if (!onlyCurrentDesktop) {
        m_listMenu->addTitle(i18n("Actions"));

        QAction *unclutterAction = m_listMenu->addAction(i18n("Unclutter Windows"));
        QAction *cascadeAction = m_listMenu->addAction(i18n("Cascade Windows"));

        connect(unclutterAction, SIGNAL(triggered()), m_listMenu, SLOT(slotUnclutterWindows()));
        connect(cascadeAction, SIGNAL(triggered()), m_listMenu, SLOT(slotCascadeWindows()));
    }

    for (int i = 0; i <= KWindowSystem::numberOfDesktops(); ++i) {
        windowList.append(QList<QAction*>());
    }

    for (int i = 0; i < windows.count(); ++i) {
        KWindowInfo window = KWindowSystem::windowInfo(windows.at(i), (NET::WMGeometry | NET::WMFrameExtents | NET::WMWindowType | NET::WMDesktop | NET::WMState | NET::XAWMState | NET::WMVisibleName));
        NET::WindowType type = window.windowType(NET::NormalMask | NET::DialogMask | NET::OverrideMask | NET::UtilityMask | NET::DesktopMask | NET::DockMask | NET::TopMenuMask | NET::SplashMask | NET::ToolbarMask | NET::MenuMask);

        if ((onlyCurrentDesktop && !window.isOnDesktop(KWindowSystem::currentDesktop())) || type == NET::Desktop || type == NET::Dock || type == NET::TopMenu || type == NET::Splash || type == NET::Menu || type == NET::Toolbar || window.hasState(NET::SkipPager)) {
            windows.removeAt(i);

            --i;

            continue;
        }

        ++amount;

        QAction *action = new QAction(QIcon(KWindowSystem::icon(windows.at(i))), window.visibleName(), this);
        action->setData((unsigned long long) windows.at(i));

        QString window_title = QString(action->text());
        window_title.truncate(55);
        action->setText(window_title);

        QFont font = QFont(action->font());

        if (window.isMinimized()) {
            font.setItalic(true);
        } else if (KWindowSystem::activeWindow() == windows.at(i)) {
            font.setUnderline(true);
            font.setBold(true);
        }

        action->setFont(font);

        number = ((onlyCurrentDesktop || window.onAllDesktops()) ? 0 : window.desktop());

        QList<QAction*> subList = windowList.value(number);
        subList.append(action);

        windowList.replace(number, subList);
    }

    const bool useSubMenus = (!onlyCurrentDesktop && KWindowSystem::numberOfDesktops() > 1 && (amount / KWindowSystem::numberOfDesktops()) > 5);

    if (amount && useSubMenus) {
        m_listMenu->addTitle(i18n("Desktops"));
    }

    for (int i = 0; i <= KWindowSystem::numberOfDesktops(); ++i) {
        if (windowList.value(i).isEmpty()) {
            continue;
        }

        KMenu *subMenu = NULL;
        QAction *subMenuAction = NULL;
        QString title = (i ? KWindowSystem::desktopName(i) : (onlyCurrentDesktop ? i18n("Current desktop") : i18n("On all desktops")));

        if (useSubMenus) {
            subMenuAction = m_listMenu->addAction(title);

            subMenu = new KMenu(m_listMenu);
            subMenu->installEventFilter(this);
        } else {
            m_listMenu->addTitle(title);
        }

        for (int j = 0; j < windowList.value(i).count(); ++j) {
            if (useSubMenus) {
                subMenu->addAction(windowList.value(i).value(j));
            } else {
                m_listMenu->addAction(windowList.value(i).value(j));
            }
        }

        if (useSubMenus) {
            subMenuAction->setMenu(subMenu);
        }
    }

    if (!amount) {
        qDeleteAll(m_listMenu->actions());

        m_listMenu->clear();

        QAction *noWindows = m_listMenu->addAction(i18n("No windows"));
        noWindows->setEnabled(false);
    }

    if (formFactor() == Plasma::Vertical || formFactor() == Plasma::Horizontal) {
        m_listMenu->popup(popupPosition(m_listMenu->sizeHint()));
    } else {
        m_listMenu->popup(QCursor::pos());
    }
}