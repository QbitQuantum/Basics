void MigrationSourceManager::cleanupOnError(OperationContext* txn) {
    if (_state == kDone) {
        return;
    }

    grid.catalogClient(txn)->logChange(txn,
                                       "moveChunk.error",
                                       _args.getNss().ns(),
                                       BSON("min" << _args.getMinKey() << "max" << _args.getMaxKey()
                                                  << "from"
                                                  << _args.getFromShardId()
                                                  << "to"
                                                  << _args.getToShardId()));

    _cleanup(txn);
}