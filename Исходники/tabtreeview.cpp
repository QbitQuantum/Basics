bool TabTreeView::viewportEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        const QModelIndex index = indexAt(me->pos());
        updateIndex(index);
        WebTab *tab = index.data(TabModel::WebTabRole).value<WebTab*>();
        if (me->buttons() == Qt::MiddleButton && tab) {
            tab->closeTab();
        }
        if (me->buttons() != Qt::LeftButton) {
            m_pressedIndex = QModelIndex();
            m_pressedButton = NoButton;
            break;
        }
        m_pressedIndex = index;
        m_pressedButton = buttonAt(me->pos(), m_pressedIndex);
        if (m_pressedIndex.isValid()) {
            if (m_pressedButton == ExpandButton) {
                if (isExpanded(m_pressedIndex)) {
                    collapse(m_pressedIndex);
                } else {
                    expand(m_pressedIndex);
                }
            } else if (m_pressedButton == NoButton && tab) {
                tab->makeCurrentTab();
            }
        }
        if (m_pressedButton == CloseButton) {
            me->accept();
            return true;
        }
        break;
    }

    case QEvent::MouseMove: {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        if (m_pressedButton == CloseButton) {
            me->accept();
            return true;
        }
        break;
    }

    case QEvent::MouseButtonRelease: {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        if (me->buttons() != Qt::NoButton) {
            break;
        }
        const QModelIndex index = indexAt(me->pos());
        updateIndex(index);
        if (m_pressedIndex != index) {
            break;
        }
        DelegateButton button = buttonAt(me->pos(), index);
        if (m_pressedButton == button) {
            if (m_pressedButton == ExpandButton) {
                me->accept();
                return true;
            }
            WebTab *tab = index.data(TabModel::WebTabRole).value<WebTab*>();
            if (tab) {
                if (m_pressedButton == CloseButton) {
                    tab->closeTab();
                } else if (m_pressedButton == AudioButton) {
                    tab->toggleMuted();
                }
            }
        }
        if (m_pressedButton == CloseButton) {
            me->accept();
            return true;
        }
        break;
    }

    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    case QEvent::HoverMove: {
        QHoverEvent *he = static_cast<QHoverEvent*>(event);
        updateIndex(m_hoveredIndex);
        m_hoveredIndex = indexAt(he->pos());
        updateIndex(m_hoveredIndex);
        break;
    }

    case QEvent::ToolTip: {
        QHelpEvent *he = static_cast<QHelpEvent*>(event);
        const QModelIndex index = indexAt(he->pos());
        DelegateButton button = buttonAt(he->pos(), index);
        if (button == AudioButton) {
            const bool muted = index.data(TabModel::AudioMutedRole).toBool();
            QToolTip::showText(he->globalPos(), muted ? tr("Unmute Tab") : tr("Mute Tab"), this, visualRect(index));
            he->accept();
            return true;
        } else if (button == CloseButton) {
            QToolTip::showText(he->globalPos(), tr("Close Tab"), this, visualRect(index));
            he->accept();
            return true;
        } else if (button == NoButton) {
            QToolTip::showText(he->globalPos(), index.data().toString(), this, visualRect(index));
            he->accept();
            return true;
        }
        break;
    }

    case QEvent::ContextMenu: {
        QContextMenuEvent *ce = static_cast<QContextMenuEvent*>(event);
        const QModelIndex index = indexAt(ce->pos());
        WebTab *tab = index.data(TabModel::WebTabRole).value<WebTab*>();
        const int tabIndex = tab ? tab->tabIndex() : -1;
        TabContextMenu::Options options = TabContextMenu::VerticalTabs | TabContextMenu::ShowDetachTabAction;
        if (m_tabsInOrder) {
            options |= TabContextMenu::ShowCloseOtherTabsActions;
        }
        TabContextMenu menu(tabIndex, m_window, options);
        addMenuActions(&menu, index);
        menu.exec(ce->globalPos());
        break;
    }

    default:
        break;
    }
    return QTreeView::viewportEvent(event);
}