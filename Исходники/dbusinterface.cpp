bool DBusInterface::handleMessage(const QDBusMessage& message, const QDBusConnection& connection)
{
    /* Check to make sure we're getting properties on our interface */
    if (message.type() != QDBusMessage::MessageType::MethodCallMessage) {
        return false;
    }

    /* Break down the path to just the app id */
    bool validpath = true;
    QString pathtemp = message.path();
    if (!pathtemp.startsWith(QLatin1String("/com/canonical/Unity/Launcher/"))) {
        validpath = false;
    }
    pathtemp.remove(QStringLiteral("/com/canonical/Unity/Launcher/"));
    if (pathtemp.indexOf('/') >= 0) {
        validpath = false;
    }

    /* Find ourselves an appid */
    QString appid = decodeAppId(pathtemp);

    // First handle methods of the Launcher interface
    if (message.interface() == QLatin1String("com.canonical.Unity.Launcher")) {
        if (message.member() == QLatin1String("Refresh")) {
            QDBusMessage reply = message.createReply();
            Q_EMIT refreshCalled();
            return connection.send(reply);
        }
    } else if (message.interface() == QLatin1String("com.canonical.Unity.Launcher.Item")) {
        // Handle methods of the Launcher-Item interface
        if (message.member() == QLatin1String("Alert") && validpath) {
            QDBusMessage reply = message.createReply();
            Q_EMIT alertCalled(appid);
            return connection.send(reply);
        }
    }

    // Now handle dynamic properties (for launcher emblems)
    if (message.interface() != QLatin1String("org.freedesktop.DBus.Properties")) {
        return false;
    }

    if (message.member() == QLatin1String("Get") && (message.arguments().count() != 2 || message.arguments()[0].toString() != QLatin1String("com.canonical.Unity.Launcher.Item"))) {
        return false;
    }

    if (message.member() == QLatin1String("Set") && (message.arguments().count() != 3 || message.arguments()[0].toString() != QLatin1String("com.canonical.Unity.Launcher.Item"))) {
        return false;
    }

    if (!validpath) {
        return false;
    }

    int index = m_launcherModel->findApplication(appid);
    LauncherItem *item = static_cast<LauncherItem*>(m_launcherModel->get(index));

    QVariantList retval;
    if (message.member() == QLatin1String("Get")) {
        QString cachedString = message.arguments()[1].toString();
        if (!item) {
            return false;
        }
        if (cachedString == QLatin1String("count")) {
            retval.append(QVariant::fromValue(QDBusVariant(item->count())));
        } else if (cachedString == QLatin1String("countVisible")) {
            retval.append(QVariant::fromValue(QDBusVariant(item->countVisible())));
        } else if (cachedString == QLatin1String("progress")) {
            retval.append(QVariant::fromValue(QDBusVariant(item->progress())));
        }
    } else if (message.member() == QLatin1String("Set")) {
        QString cachedString = message.arguments()[1].toString();
        if (cachedString == QLatin1String("count")) {
            int newCount = message.arguments()[2].value<QDBusVariant>().variant().toInt();
            if (!item || newCount != item->count()) {
                Q_EMIT countChanged(appid, newCount);
                notifyPropertyChanged(QStringLiteral("com.canonical.Unity.Launcher.Item"), encodeAppId(appid), QStringLiteral("count"), QVariant(newCount));
            }
        } else if (cachedString == QLatin1String("countVisible")) {
            bool newVisible = message.arguments()[2].value<QDBusVariant>().variant().toBool();
            if (!item || newVisible != item->countVisible()) {
                Q_EMIT countVisibleChanged(appid, newVisible);
                notifyPropertyChanged(QStringLiteral("com.canonical.Unity.Launcher.Item"), encodeAppId(appid), QStringLiteral("countVisible"), newVisible);
            }
        } else if (cachedString == QLatin1String("progress")) {
            int newProgress = message.arguments()[2].value<QDBusVariant>().variant().toInt();
            if (!item || newProgress != item->progress()) {
                Q_EMIT progressChanged(appid, newProgress);
                notifyPropertyChanged(QStringLiteral("com.canonical.Unity.Launcher.Item"), encodeAppId(appid), QStringLiteral("progress"), QVariant(newProgress));
            }
        }
    } else if (message.member() == QLatin1String("GetAll")) {
        if (item) {
            QVariantMap all;
            all.insert(QStringLiteral("count"), item->count());
            all.insert(QStringLiteral("countVisible"), item->countVisible());
            all.insert(QStringLiteral("progress"), item->progress());
            retval.append(all);
        }
    } else {
        return false;
    }

    QDBusMessage reply = message.createReply(retval);
    return connection.send(reply);
}