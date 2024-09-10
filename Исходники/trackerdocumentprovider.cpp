void TrackerDocumentProvider::componentComplete()
{
    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    sessionBus.connect(dbusService, dbusPath, dbusInterface, dbusSignal, this, SLOT(trackerGraphChanged(QString,QVariantList,QVariantList)));

    d->connection = new QSparqlConnection(trackerDriver);
    startSearch();
}