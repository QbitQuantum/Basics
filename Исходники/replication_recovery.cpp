void ReplicationRecoveryImpl::_truncateOplogTo(OperationContext* opCtx,
                                               Timestamp truncateTimestamp) {
    Timer timer;
    const NamespaceString oplogNss(NamespaceString::kRsOplogNamespace);
    AutoGetDb autoDb(opCtx, oplogNss.db(), MODE_IX);
    Lock::CollectionLock oplogCollectionLoc(opCtx->lockState(), oplogNss.ns(), MODE_X);
    Collection* oplogCollection = autoDb.getDb()->getCollection(opCtx, oplogNss);
    if (!oplogCollection) {
        fassertFailedWithStatusNoTrace(
            34418,
            Status(ErrorCodes::NamespaceNotFound,
                   str::stream() << "Can't find " << NamespaceString::kRsOplogNamespace.ns()));
    }

    // Scan through oplog in reverse, from latest entry to first, to find the truncateTimestamp.
    RecordId oldestIDToDelete;  // Non-null if there is something to delete.
    auto oplogRs = oplogCollection->getRecordStore();
    auto oplogReverseCursor = oplogRs->getCursor(opCtx, /*forward=*/false);
    size_t count = 0;
    while (auto next = oplogReverseCursor->next()) {
        const BSONObj entry = next->data.releaseToBson();
        const RecordId id = next->id;
        count++;

        const auto tsElem = entry["ts"];
        if (count == 1) {
            if (tsElem.eoo())
                LOG(2) << "Oplog tail entry: " << redact(entry);
            else
                LOG(2) << "Oplog tail entry ts field: " << tsElem;
        }

        if (tsElem.timestamp() < truncateTimestamp) {
            // If count == 1, that means that we have nothing to delete because everything in the
            // oplog is < truncateTimestamp.
            if (count != 1) {
                invariant(!oldestIDToDelete.isNull());
                oplogCollection->cappedTruncateAfter(opCtx, oldestIDToDelete, /*inclusive=*/true);
            }
            log() << "Replication recovery oplog truncation finished in: " << timer.millis()
                  << "ms";
            return;
        }

        oldestIDToDelete = id;
    }

    severe() << "Reached end of oplog looking for oplog entry before " << truncateTimestamp.toBSON()
             << " but couldn't find any after looking through " << count << " entries.";
    fassertFailedNoTrace(40296);
}