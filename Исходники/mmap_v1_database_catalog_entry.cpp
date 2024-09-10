Status MMAPV1DatabaseCatalogEntry::renameCollection(OperationContext* txn,
                                                    StringData fromNS,
                                                    StringData toNS,
                                                    bool stayTemp) {
    Status s = _renameSingleNamespace(txn, fromNS, toNS, stayTemp);
    if (!s.isOK())
        return s;

    NamespaceDetails* details = _namespaceIndex.details(toNS);
    invariant(details);

    RecordStoreV1Base* systemIndexRecordStore = _getIndexRecordStore();
    auto cursor = systemIndexRecordStore->getCursor(txn);
    while (auto record = cursor->next()) {
        BSONObj oldIndexSpec = record->data.releaseToBson();
        if (fromNS != oldIndexSpec["ns"].valuestrsafe())
            continue;

        BSONObj newIndexSpec;
        {
            BSONObjBuilder b;
            BSONObjIterator i(oldIndexSpec);
            while (i.more()) {
                BSONElement e = i.next();
                if (strcmp(e.fieldName(), "ns") != 0)
                    b.append(e);
                else
                    b << "ns" << toNS;
            }
            newIndexSpec = b.obj();
        }

        StatusWith<RecordId> newIndexSpecLoc = systemIndexRecordStore->insertRecord(
            txn, newIndexSpec.objdata(), newIndexSpec.objsize(), false);
        if (!newIndexSpecLoc.isOK())
            return newIndexSpecLoc.getStatus();

        const std::string& indexName = oldIndexSpec.getStringField("name");

        {
            // Fix the IndexDetails pointer.
            int indexI = getCollectionCatalogEntry(toNS)->_findIndexNumber(txn, indexName);

            IndexDetails& indexDetails = details->idx(indexI);
            *txn->recoveryUnit()->writing(&indexDetails.info) =
                DiskLoc::fromRecordId(newIndexSpecLoc.getValue());
        }

        {
            // Move the underlying namespace.
            std::string oldIndexNs = IndexDescriptor::makeIndexNamespace(fromNS, indexName);
            std::string newIndexNs = IndexDescriptor::makeIndexNamespace(toNS, indexName);

            Status s = _renameSingleNamespace(txn, oldIndexNs, newIndexNs, false);
            if (!s.isOK())
                return s;
        }

        systemIndexRecordStore->deleteRecord(txn, record->id);
    }

    return Status::OK();
}