xpr_sint_t FolderPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (super::OnCreate(lpCreateStruct) == -1)
        return -1;

    mFolderCtrl = new FolderCtrl;
    if (XPR_IS_NULL(mFolderCtrl))
        return -1;

    mFolderCtrl->setObserver(dynamic_cast<FolderCtrlObserver *>(this));
    mFolderCtrl->setViewIndex(mViewIndex);

    if (mFolderCtrl->Create(this, CTRL_ID_FOLDER_CTRL, CRect(0, 0, 0, 0)) == XPR_FALSE)
    {
        XPR_SAFE_DELETE(mFolderCtrl);
        return -1;
    }

    mFolderCtrl->setImageList(&SingletonManager::get<ImgListManager>().mSysImgList16);

    CWnd *sToolTipWnd = FromHandle((HWND)mFolderCtrl->SendMessage(TVM_GETTOOLTIPS));
    if (XPR_IS_NOT_NULL(sToolTipWnd))
        sToolTipWnd->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    mFolderCtrl->init(XPR_NULL, XPR_FALSE);

    setFolderOption(mFolderCtrl, *gOpt);

    return 0;
}