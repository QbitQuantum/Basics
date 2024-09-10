void
DocAccessibleParent::Destroy()
{
  // If we are already shutdown that is because our containing tab parent is
  // shutting down in which case we don't need to do anything.
  if (mShutdown) {
    return;
  }

  mShutdown = true;

  MOZ_DIAGNOSTIC_ASSERT(LiveDocs().Contains(mActorID));
  uint32_t childDocCount = mChildDocs.Length();
  for (uint32_t i = 0; i < childDocCount; i++) {
    for (uint32_t j = i + 1; j < childDocCount; j++) {
      MOZ_DIAGNOSTIC_ASSERT(mChildDocs[i] != mChildDocs[j]);
    }
  }

  // XXX This indirection through the hash map of live documents shouldn't be
  // needed, but be paranoid for now.
  int32_t actorID = mActorID;
  for (uint32_t i = childDocCount - 1; i < childDocCount; i--) {
    DocAccessibleParent* thisDoc = LiveDocs().Get(actorID);
    MOZ_ASSERT(thisDoc);
    if (!thisDoc) {
      return;
    }

    thisDoc->ChildDocAt(i)->Destroy();
  }

  for (auto iter = mAccessibles.Iter(); !iter.Done(); iter.Next()) {
    MOZ_ASSERT(iter.Get()->mProxy != this);
    ProxyDestroyed(iter.Get()->mProxy);
    iter.Remove();
  }

  DocAccessibleParent* thisDoc = LiveDocs().Get(actorID);
  MOZ_ASSERT(thisDoc);
  if (!thisDoc) {
    return;
  }

  // The code above should have already completely cleared these, but to be
  // extra safe make sure they are cleared here.
  thisDoc->mAccessibles.Clear();
  thisDoc->mChildDocs.Clear();

  DocManager::NotifyOfRemoteDocShutdown(thisDoc);
  thisDoc = LiveDocs().Get(actorID);
  MOZ_ASSERT(thisDoc);
  if (!thisDoc) {
    return;
  }

  ProxyDestroyed(thisDoc);
  thisDoc = LiveDocs().Get(actorID);
  MOZ_ASSERT(thisDoc);
  if (!thisDoc) {
    return;
  }

  if (DocAccessibleParent* parentDoc = thisDoc->ParentDoc())
    parentDoc->RemoveChildDoc(thisDoc);
  else if (IsTopLevel())
    GetAccService()->RemoteDocShutdown(this);
}