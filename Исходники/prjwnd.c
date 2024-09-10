LRESULT CALLBACK ProjectProc(HWND hwnd, UINT iMessage, WPARAM wParam,
    LPARAM lParam)
{
    int i;
    RECT rs;
    NM_TREEVIEW *nm;
    DWINFO info;
    LPNMTVKEYDOWN key;
    PROJECTITEM *data;
    TVHITTESTINFO hittest;
    HWND win;
    HTREEITEM oldSel;
    static HCURSOR origCurs;
    static BOOL dragging;
    static BOOL inView;
    static HTREEITEM srcItem, dstItem;
    switch (iMessage)
    {
        LOGFONT lf;
        case WM_SYSCOMMAND:
            if (wParam == SC_CLOSE)
                SendMessage(hwnd, WM_CLOSE, 0, 0);
            break;
//        case WM_SETTEXT:
//            return SendMessage(hwndTab, iMessage, wParam, lParam);
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            SetFocus(hwnd);
            break;
        case WM_NOTIFY:
            nm = (NM_TREEVIEW*)lParam;
            switch (nm->hdr.code)
            {
            case NM_CUSTOMDRAW:
                return CustomDraw(hwnd, (LPNMTVCUSTOMDRAW)nm);
            case N_EDITDONE:
                DoneRenaming();
                break;
            case TVN_BEGINDRAG:
                GetCursorPos(&hittest.pt);
                ScreenToClient(prjTreeWindow, &hittest.pt);
                srcItem = TreeView_HitTest(prjTreeWindow, &hittest);
                data = GetItemInfo(srcItem);
                if (data && (data->type == PJ_FILE || data->type == PJ_FOLDER))
                {
                    dragging = TRUE;
                    SetCapture(hwnd);
                    origCurs = SetCursor(dragCur);
                    inView = TRUE;
                }
                break;
            case TVN_KEYDOWN:
                key = (LPNMTVKEYDOWN)lParam;
                switch (key->wVKey)
                {
                    case VK_INSERT:
                        if (GetKeyState(VK_CONTROL) &0x80000000)
                        {
                            data = GetItemInfo(prjSelectedItem);
                            if (data)
                            {
                                int msg = -1;
                                switch (data->type)
                                {
                                    case PJ_WS:
                                        msg = IDM_EXISTINGPROJECT;
                                        break;
                                    case PJ_PROJ:
                                        msg = IDM_NEWFOLDER;
                                        break;
                                    case PJ_FOLDER:
                                        msg = IDM_EXISTINGFILE;
                                        break;
                                }
                                if (msg != -1)
                                    PostMessage(hwnd, WM_COMMAND, msg, 0);
                            }
                        }
                        else if (GetKeyState(VK_SHIFT) &0x80000000)
                        {
                            data = GetItemInfo(prjSelectedItem);
                            if (data)
                            {
                                int msg = -1;
                                switch (data->type)
                                {
                                    case PJ_WS:
                                        msg = IDM_NEWPROJECT;
                                        break;
                                    case PJ_PROJ:
                                        msg = IDM_NEWFOLDER;
                                        break;
                                    case PJ_FOLDER:
                                        msg = IDM_NEWFILE_P;
                                        break;
                                }
                                if (msg != -1)
                                    PostMessage(hwnd, WM_COMMAND, msg, 0);
                            }
                        }
                        else 
                        {
                            data = GetItemInfo(prjSelectedItem);
                            if (data && (data->type != PJ_WS))
                                PostMessage(hwnd, WM_COMMAND, IDM_RENAME, 0);
                        }
                        break;
                    case VK_DELETE:
                        if (!(GetKeyState(VK_CONTROL) &0x80000000) && !(GetKeyState(VK_SHIFT) &0x8000000))
                        {
                            data = GetItemInfo(prjSelectedItem);
                            if (data && (data->type == PJ_FOLDER || data->type == PJ_FILE))
                                PostMessage(hwnd, WM_COMMAND, IDM_REMOVE, 0);
                        }
                        break;
                    case VK_RETURN:
                        SendMessage(hwnd, WM_COMMAND, IDM_OPENFILES, 0);
                        break;
                    }
                    break;
                case NM_DBLCLK:
                    oldSel = prjSelectedItem;
                    GetCursorPos(&hittest.pt);
                    ScreenToClient(prjTreeWindow, &hittest.pt);
                    prjSelectedItem = TreeView_HitTest(prjTreeWindow, &hittest);
                    if (prjSelectedItem)
                        PostMessage(hwnd, WM_COMMAND, IDM_OPENFILES, 0);
                    prjSelectedItem = oldSel;
                    return 0;
                case NM_RCLICK:
                    GetCursorPos(&hittest.pt);
                    ScreenToClient(prjTreeWindow, &hittest.pt);
                    prjSelectedItem = TreeView_HitTest(prjTreeWindow, &hittest);
                    if (prjSelectedItem)
                    {
                        TreeView_SelectItem(prjTreeWindow, prjSelectedItem);
                    }
                    CreateProjectMenu();
                    break;
                case TVN_SELCHANGED:
                    nm = (NM_TREEVIEW*)lParam;
                    prjSelectedItem = nm->itemNew.hItem;
                    if (prjSelectedItem == 0)
                        prjSelectedItem = workArea->hTreeItem;
                    break;
                case TVN_ITEMEXPANDED:
                    nm = (NM_TREEVIEW *)lParam;
                    data = GetItemInfo(nm->itemNew.hItem);
                    if (data)
                    {
                        if (data->type == PJ_FOLDER)
                        {
                            TV_ITEM setitem;
                            memset(&setitem, 0, sizeof(setitem));
                            setitem.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
                            setitem.iImage = setitem.iSelectedImage = 
                                nm->action == TVE_EXPAND ? ilfolderOpen : ilfolderClose;
                            setitem.hItem = nm->itemNew.hItem;
                            TreeView_SetItem(prjTreeWindow, &setitem);
                        }
                        if (nm->action == TVE_EXPAND)
                        {
                            data->expanded = TRUE;
                        }
                        else
                            data->expanded = FALSE;
                        return 0;
                    }
                    break;
                case TVN_DELETEITEM:
                    nm = (NM_TREEVIEW *)lParam;
                    if (nm->itemOld.hItem == prjSelectedItem)
                        prjSelectedItem = TreeView_GetSelection(prjTreeWindow);
                    break;
            }
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case ID_TBPROFILE:
                    if (HIWORD(wParam) == CBN_SELENDOK)
                    {
                        int i = SendMessage(hwndTbProfile, CB_GETCURSEL, 0 , 0);
                        if (i != CB_ERR)
                        {
                            if (i == 0)
                            {
                                strcpy(currentProfileName, sysProfileName);
                            }
                            else
                            {
                                PROFILENAMELIST *pf = profileNames;
                                while (pf && --i)
                                    pf = pf->next;
                                if (pf)
                                {
                                    strcpy(currentProfileName, pf->name);
                                }
                            }
                            MarkChanged(workArea, TRUE);
                        }
                    }
                    break;
                case ID_TBBUILDTYPE:
                    if (HIWORD(wParam) == CBN_SELENDOK)
                    {
                        int i = SendMessage(hwndTbBuildType, CB_GETCURSEL, 0 , 0);
                        if (i != CB_ERR)
                        {
                            profileDebugMode = i == 0 ? 1 : 0;
                            MarkChanged(workArea, TRUE);
                        }
                    }
                    break;
                case IDM_RESETPROFILECOMBOS:
                {
                    HWND htemp;
                    PROFILENAMELIST *pf;
                    int selected,n;
                    int count;
                    POINT pt;
                    pf = profileNames;
                    selected = 0;
                    count = 0;
                    SendMessage(hwndTbProfile, CB_RESETCONTENT, 0, 0);
                    SendMessage(hwndTbProfile, CB_ADDSTRING, 0, (LPARAM)sysProfileName);
                    while (pf)
                    {
                        count++;
                        if (!strcmp(pf->name,currentProfileName))
                            selected = count;
                        SendMessage(hwndTbProfile, CB_ADDSTRING, 0, (LPARAM)pf->name);
                            
                        pf = pf->next;
                            
                    }
                    SendMessage(hwndTbProfile, CB_SETCURSEL, selected, 0);
                    SendMessage(hwndTbBuildType, CB_RESETCONTENT, 0, 0);
                    SendMessage(hwndTbBuildType, CB_ADDSTRING, 0, (LPARAM)"Debug");
                    SendMessage(hwndTbBuildType, CB_ADDSTRING, 0, (LPARAM)"Release");
                    SendMessage(hwndTbBuildType, CB_SETCURSEL, profileDebugMode ? 0 : 1, 0);
                    
                    pt.x = 5;
                    pt.y = 5;
                    htemp = ChildWindowFromPoint(hwndTbProfile, pt);
                    SendMessage(htemp, EM_SETREADONLY, 1, 0);
                    htemp = ChildWindowFromPoint(hwndTbBuildType, pt);
                    SendMessage(htemp, EM_SETREADONLY, 1, 0);
                    EnableWindow(hwndTbProfile, TRUE);
                    EnableWindow(hwndTbBuildType, TRUE);
                    break;
                }
            case IDM_IMPORT_CWS:
                ImportProject(FALSE);
                break;
            case IDM_IMPORT_CTG:
                ImportProject(TRUE);
                break;
            case IDM_DOSWINDOW:
            {
                DosWindow(activeProject ? activeProject->realName : NULL, NULL, NULL, NULL, NULL);
            }
                break;
            case IDM_MAKEWINDOW:
            {
                char exec[MAX_PATH];
                sprintf(exec, "%s\\bin\\imake.exe", szInstallPath);
                DosWindow(activeProject ? activeProject->realName : NULL, exec, "", "Custom Make", "Make Is Complete.");
            }
                break;
            case IDM_RUN:
                SaveWorkArea(workArea);
                dbgRebuildMain(wParam);
                break;
            case IDM_SETACTIVEPROJECT:
                ProjectSetActive();
                break;
            case IDM_NEWFILE_P:
                ProjectNewFile();
                PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
                break;
            case IDM_EXISTINGFILE:
                ProjectExistingFile();
                PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
                break;
            case IDM_NEWPROJECT:
                ProjectNewProject();
                PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
                break;
            case IDM_EXISTINGPROJECT:
                ProjectExistingProject();
                PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
                break ;
            case IDM_REMOVE:
                ProjectRemove();
                PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
                break;
            case IDM_RENAME:
                ProjectRename();
                break;
            case IDM_NEWFOLDER:
                ProjectNewFolder();
                PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
                break;
            case IDM_NEWWS:
                if (uState != notDebugging)
                {
                    if (ExtendedMessageBox("WorkArea", MB_OKCANCEL, 
                        "This action requires the debugger to be stopped.") != IDOK)
                    {
                        break;
                    }
                    abortDebug();
                }
                SelectWindow(DID_PROJWND);
                ProjectNewWorkArea();
                break;
            case IDM_OPENWS:
                if (uState != notDebugging)
                {
                    if (ExtendedMessageBox("WorkArea", MB_OKCANCEL, 
                        "This action requires the debugger to be stopped.") != IDOK)
                    {
                        break;
                    }
                    abortDebug();
                }
                SelectWindow(DID_PROJWND);
                ProjectExistingWorkArea();
                break;
            case IDM_CLOSEWS:
                if (making)
                    break;
                if (uState != notDebugging)
                {
                    if (ExtendedMessageBox("WorkArea", MB_OKCANCEL, 
                        "This action requires the debugger to be stopped.") != IDOK)
                    {
                        break;
                    }
                    abortDebug();
                }
                CloseWorkArea();
                break;
            case IDM_SAVEWS:
                SaveAllProjects(workArea, TRUE);
                break;
            case IDM_COMPILEFILEFROMTREE:
            {
                PROJECTITEM *data = GetItemInfo(prjSelectedItem);
                if (data && data->type == PJ_FILE) 
                {
                    unlink(data->outputName);
                    Maker(data, TRUE);
                }        
            }
                break;
            case IDM_COMPILEFILE:
                win = (HWND)SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0);
                if (IsWindow(win) && IsEditWindow(win))
                {
                    HTREEITEM item = FindItemByWind(win);
                    PROJECTITEM *data = GetItemInfo(item);
                    if (data) {
                        unlink(data->outputName);
                        Maker(data, TRUE);
                    }
                }
                break;
            case IDM_GENMAKE:
                if (workArea && workArea->children)
                {
                    genMakeFile(workArea);
                }
                else
                {
                    ExtendedMessageBox("Makefile Generation", MB_SETFOREGROUND |
                        MB_SYSTEMMODAL, 
                        "You need at least one project to generate a make file");
                }
                break;
            case IDM_MAKE:
                if (HIWORD(wParam))
                    if (GetKeyState(VK_CONTROL) &0x80000000)
                        SendMessage(hwnd, WM_COMMAND, IDM_COMPILEFILE, 0);
                    else if (GetKeyState(VK_SHIFT) &0x80000000)
                        Maker(activeProject, FALSE);
                    else
                        Maker(workArea, FALSE);
                else
                    Maker(workArea, FALSE);
                break;                
            case IDM_MAKE_RIGHTCLICK:
                if (HIWORD(wParam))
                    if (GetKeyState(VK_CONTROL) &0x80000000)
                        SendMessage(hwnd, WM_COMMAND, IDM_COMPILEFILE, 0);
                    else if (GetKeyState(VK_SHIFT) &0x80000000)
                        Maker(activeProject, FALSE);
                    else
                        Maker(workArea, FALSE);
                else
                {
                    if (prjSelectedItem)
                    {
                        PROJECTITEM *data = GetItemInfo(prjSelectedItem);
                        if (data)
                        {
                            Maker(data, FALSE);
                            break;
                        }
                    }
            
                    Maker(workArea, FALSE);
                }
                break;
            case IDM_BUILDALL:
                Maker(workArea, TRUE);
                break;                
            case IDM_BUILDALL_RIGHTCLICK:
                if (prjSelectedItem)
                {
                    PROJECTITEM *data = GetItemInfo(prjSelectedItem);
                    if (data)
                    {
                        Maker(data, TRUE);
                        break;
                    }
                }
                Maker(workArea, TRUE);
                break;
            case IDM_BUILDSELECTED:
                Maker(activeProject, FALSE);
                break;
            case IDM_STOPBUILD:
                StopBuild();
                break;
            case IDM_CALCULATEDEPENDS:
                CalculateProjectDepends(GetItemInfo(prjSelectedItem));
                break;
            case IDM_RUNNODEBUG:
            {
                SaveWorkArea(workArea);
                RunProgram(activeProject);
                break;
            }
            case IDM_SELECTPROFILE:
                SelectProfileDialog();
                break;
            case IDM_ACTIVEPROJECTPROPERTIES:
                if (activeProject)
                    prjSelectedItem = activeProject->hTreeItem;
                // fall through
            case IDM_PROJECTPROPERTIES:
                data = GetItemInfo(prjSelectedItem);
                ShowBuildProperties(data);
                break;
            case IDM_PROJECTDEPENDS:
                data = GetItemInfo(prjSelectedItem);
                EditProjectDependencies(data);
                break;
            case IDM_OPENFILES:
                data = GetItemInfo(prjSelectedItem);
                if (data)
                    if (data->type == PJ_FILE)
                    {
                        if (strlen(data->realName) >= 3 && !stricmp(data->realName + strlen(data->realName) -3, ".rc"))
                        {
                            NavigateToResource(data);
                        }
                        else
                        {
                            strcpy(info.dwName, data->realName);
                            strcpy(info.dwTitle, data->displayName);
                            info.dwLineNo =  - 1;
                            info.logMRU = FALSE;
                            info.newFile = FALSE;
                            CreateDrawWindow(&info, TRUE);
                        }
                    }
                break;
            case IDM_CLOSE:
                SendMessage(hwnd, WM_CLOSE, 0, 0);
                break;
            default:
                return DefWindowProc(hwnd, iMessage, wParam, lParam);
            }
            break;
        case WM_LBUTTONUP:
            if (dragging)
            {
                SetCursor(origCurs);
                ReleaseCapture();
                dragging = FALSE;
                TreeView_SelectDropTarget(prjTreeWindow, NULL);
                if (inView && dstItem != srcItem && srcItem && dstItem)
                {
                    DragTo(dstItem, srcItem);
                }
            }
            break;
        case WM_MOUSEMOVE:
            if (dragging)
            {
                hittest.pt.x = (long)(short)LOWORD(lParam);
                hittest.pt.y = (long)(short)HIWORD(lParam);
                
                dstItem = TreeView_HitTest(prjTreeWindow, &hittest);
                if (dstItem && dstItem != srcItem)
                {
                    PROJECTITEM *srcData = GetItemInfo(srcItem);
                    data = GetItemInfo(dstItem);
                    if (srcData && data)
                    {
                        PROJECTITEM *p = data->parent;
                        while (p)
                            if (p == srcData)
                                break;
                            else
                                p = p->parent;
                        if (p)
                        {
                            if (inView)
                            {
                                inView = FALSE;
                                SetCursor(noCur);
                                TreeView_SelectDropTarget(prjTreeWindow, NULL);
                            }
                            break;
                        }
                    }
                    if (data && (data->type == PJ_PROJ || data->type == PJ_FOLDER))
                    {
                        if (!inView)
                        {
                            inView = TRUE;
                            SetCursor(dragCur);
                        }
                        TreeView_SelectDropTarget(prjTreeWindow, dstItem);
                    }
                    else
                    {
                        if (inView)
                        {
                            inView = FALSE;
                            SetCursor(noCur);
                            TreeView_SelectDropTarget(prjTreeWindow, NULL);
                        }
                    }
                }
                else
                {
                    if (inView)
                    {
                        inView = FALSE;
                        SetCursor(noCur);
                        TreeView_SelectDropTarget(prjTreeWindow, NULL);
                    }
                }
            }
            break;
        case WM_SETFOCUS:
            PostMessage(hwndFrame, WM_REDRAWTOOLBAR, 0, 0);
            SetFocus(prjTreeWindow);
            break;
        case WM_CREATE:
            hwndProject = hwnd;
            GetClientRect(hwnd, &rs);

            treeViewSelected = 0;
            dragCur = LoadCursor(hInstance, "ID_DRAGCUR");
            noCur = LoadCursor(hInstance, "ID_NODRAGCUR");
            folderClose = LoadBitmap(hInstance, "ID_FOLDERCLOSE");
            folderOpen = LoadBitmap(hInstance, "ID_FOLDEROPEN");
            treeIml = ImageList_Create(16, 16, ILC_COLOR24, IL_IMAGECOUNT+2, 0);
            
            mainIml = LoadBitmap(hInstance, "ID_FILES");
            ChangeBitmapColor(mainIml, 0xffffff, RetrieveSysColor(COLOR_WINDOW));
            ImageList_Add(treeIml, mainIml, NULL);
            ilfolderClose = ImageList_Add(treeIml, folderClose, 0);
            ilfolderOpen = ImageList_Add(treeIml, folderOpen, 0);
            DeleteObject(folderClose);
            DeleteObject(folderOpen);
            DeleteObject(mainIml);
            prjTreeWindow = CreateWindowEx(0, sztreeDoubleBufferName, "", WS_VISIBLE |
                WS_CHILD | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_TRACKSELECT,
                0, 0, rs.right, rs.bottom, hwnd, (HMENU)ID_TREEVIEW,
                hInstance, NULL);
            TreeView_SetImageList(prjTreeWindow, treeIml, TVSIL_NORMAL);
            lf = systemDialogFont;
            projFont = CreateFontIndirect(&lf);
            lf.lfItalic = TRUE;
            italicProjFont = CreateFontIndirect(&lf);
            lf.lfItalic = FALSE;
            lf.lfWeight = FW_BOLD;
            boldProjFont = CreateFontIndirect(&lf);
            SendMessage(prjTreeWindow, WM_SETFONT, (WPARAM)boldProjFont, 0);
            return 0;
        case WM_CLOSE:
            SaveAllProjects(workArea, FALSE);
            break;
        case WM_DESTROY:
            FreeSubTree(workArea, FALSE);
            DestroyWindow(prjTreeWindow);
            DeleteObject(projFont);
            DeleteObject(boldProjFont);
            DeleteObject(italicProjFont);
            DestroyCursor(dragCur);
            DestroyCursor(noCur);
            hwndProject = 0;
            break;
        case WM_SIZE:
            MoveWindow(prjTreeWindow, 0, 0, LOWORD(lParam), HIWORD(lParam), 0);
            break;
        default:
            break;
    }
    return DefWindowProc(hwnd, iMessage, wParam, lParam);
}