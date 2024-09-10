BOOL plResponderProc::DragListProc(HWND hWnd, DRAGLISTINFO *info)
{
    static int oldIdx = -1;

    int curIdx = LBItemFromPt(info->hWnd, info->ptCursor, TRUE);

    switch (info->uNotification)
    {
        // Allow the drag
        case DL_BEGINDRAG:
            // When you click on an item in the listbox, the rollups are changed and Max can
            // shift the position of dialog you were just clicking in.  Since this happens
            // before you let go of the mouse button, the listbox thinks you are dragging.
            // To get around it, we don't allow a selection change and a drag in the same click.
            if (fIgnoreNextDrop)
            {
                SetWindowLong(hWnd, DWL_MSGRESULT, FALSE);
            }
            else
            {
                oldIdx = curIdx;
                SetWindowLong(hWnd, DWL_MSGRESULT, TRUE);
            }
            return TRUE;

        case DL_DRAGGING:
            {
                if (curIdx < oldIdx)
                    DrawInsert(hWnd, info->hWnd, curIdx);
                else if (curIdx > oldIdx && ListBox_GetCount(info->hWnd) > curIdx+1)
                    DrawInsert(hWnd, info->hWnd, curIdx+1);
                else
                    DrawInsert(hWnd, info->hWnd, -1);
            }
            return TRUE;

        case DL_CANCELDRAG:
            // Clear drag arrow
            DrawInsert(hWnd, info->hWnd, -1);
            return TRUE;

        case DL_DROPPED:
        {
            if (fIgnoreNextDrop)
            {
                fIgnoreNextDrop = false;
                return TRUE;
            }

            // Clear drag arrow
            DrawInsert(hWnd, info->hWnd, -1);

            if (curIdx != -1 && oldIdx != -1 && curIdx != oldIdx)
            {
                // Make sure this won't mess up any wait commands, or at least
                // that the user approves if it does.
                if (!ResponderWait::ValidateCmdMove(fStatePB, oldIdx, curIdx))
                    return TRUE;

                MoveCommand(oldIdx, curIdx);
            }

            return TRUE;
        }
    }

    return FALSE;
}