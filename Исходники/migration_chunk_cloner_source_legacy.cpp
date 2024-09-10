Status MigrationChunkClonerSourceLegacy::commitClone(OperationContext* txn) {
    invariant(!txn->lockState()->isLocked());

    {
        stdx::lock_guard<stdx::mutex> sl(_mutex);
        invariant(!_cloneCompleted);
    }

    auto responseStatus = _callRecipient(createRecvChunkCommitRequest(_args.getNss(), _sessionId));
    if (responseStatus.isOK()) {
        _cleanup(txn);
        return Status::OK();
    }

    cancelClone(txn);
    return responseStatus.getStatus();
}