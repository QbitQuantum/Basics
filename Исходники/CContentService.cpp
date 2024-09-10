ECode CContentService::NotifyChange(
    /* [in] */ IUri* uri,
    /* [in] */ IContentObserver* observer,
    /* [in] */ Boolean observerWantsSelfNotifications,
    /* [in] */ Boolean syncToNetwork)
{
    if (Logger::IsLoggable(TAG, Logger::VERBOSE)) {
        String str("Notifying update of ");
        if (NULL != uri) {
            String strUri;
            uri->ToString(&strUri);
            str.Append(strUri);
        } 
        else {
            str.Append(" null ");
        }
        str.Append(" from observer ");
        //TODO: observer->ToString();
        str.Append(", syncToNetwork ");
        str.Append(syncToNetwork ? " true ":" false ");
        Logger::V(TAG, str);
    }
    // This makes it so that future permission checks will be in the context of this
    // process rather than the caller's process. We will restore this before returning.
    //TODO: long identityToken = clearCallingIdentity();

    List<AutoPtr<ObserverCall> >* calls = new List<AutoPtr<ObserverCall> >();
    Mutex::Autolock lock(mRootNodeLock);
    FAIL_RETURN(mRootNode->CollectObserversLocked(mRootNode, uri, 0, observer, observerWantsSelfNotifications, calls));
    List<AutoPtr<ObserverCall> >::Iterator it;
    ECode ecode = NOERROR;
    AutoPtr<ObserverCall> oc;

    for (it = calls->Begin(); it != calls->End(); it++) {
        oc = *it;
        ecode = oc->mObserver->OnChange(oc->mSelfNotify);
        if (Logger::IsLoggable(TAG, Logger::VERBOSE)) {
            String str("Notified ");
            //TODO: oc->mObserver->ToString();
            str.Append(" of update at ");
            if (NULL != uri) {
                String strUri;
                uri->ToString(&strUri);
                str.Append(strUri);
            } 
            else {
                str.Append(" null ");
            }
            Logger::V(TAG, str);
        }
        if (ecode != NOERROR) {
            Mutex::Autolock lock(mRootNodeLock);
            Logger::W(TAG, "Found dead observer, removing");
            AutoPtr<IContentObserver> tmpObserver = oc->mObserver;
            //IBinder binder = oc.mObserver.asBinder();
            List<AutoPtr<ObserverNode::ObserverEntry> >* list = oc->mNode->mObservers;
            Int32 size = list->GetSize();
            List<AutoPtr<ObserverNode::ObserverEntry> >::Iterator iter;

            for (Int32 i = 0; i < size; i++) {
                AutoPtr<ObserverNode::ObserverEntry> oe = (*list)[i];
                if (_CObject_Compare(tmpObserver, oe->mObserver)){
                    list->Remove(oe);
                   i--;
                   size--;
                }
            }
        }

    }
    if (syncToNetwork) {
        AutoPtr<ISyncManager> syncManager = GetSyncManager();
        if (NULL != syncManager) {
            String authority;
            uri->GetAuthority(&authority);
            AutoPtr<IAccount> nullAccount;
            FAIL_RETURN(syncManager->ScheduleLocalSync(nullAccount /* all accounts */, &authority));
        }
    }
    //TODO: restoreCallingIdentity(identityToken);
    if (NULL != calls) {
        calls->Clear();
        delete calls;
    }
    return NOERROR;
}