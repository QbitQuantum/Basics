TEST_F(
    TransactionCoordinatorServiceTest,
    CreateCoordinatorWithHigherTxnNumberThanExistingButNotYetCommittingTxnCancelsPreviousTxnAndSucceeds) {
    auto coordinatorService = TransactionCoordinatorService::get(operationContext());
    coordinatorService->createCoordinator(operationContext(), _lsid, _txnNumber, kCommitDeadline);

    // Create a coordinator for a higher transaction number in the same session. This should
    // cancel commit on the old coordinator.
    coordinatorService->createCoordinator(
        operationContext(), _lsid, _txnNumber + 1, kCommitDeadline);
    auto newTxnCommitDecisionFuture = *coordinatorService->coordinateCommit(
        operationContext(), _lsid, _txnNumber + 1, kTwoShardIdSet);

    // Since this transaction has already been canceled, this should return boost::none.
    auto oldTxnCommitDecisionFuture =
        coordinatorService->coordinateCommit(operationContext(), _lsid, _txnNumber, kTwoShardIdSet);

    // The old transaction should now be committed.
    ASSERT(oldTxnCommitDecisionFuture == boost::none);

    // Make sure the newly created one works fine too.
    commitTransaction(*coordinatorService, _lsid, _txnNumber + 1, kTwoShardIdSet);
}