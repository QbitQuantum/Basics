void QAccessible::updateAccessibility(QObject *o, int who, Event reason)
{
    Q_ASSERT(o);

    if (updateHandler) {
        updateHandler(o, who, reason);
        return;
    }

    QByteArray soundName;
    switch (reason) {
    case PopupMenuStart:
        soundName = "MenuPopup";
        break;

    case MenuCommand:
        soundName = "MenuCommand";
        break;

    case Alert:
        {
#ifndef QT_NO_MESSAGEBOX
            QMessageBox *mb = ::qobject_cast<QMessageBox*>(o);
            if (mb) {
                switch (mb->icon()) {
                case QMessageBox::Warning:
                    soundName = "SystemExclamation";
                    break;
                case QMessageBox::Critical:
                    soundName = "SystemHand";
                    break;
                case QMessageBox::Information:
                    soundName = "SystemAsterisk";
                    break;
                default:
                    break;
                }
            } else
#endif // QT_NO_MESSAGEBOX
            {
                soundName = "SystemAsterisk";
            }

        }
        break;
    default:
        break;
    }

    if (soundName.size()) {
        QSettings settings(QLatin1String("HKEY_CURRENT_USER\\AppEvents\\Schemes\\Apps\\.Default\\") +
                                         QString::fromLatin1(soundName.constData()), QSettings::NativeFormat);
        QString file = settings.value(QLatin1String(".Current/.")).toString();
        if (!file.isEmpty())
            PlaySoundA(soundName.constData(), 0, SND_ALIAS | SND_ASYNC | SND_NODEFAULT | SND_NOWAIT );
    }

    if (!isActive())
        return;

    typedef void (WINAPI *PtrNotifyWinEvent)(DWORD, HWND, LONG, LONG);

    static PtrNotifyWinEvent ptrNotifyWinEvent = 0;
    static bool resolvedNWE = false;
    if (!resolvedNWE) {
        resolvedNWE = true;
        ptrNotifyWinEvent = (PtrNotifyWinEvent)QLibrary::resolve(QLatin1String("user32"), "NotifyWinEvent");
    }
    if (!ptrNotifyWinEvent)
        return;

    // An event has to be associated with a window,
    // so find the first parent that is a widget.
    QWidget *w = 0;
    if (o->isWidgetType()) {
        w = (QWidget*)o;
    } else {
        QObject *p = o;
        while ((p = p->parent()) != 0) {
            if (p->isWidgetType()) {
                w = (QWidget*)p;
                break;
            }
        }
    }

    if (!w) {
        if (reason != QAccessible::ContextHelpStart &&
             reason != QAccessible::ContextHelpEnd)
            w = qApp->focusWidget();
        if (!w) {
            w = qApp->activeWindow();

            if (!w)
                return;

// ### Fixme
//             if (!w) {
//                 w = qApp->mainWidget();
//                 if (!w)
//                     return;
//             }
        }
    }

    if (reason != MenuCommand) { // MenuCommand is faked
        ptrNotifyWinEvent(reason, w->winId(), OBJID_CLIENT, who);
    }
}