QContactAbstractRequest* QContactJsonDbRequestManager::removeRequest(QJsonDbRequest *jsonDbRequest, RequestType &requestType, int &contactIndex, QString *partitionName)
{
    QMutexLocker locker(m_operationMutex);
    if (m_jsonDbRequestTypeMap.contains(jsonDbRequest)) {
        requestType = m_jsonDbRequestTypeMap.value(jsonDbRequest);
        m_jsonDbRequestTypeMap.remove(jsonDbRequest);
        if (requestType == OrphanRequest || requestType == InvalidRequest)
            return 0;
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find jsondbRequest:" << jsonDbRequest;
        requestType = InvalidRequest;
        return 0;
    }
    QList<QContactAbstractRequest*> reqList = m_activeRequests.keys();
    for (int i = 0; i < reqList.size(); i++) {
        QContactAbstractRequest* req = reqList.at(i);
        QMap<QJsonDbRequest*, int>* requestMap = &(m_activeRequests.value(req)->m_jsonDbRequestMap);
        if (requestMap->contains(jsonDbRequest)) {
            *partitionName = jsonDbRequest->partition();
            contactIndex = requestMap->value(jsonDbRequest);
            requestMap->remove(jsonDbRequest);
            return reqList.at(i);
        }
    }
    // request already deleted so mark this as orphan.
    requestType = OrphanRequest;
    return 0;
}