  void IncrementalParser::commitTransaction(Transaction* T) {
    //Transaction* CurT = m_Consumer->getTransaction();
    assert(T->isCompleted() && "Transaction not ended!?");
    assert(T->getState() != Transaction::kCommitted
           && "Committing an already committed transaction.");

    // If committing a nested transaction the active one should be its parent
    // from now on.
    if (T->isNestedTransaction())
      m_Consumer->setTransaction(T->getParent());

    // Check for errors...
    if (T->getIssuedDiags() == Transaction::kErrors) {
      rollbackTransaction(T);
      return;
    }

    if (T->hasNestedTransactions()) {
      for(Transaction::const_nested_iterator I = T->nested_begin(),
            E = T->nested_end(); I != E; ++I)
        if ((*I)->getState() != Transaction::kCommitted)
          commitTransaction(*I);
    }

    if (!transformTransactionAST(T))
      return;

    // Here we expect a template instantiation. We need to open the transaction
    // that we are currently work with.
    Transaction::State oldState = T->getState();
    T->setState(Transaction::kCollecting);
    // Pull all template instantiations in that came from the consumers.
    getCI()->getSema().PerformPendingInstantiations();
    T->setState(oldState);

    m_Consumer->HandleTranslationUnit(getCI()->getASTContext());

    if (T->getCompilationOpts().CodeGeneration && hasCodeGenerator()) {
      codeGenTransaction(T);
      transformTransactionIR(T);
    }

    // The static initializers might run anything and can thus cause more
    // decls that need to end up in a transaction. But this one is done
    // with CodeGen...
    T->setState(Transaction::kCommitted);

    if (T->getCompilationOpts().CodeGeneration && hasCodeGenerator()) {
      runStaticInitOnTransaction(T);
    }

    InterpreterCallbacks* callbacks = m_Interpreter->getCallbacks();

    if (callbacks)
      callbacks->TransactionCommitted(*T);

    // If the transaction is empty do nothing.
    // Except it was nested transaction and we want to reuse it later on.
    if (T->empty() && T->isNestedTransaction()) {
      // We need to remove the marker from its parent.
      Transaction* ParentT = T->getParent();
      for (size_t i = 0; i < ParentT->size(); ++i)
        if ((*ParentT)[i].m_DGR.isNull())
          ParentT->erase(i);
    }
  }