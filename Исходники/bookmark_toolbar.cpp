void BookmarkToolBar::OnContextMenu(CWnd* pWnd, CPoint aPoint)
{
    CToolBarCtrl &sToolBarCtrl = GetToolBarCtrl();

    CPoint sClientPoint(aPoint);
    ScreenToClient(&sClientPoint);

    xpr_bool_t sSucceeded = XPR_FALSE;
    xpr_sint_t sIndex = sToolBarCtrl.HitTest(&sClientPoint);
    if (GetKeyState(VK_CONTROL) < 0 && sIndex >= 0)
    {
        BookmarkItem *sBookmarkItem = BookmarkMgr::instance().getBookmark(sIndex);
        if (sBookmarkItem != XPR_NULL)
        {
            LPITEMIDLIST sFullPidl = sBookmarkItem->getPidl();
            if (sFullPidl != XPR_NULL)
            {
                xpr_bool_t    sResult;
                LPSHELLFOLDER sShellFolder = XPR_NULL;
                LPCITEMIDLIST sPidl        = XPR_NULL;

                sResult = fxfile::base::Pidl::getSimplePidl(sFullPidl, sShellFolder, sPidl);
                if (SUCCEEDED(sResult) && sShellFolder != XPR_NULL && sPidl != XPR_NULL)
                {
                    ContextMenu sContextMenu(GetSafeHwnd());
                    if (sContextMenu.init(sShellFolder, &sPidl, 1))
                    {
                        TBBUTTON sTbButton = {0};
                        sToolBarCtrl.GetButton(sIndex, &sTbButton);
                        sToolBarCtrl.SetState(sTbButton.idCommand, TBSTATE_MARKED | TBSTATE_ENABLED);

                        xpr_uint_t sId = sContextMenu.trackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_RIGHTBUTTON, &aPoint, CMF_EXPLORE);
                        if (sId != -1)
                        {
                            sId -= sContextMenu.getFirstId();

                            xpr_tchar_t sVerb[0xff] = {0};
                            sContextMenu.getCommandVerb(sId, sVerb, 0xfe);

                            xpr_bool_t sSelfInvoke = XPR_FALSE;

                            if (_tcsicmp(sVerb, CMID_VERB_OPEN) == 0)
                            {
                                gFrame->gotoBookmark(sIndex);
                                sSelfInvoke = XPR_TRUE;
                            }

                            if (sSelfInvoke == XPR_FALSE)
                                sContextMenu.invokeCommand(sId);
                        }

                        sToolBarCtrl.GetButton(sIndex, &sTbButton);
                        sToolBarCtrl.SetState(sTbButton.idCommand, TBSTATE_ENABLED);
                    }

                    sContextMenu.destroy();

                    sSucceeded = XPR_TRUE;
                }

                COM_RELEASE(sShellFolder);
                COM_FREE(sFullPidl);
            }
        }
    }

    if (sSucceeded == XPR_FALSE)
    {
        BCMenu sMenu;
        if (sMenu.LoadMenu(IDR_COOLBAR_BOOKMARKBAR) == XPR_TRUE)
        {
            BCMenu *sPopupMenu = (BCMenu *)sMenu.GetSubMenu(0);
            if (XPR_IS_NOT_NULL(sPopupMenu))
                sPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, aPoint, AfxGetMainWnd());
        }
    }
}