TEST_F(WiredTigerRecoveryUnitTestFixture,
       LocalReadOnADocumentBeingPreparedDoesntTriggerPrepareConflict) {
    // Prepare but don't commit a transaction
    ru1->beginUnitOfWork(clientAndCtx1.second.get());
    WT_CURSOR* cursor;
    getCursor(ru1, &cursor);
    cursor->set_key(cursor, "key");
    cursor->set_value(cursor, "value");
    invariantWTOK(cursor->insert(cursor));
    ru1->setPrepareTimestamp({1, 1});
    ru1->prepareUnitOfWork();

    // A transaction that chooses to ignore prepare conflicts does not see the record instead of
    // returning a prepare conflict.
    ru2->beginUnitOfWork(clientAndCtx2.second.get());
    ru2->setIgnorePrepared(true);
    getCursor(ru2, &cursor);
    cursor->set_key(cursor, "key");
    int ret = cursor->search(cursor);
    ASSERT_EQ(WT_NOTFOUND, ret);

    ru1->abortUnitOfWork();
    ru2->abortUnitOfWork();
}