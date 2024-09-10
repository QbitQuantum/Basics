bool ShortcutHandler::eventFilter(QObject *o, QEvent *e)
{
    if (!o->isWidgetType())
        return QObject::eventFilter(o, e);

    QWidget *widget = static_cast<QWidget*>(o);
    switch(e->type())
    {
    case QEvent::KeyPress:
        if (Qt::Key_Alt==static_cast<QKeyEvent *>(e)->key())
        {
            m_altDown = true;
            if(qobject_cast<QMenu *>(widget))
            {
                m_seenAlt.insert(widget);
                updateWidget(widget);
                if(widget->parentWidget() && widget->parentWidget()->window())
                    m_seenAlt.insert(widget->parentWidget()->window());
            }
            else
            {
                widget = widget->window();
                m_seenAlt.insert(widget);
                QList<QWidget*> l = widget->findChildren<QWidget*>();
                for (int pos = 0;pos < l.size();++pos) {
                    QWidget *w = l.at(pos);
                    if (!(w->isWindow() || !w->isVisible())) // || w->style()->styleHint(QStyle::SH_UnderlineShortcut, 0, w)))
                        updateWidget(w);
                }

                QList<QMenuBar*> m = widget->findChildren<QMenuBar*>();
                for (int i = 0;i < m.size();++i) {
                    updateWidget(m.at(i));
                }
            }
        }
        break;
    case QEvent::WindowDeactivate:
    case QEvent::KeyRelease:
        if (QEvent::WindowDeactivate == e->type() ||
            static_cast<QKeyEvent*>(e)->key() == Qt::Key_Alt) {
            m_altDown = false;
            for (QWidget *widget: const_(m_updated)) {
                widget->update();
            }
            if (!m_updated.contains(widget))
                widget->update();
            m_seenAlt.clear();
            m_updated.clear();
        }
        break;
    case QEvent::Show:
        if(qobject_cast<QMenu *>(widget))
        {
            QWidget *prev=m_openMenus.count() ? m_openMenus.last() : 0L;
            m_openMenus.append(widget);
            if(m_altDown && prev)
                prev->update();
            connect(widget, &QWidget::destroyed,
                    this, &ShortcutHandler::widgetDestroyed);
        }
        break;
    case QEvent::Hide:
        if(qobject_cast<QMenu *>(widget))
        {
            m_seenAlt.remove(widget);
            m_updated.remove(widget);
            m_openMenus.removeAll(widget);
            if(m_altDown)
            {
                if(m_openMenus.count())
                    m_openMenus.last()->update();
                else if(widget->parentWidget() && widget->parentWidget()->window())
                    widget->parentWidget()->window()->update();
            }
        }
        break;
    case QEvent::Close:
        // Reset widget when closing
        m_seenAlt.remove(widget);
        m_updated.remove(widget);
        m_seenAlt.remove(widget->window());
        m_openMenus.removeAll(widget);
        if(m_altDown)
        {
            if(m_openMenus.count())
                m_openMenus.last()->update();
            else if(widget->parentWidget() && widget->parentWidget()->window())
                widget->parentWidget()->window()->update();
        }
        break;
    default:
        break;
    }
    return QObject::eventFilter(o, e);
}