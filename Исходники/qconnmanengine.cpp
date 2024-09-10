void QConnmanEngine::connectToId(const QString &id)
{
    QMutexLocker locker(&mutex);
    QString servicePath = serviceFromId(id);
    QConnmanServiceInterface serv(servicePath);
    if(!serv.isValid()) {
        emit connectionError(id, QBearerEngineImpl::InterfaceLookupError);
    } else {
        if(serv.getType() != "cellular") {

            serv.connect();
        } else {
            QOfonoManagerInterface ofonoManager(0);
            QString modemPath = ofonoManager.currentModem().path();
            QOfonoDataConnectionManagerInterface dc(modemPath,0);
            foreach(const QDBusObjectPath dcPath,dc.getPrimaryContexts()) {
                if(dcPath.path().contains(servicePath.section("_",-1))) {
                    QOfonoPrimaryDataContextInterface primaryContext(dcPath.path(),0);
                    primaryContext.setActive(true);
                }
            }
        }
    }
}