  void verify(QList<TestContext*> allContexts) {

    {
      DUChainReadLocker lock(DUChain::lock());
      QCOMPARE(m_context->importedParentContexts().count(), imports.count());
    }
    //Compute a closure of all children, and verify that they are imported.
    QSet<TestContext*> collected;
    collectImports(collected);
    collected.remove(this);

    DUChainReadLocker lock(DUChain::lock());
    foreach(TestContext* context, collected) {
      QVERIFY(m_context->imports(context->m_context, CursorInRevision::invalid()));
#ifdef TEST_NORMAL_IMPORTS
      QVERIFY(m_normalContext->imports(context->m_normalContext));
#endif
    }