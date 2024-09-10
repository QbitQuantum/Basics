HTTPTransaction*
HTTPUpstreamSession::newTransaction(HTTPTransaction::Handler* handler,
                                    int8_t priority) {
  CHECK_NOTNULL(handler);

  if (!supportsMoreTransactions() || draining_) {
    // This session doesn't support any more parallel transactions
    return nullptr;
  }

  if (!started_) {
    startNow();
  }

  auto txn = createTransaction(codec_->createStream(),
                               0,
                               priority);

  if (txn) {
    DestructorGuard dg(this);
    auto txnID = txn->getID();
    txn->setHandler(handler);
    setNewTransactionPauseState(txnID);
  }
  return txn;
}