Status doTxn(OperationContext* opCtx,
             const std::string& dbName,
             const BSONObj& doTxnCmd,
             BSONObjBuilder* result) {
    auto txnNumber = opCtx->getTxnNumber();
    uassert(ErrorCodes::InvalidOptions, "doTxn can only be run with a transaction ID.", txnNumber);
    auto txnParticipant = TransactionParticipant::get(opCtx);
    uassert(ErrorCodes::InvalidOptions, "doTxn must be run within a transaction", txnParticipant);
    invariant(txnParticipant->inMultiDocumentTransaction());
    invariant(opCtx->getWriteUnitOfWork());
    uassert(
        ErrorCodes::InvalidOptions, "doTxn supports only CRUD opts.", _areOpsCrudOnly(doTxnCmd));
    auto hasPrecondition = _hasPrecondition(doTxnCmd);


    // Acquire global lock in IX mode so that the replication state check will remain valid.
    Lock::GlobalLock globalLock(opCtx, MODE_IX);

    auto replCoord = repl::ReplicationCoordinator::get(opCtx);
    bool userInitiatedWritesAndNotPrimary =
        opCtx->writesAreReplicated() && !replCoord->canAcceptWritesForDatabase(opCtx, dbName);

    if (userInitiatedWritesAndNotPrimary)
        return Status(ErrorCodes::NotMaster,
                      str::stream() << "Not primary while applying ops to database " << dbName);

    int numApplied = 0;

    try {
        BSONObjBuilder intermediateResult;

        // The transaction takes place in a global unit of work, so the precondition check
        // and the writes will share the same snapshot.
        if (hasPrecondition) {
            uassertStatusOK(_checkPrecondition(opCtx, doTxnCmd, result));
        }

        numApplied = 0;
        uassertStatusOK(_doTxn(opCtx, dbName, doTxnCmd, &intermediateResult, &numApplied));
        txnParticipant->commitUnpreparedTransaction(opCtx);
        result->appendElements(intermediateResult.obj());
    } catch (const DBException& ex) {
        txnParticipant->abortActiveUnpreparedOrStashPreparedTransaction(opCtx);
        BSONArrayBuilder ab;
        ++numApplied;
        for (int j = 0; j < numApplied; j++)
            ab.append(false);
        result->append("applied", numApplied);
        result->append("code", ex.code());
        result->append("codeName", ErrorCodes::errorString(ex.code()));
        result->append("errmsg", ex.what());
        result->append("results", ab.arr());
        return Status(ErrorCodes::UnknownError, ex.what());
    }

    return Status::OK();
}