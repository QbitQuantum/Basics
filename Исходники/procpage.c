static void ProcessPageOnNotify(WPARAM wParam, LPARAM lParam)
{
    int                idctrl;
    LPNMHDR            pnmh;
    LPNMLISTVIEW    pnmv;
    NMLVDISPINFO*    pnmdi;
    LPNMHEADER        pnmhdr;
    LVITEM            lvitem;
    ULONG            Index;
    ULONG            ColumnIndex;
    IO_COUNTERS        iocounters;
    TIME            time;

    idctrl = (int) wParam;
    pnmh = (LPNMHDR) lParam;
    pnmv = (LPNMLISTVIEW) lParam;
    pnmdi = (NMLVDISPINFO*) lParam;
    pnmhdr = (LPNMHEADER) lParam;

    if (pnmh->hwndFrom == hProcessPageListCtrl)
    {
        switch (pnmh->code)
        {
#if 0
        case LVN_ITEMCHANGED:
            ProcessPageUpdate();
            break;
#endif
            
        case LVN_GETDISPINFO:

            if (!(pnmdi->item.mask & LVIF_TEXT))
                break;
            
            ColumnIndex = pnmdi->item.iSubItem;
            Index = pnmdi->item.iItem;

            if (ColumnDataHints[ColumnIndex] == COLUMN_IMAGENAME)
                PerfDataGetImageName(Index, pnmdi->item.pszText, pnmdi->item.cchTextMax);
            if (ColumnDataHints[ColumnIndex] == COLUMN_PID)
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetProcessId(Index));
            if (ColumnDataHints[ColumnIndex] == COLUMN_USERNAME)
                PerfDataGetUserName(Index, pnmdi->item.pszText, pnmdi->item.cchTextMax);
            if (ColumnDataHints[ColumnIndex] == COLUMN_SESSIONID)
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetSessionId(Index));
            if (ColumnDataHints[ColumnIndex] == COLUMN_CPUUSAGE)
                wsprintf(pnmdi->item.pszText, _T("%02d"), PerfDataGetCPUUsage(Index));
            if (ColumnDataHints[ColumnIndex] == COLUMN_CPUTIME)
            {
                DWORD dwHours;
                DWORD dwMinutes;
                DWORD dwSeconds;
                ULONGLONG secs;

                time = PerfDataGetCPUTime(Index);
                secs = time.QuadPart / 10000000;
                dwHours = secs / 3600;
                dwMinutes = (secs % 3600) / 60;
                dwSeconds = (secs % 3600) % 60;
                wsprintf(pnmdi->item.pszText, _T("%d:%02d:%02d"), dwHours, dwMinutes, dwSeconds);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_MEMORYUSAGE)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetWorkingSetSizeBytes(Index) / 1024);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
                _tcscat(pnmdi->item.pszText, _T(" K"));
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_PEAKMEMORYUSAGE)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetPeakWorkingSetSizeBytes(Index) / 1024);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
                _tcscat(pnmdi->item.pszText, _T(" K"));
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_MEMORYUSAGEDELTA)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetWorkingSetSizeDelta(Index) / 1024);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
                _tcscat(pnmdi->item.pszText, _T(" K"));
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_PAGEFAULTS)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetPageFaultCount(Index));
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_PAGEFAULTSDELTA)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetPageFaultCountDelta(Index));
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_VIRTUALMEMORYSIZE)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetVirtualMemorySizeBytes(Index) / 1024);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
                _tcscat(pnmdi->item.pszText, _T(" K"));
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_PAGEDPOOL)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetPagedPoolUsagePages(Index) / 1024);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
                _tcscat(pnmdi->item.pszText, _T(" K"));
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_NONPAGEDPOOL)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetNonPagedPoolUsagePages(Index) / 1024);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
                _tcscat(pnmdi->item.pszText, _T(" K"));
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_BASEPRIORITY)
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetBasePriority(Index));
            if (ColumnDataHints[ColumnIndex] == COLUMN_HANDLECOUNT)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetHandleCount(Index));
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_THREADCOUNT)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetThreadCount(Index));
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_USEROBJECTS)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetUSERObjectCount(Index));
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_GDIOBJECTS)
            {
                wsprintf(pnmdi->item.pszText, _T("%d"), PerfDataGetGDIObjectCount(Index));
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_IOREADS)
            {
                PerfDataGetIOCounters(Index, &iocounters);
                /* wsprintf(pnmdi->item.pszText, _T("%d"), iocounters.ReadOperationCount); */
#ifdef UNICODE
#define _ui64toa _ui64tow
#else
#endif
                _ui64toa(iocounters.ReadOperationCount, pnmdi->item.pszText, 10);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_IOWRITES)
            {
                PerfDataGetIOCounters(Index, &iocounters);
                /* wsprintf(pnmdi->item.pszText, _T("%d"), iocounters.WriteOperationCount); */
                _ui64toa(iocounters.WriteOperationCount, pnmdi->item.pszText, 10);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_IOOTHER)
            {
                PerfDataGetIOCounters(Index, &iocounters);
                /* wsprintf(pnmdi->item.pszText, _T("%d"), iocounters.OtherOperationCount); */
                _ui64toa(iocounters.OtherOperationCount, pnmdi->item.pszText, 10);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_IOREADBYTES)
            {
                PerfDataGetIOCounters(Index, &iocounters);
                /* wsprintf(pnmdi->item.pszText, _T("%d"), iocounters.ReadTransferCount); */
                _ui64toa(iocounters.ReadTransferCount, pnmdi->item.pszText, 10);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_IOWRITEBYTES)
            {
                PerfDataGetIOCounters(Index, &iocounters);
                /* wsprintf(pnmdi->item.pszText, _T("%d"), iocounters.WriteTransferCount); */
                _ui64toa(iocounters.WriteTransferCount, pnmdi->item.pszText, 10);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }
            if (ColumnDataHints[ColumnIndex] == COLUMN_IOOTHERBYTES)
            {
                PerfDataGetIOCounters(Index, &iocounters);
                /* wsprintf(pnmdi->item.pszText, _T("%d"), iocounters.OtherTransferCount); */
                _ui64toa(iocounters.OtherTransferCount, pnmdi->item.pszText, 10);
                CommaSeparateNumberString(pnmdi->item.pszText, pnmdi->item.cchTextMax);
            }

            break;

        case NM_RCLICK:

            for (Index=0; Index<(ULONG)ListView_GetItemCount(hProcessPageListCtrl); Index++)
            {
                memset(&lvitem, 0, sizeof(LVITEM));

                lvitem.mask = LVIF_STATE;
                lvitem.stateMask = LVIS_SELECTED;
                lvitem.iItem = Index;

                SendMessage(hProcessPageListCtrl, LVM_GETITEM, 0, (LPARAM) &lvitem);

                if (lvitem.state & LVIS_SELECTED)
                    break;
            }

            if ((ListView_GetSelectedCount(hProcessPageListCtrl) == 1) &&
                (PerfDataGetProcessId(Index) != 0))
            {
                ProcessPageShowContextMenu(PerfDataGetProcessId(Index));
            }

            break;

        }
    }
    else if (pnmh->hwndFrom == hProcessPageHeaderCtrl)
    {
        switch (pnmh->code)
        {
        case HDN_ITEMCLICK:

            /*
             * FIXME: Fix the column sorting
             *
             *ListView_SortItems(hApplicationPageListCtrl, ApplicationPageCompareFunc, NULL);
             *bSortAscending = !bSortAscending;
             */

            break;

        case HDN_ITEMCHANGED:

            UpdateColumnDataHints();

            break;

        case HDN_ENDDRAG:

            UpdateColumnDataHints();

            break;

        }
    }

}