void RMemoryStorage::deleteTransactionsFrom(int transactionId) {
    QSet<int> keysToRemove;

    {
        QHash<int, RTransaction>::iterator it;
        for (it = transactionMap.begin(); it!=transactionMap.end(); ++it) {
            if (it.key()>=transactionId) {
                // delete orphaned objects:
                QList<RObject::Id> affectedObjects =
                    it.value().getAffectedObjects();

                QList<RObject::Id>::iterator it2;
                for (it2=affectedObjects.begin(); it2!=affectedObjects.end(); ++it2) {
                    QSharedPointer<RObject> obj = queryObjectDirect(*it2);
                    if (!obj.isNull() && obj->isUndone()) {
                        deleteObject(*it2);
                    }
                }

                // delete transaction:
                keysToRemove.insert(it.key());
            }
        }
    }

    {
        QSet<int>::iterator it;
        for (it=keysToRemove.begin(); it!=keysToRemove.end(); ++it) {
            transactionMap.remove(*it);
        }
    }
}