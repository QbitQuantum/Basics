static void clang_indexTranslationUnit_Impl(void *UserData) {
  IndexTranslationUnitInfo *ITUI =
    static_cast<IndexTranslationUnitInfo*>(UserData);
  CXTranslationUnit TU = ITUI->TU;
  CXClientData client_data = ITUI->client_data;
  IndexerCallbacks *client_index_callbacks = ITUI->index_callbacks;
  unsigned index_callbacks_size = ITUI->index_callbacks_size;
  unsigned index_options = ITUI->index_options;
  ITUI->result = 1; // init as error.

  if (!TU)
    return;
  if (!client_index_callbacks || index_callbacks_size == 0)
    return;

  CIndexer *CXXIdx = (CIndexer*)TU->CIdx;
  if (CXXIdx->isOptEnabled(CXGlobalOpt_ThreadBackgroundPriorityForIndexing))
    setThreadBackgroundPriority();

  IndexerCallbacks CB;
  memset(&CB, 0, sizeof(CB));
  unsigned ClientCBSize = index_callbacks_size < sizeof(CB)
                                  ? index_callbacks_size : sizeof(CB);
  memcpy(&CB, client_index_callbacks, ClientCBSize);

  OwningPtr<IndexingContext> IndexCtx;
  IndexCtx.reset(new IndexingContext(client_data, CB, index_options, TU));

  // Recover resources if we crash before exiting this method.
  llvm::CrashRecoveryContextCleanupRegistrar<IndexingContext>
    IndexCtxCleanup(IndexCtx.get());

  OwningPtr<IndexingConsumer> IndexConsumer;
  IndexConsumer.reset(new IndexingConsumer(*IndexCtx));

  // Recover resources if we crash before exiting this method.
  llvm::CrashRecoveryContextCleanupRegistrar<IndexingConsumer>
    IndexConsumerCleanup(IndexConsumer.get());

  ASTUnit *Unit = static_cast<ASTUnit *>(TU->TUData);
  if (!Unit)
    return;

  ASTUnit::ConcurrencyCheck Check(*Unit);

  FileManager &FileMgr = Unit->getFileManager();

  if (Unit->getOriginalSourceFileName().empty())
    IndexCtx->enteredMainFile(0);
  else
    IndexCtx->enteredMainFile(FileMgr.getFile(Unit->getOriginalSourceFileName()));

  IndexConsumer->Initialize(Unit->getASTContext());

  indexPreprocessingRecord(*Unit, *IndexCtx);
  indexTranslationUnit(*Unit, *IndexCtx);
  indexDiagnostics(TU, *IndexCtx);

  ITUI->result = 0;
}