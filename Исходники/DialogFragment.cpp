void DialogFragment::DismissInternal(
    /* [in] */ Boolean allowStateLoss)
{
    if (mDismissed) {
        return;
    }
    mDismissed = TRUE;
    mShownByMe = FALSE;
    if (mDialog != NULL) {
        IDialogInterface::Probe(mDialog)->Dismiss();
        mDialog = NULL;
    }
    mViewDestroyed = TRUE;
    if (mBackStackId >= 0) {
        AutoPtr<IFragmentManager> frMgr;
        GetFragmentManager((IFragmentManager**)&frMgr);
        frMgr->PopBackStack(mBackStackId,
                IFragmentManager::POP_BACK_STACK_INCLUSIVE);
        mBackStackId = -1;
    } else {
        AutoPtr<IFragmentTransaction> ft;
        AutoPtr<IFragmentManager> frMgr;
        GetFragmentManager((IFragmentManager**)&frMgr);
        frMgr->BeginTransaction((IFragmentTransaction**)&ft);
        ft->Remove(this);
        if (allowStateLoss) {
            Int32 result;
            ft->CommitAllowingStateLoss(&result);
        } else {
            Int32 id;
            ft->Commit(&id);
        }
    }
}