void
NotificationController::WillRefresh(mozilla::TimeStamp aTime)
{
  Telemetry::AutoTimer<Telemetry::A11Y_UPDATE_TIME> updateTimer;

  // If the document accessible that notification collector was created for is
  // now shut down, don't process notifications anymore.
  NS_ASSERTION(mDocument,
               "The document was shut down while refresh observer is attached!");
  if (!mDocument)
    return;

  if (mObservingState == eRefreshProcessing ||
      mObservingState == eRefreshProcessingForUpdate)
    return;

  // Any generic notifications should be queued if we're processing content
  // insertions or generic notifications.
  mObservingState = eRefreshProcessingForUpdate;

  // Initial accessible tree construction.
  if (!mDocument->HasLoadState(DocAccessible::eTreeConstructed)) {
    // If document is not bound to parent at this point then the document is not
    // ready yet (process notifications later).
    if (!mDocument->IsBoundToParent()) {
      mObservingState = eRefreshObserving;
      return;
    }

#ifdef A11Y_LOG
    if (logging::IsEnabled(logging::eTree)) {
      logging::MsgBegin("TREE", "initial tree created");
      logging::Address("document", mDocument);
      logging::MsgEnd();
    }
#endif

    mDocument->DoInitialUpdate();

    NS_ASSERTION(mContentInsertions.Length() == 0,
                 "Pending content insertions while initial accessible tree isn't created!");
  }

  // Initialize scroll support if needed.
  if (!(mDocument->mDocFlags & DocAccessible::eScrollInitialized))
    mDocument->AddScrollListener();

  // Process content inserted notifications to update the tree. Process other
  // notifications like DOM events and then flush event queue. If any new
  // notifications are queued during this processing then they will be processed
  // on next refresh. If notification processing queues up new events then they
  // are processed in this refresh. If events processing queues up new events
  // then new events are processed on next refresh.
  // Note: notification processing or event handling may shut down the owning
  // document accessible.

  // Process only currently queued content inserted notifications.
  nsTArray<nsRefPtr<ContentInsertion> > contentInsertions;
  contentInsertions.SwapElements(mContentInsertions);

  uint32_t insertionCount = contentInsertions.Length();
  for (uint32_t idx = 0; idx < insertionCount; idx++) {
    contentInsertions[idx]->Process();
    if (!mDocument)
      return;
  }

  // Process rendered text change notifications.
  mTextHash.EnumerateEntries(TextEnumerator, mDocument);
  mTextHash.Clear();

  // Bind hanging child documents.
  uint32_t hangingDocCnt = mHangingChildDocuments.Length();
  for (uint32_t idx = 0; idx < hangingDocCnt; idx++) {
    DocAccessible* childDoc = mHangingChildDocuments[idx];
    if (childDoc->IsDefunct())
      continue;

    nsIContent* ownerContent = mDocument->DocumentNode()->
      FindContentForSubDocument(childDoc->DocumentNode());
    if (ownerContent) {
      Accessible* outerDocAcc = mDocument->GetAccessible(ownerContent);
      if (outerDocAcc && outerDocAcc->AppendChild(childDoc)) {
        if (mDocument->AppendChildDocument(childDoc)) {
          if (XRE_GetProcessType() != GeckoProcessType_Default) {
            DocAccessibleChild* ipcDoc = new DocAccessibleChild(childDoc);
            childDoc->SetIPCDoc(ipcDoc);
            auto contentChild = dom::ContentChild::GetSingleton();
            DocAccessibleChild* parentIPCDoc = mDocument->IPCDoc();
            uint64_t id = reinterpret_cast<uintptr_t>(outerDocAcc->UniqueID());
            contentChild->SendPDocAccessibleConstructor(ipcDoc, parentIPCDoc,
                                                        id);
          }

          continue;
        }

        outerDocAcc->RemoveChild(childDoc);
      }

      // Failed to bind the child document, destroy it.
      childDoc->Shutdown();
    }
  }
  mHangingChildDocuments.Clear();

  // If the document is ready and all its subdocuments are completely loaded
  // then process the document load.
  if (mDocument->HasLoadState(DocAccessible::eReady) &&
      !mDocument->HasLoadState(DocAccessible::eCompletelyLoaded) &&
      hangingDocCnt == 0) {
    uint32_t childDocCnt = mDocument->ChildDocumentCount(), childDocIdx = 0;
    for (; childDocIdx < childDocCnt; childDocIdx++) {
      DocAccessible* childDoc = mDocument->GetChildDocumentAt(childDocIdx);
      if (!childDoc->HasLoadState(DocAccessible::eCompletelyLoaded))
        break;
    }

    if (childDocIdx == childDocCnt) {
      mDocument->ProcessLoad();
      if (!mDocument)
        return;
    }
  }

  // Process only currently queued generic notifications.
  nsTArray < nsRefPtr<Notification> > notifications;
  notifications.SwapElements(mNotifications);

  uint32_t notificationCount = notifications.Length();
  for (uint32_t idx = 0; idx < notificationCount; idx++) {
    notifications[idx]->Process();
    if (!mDocument)
      return;
  }

  // Process invalidation list of the document after all accessible tree
  // modification are done.
  mDocument->ProcessInvalidationList();

  // If a generic notification occurs after this point then we may be allowed to
  // process it synchronously.  However we do not want to reenter if fireing
  // events causes script to run.
  mObservingState = eRefreshProcessing;

  ProcessEventQueue();
  mObservingState = eRefreshObserving;
  if (!mDocument)
    return;

  // Stop further processing if there are no new notifications of any kind or
  // events and document load is processed.
  if (mContentInsertions.IsEmpty() && mNotifications.IsEmpty() &&
      mEvents.IsEmpty() && mTextHash.Count() == 0 &&
      mHangingChildDocuments.IsEmpty() &&
      mDocument->HasLoadState(DocAccessible::eCompletelyLoaded) &&
      mPresShell->RemoveRefreshObserver(this, Flush_Display)) {
    mObservingState = eNotObservingRefresh;
  }
}