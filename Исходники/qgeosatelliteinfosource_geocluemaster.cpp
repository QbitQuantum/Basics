void QGeoSatelliteInfoSourceGeoclueMaster::positionProviderChanged(const QString &name,
                                                                   const QString &description,
                                                                   const QString &service,
                                                                   const QString &path)
{
    Q_UNUSED(name)
    Q_UNUSED(description)

    cleanupSatelliteSource();

    QString providerService;
    QString providerPath;

    if (service.isEmpty() || path.isEmpty()) {
        // No valid position provider has been selected. This probably means that the GPS provider
        // has not yet obtained a position fix. It can still provide satellite information though.
        if (!m_satellitesChangedConnected) {
            QDBusConnection conn = QDBusConnection::sessionBus();
            conn.connect(QString(), QString(), QStringLiteral("org.freedesktop.Geoclue.Satellite"),
                         QStringLiteral("SatelliteChanged"), this,
                         SLOT(satelliteChanged(QDBusMessage)));
            m_satellitesChangedConnected = true;
            return;
        }
    } else {
        if (m_satellitesChangedConnected) {
            QDBusConnection conn = QDBusConnection::sessionBus();
            conn.disconnect(QString(), QString(),
                            QStringLiteral("org.freedesktop.Geoclue.Satellite"),
                            QStringLiteral("SatelliteChanged"), this,
                            SLOT(satelliteChanged(QDBusMessage)));
            m_satellitesChangedConnected = false;
        }

        providerService = service;
        providerPath = path;
    }

    if (providerService.isEmpty() || providerPath.isEmpty()) {
        m_error = AccessError;
        emit QGeoSatelliteInfoSource::error(m_error);
        return;
    }

    m_provider = new OrgFreedesktopGeoclueInterface(providerService, providerPath, QDBusConnection::sessionBus());
    m_provider->AddReference();

    m_sat = new OrgFreedesktopGeoclueSatelliteInterface(providerService, providerPath, QDBusConnection::sessionBus());

    if (m_running) {
        connect(m_sat, SIGNAL(SatelliteChanged(qint32,qint32,qint32,QList<qint32>,QList<QGeoSatelliteInfo>)),
                this, SLOT(satelliteChanged(qint32,qint32,qint32,QList<qint32>,QList<QGeoSatelliteInfo>)));
    }
}