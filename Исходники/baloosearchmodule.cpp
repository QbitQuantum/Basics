void SearchModule::init()
{
    m_dirNotify = new org::kde::KDirNotify(QString(), QString(),
                                           QDBusConnection::sessionBus(), this);
    connect(m_dirNotify, &OrgKdeKDirNotifyInterface::enteredDirectory,
            this, &SearchModule::registerSearchUrl);
    connect(m_dirNotify, &OrgKdeKDirNotifyInterface::leftDirectory,
            this, &SearchModule::unregisterSearchUrl);


    // FIXME: Listen to changes from Baloo!!
    // Listen to dbChanged
    QDBusConnection con = QDBusConnection::sessionBus();
    con.connect(QString(), QStringLiteral("/files"), QStringLiteral("org.kde.baloo"),
                QStringLiteral("updated"), this, SLOT(slotBalooFileDbChanged()));
    con.connect(QString(), QStringLiteral("/files"), QStringLiteral("org.kde"),
                QStringLiteral("changed"), this, SLOT(slotFileMetaDataChanged(QStringList)));
}