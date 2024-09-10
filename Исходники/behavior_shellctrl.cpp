    void OnItemExpanding(EShellTreeItem& tItem)
    {
        //LPNMTREEVIEW pnmtv = (LPNMTREEVIEW) pnmh;

#ifdef __ATLCTRLX_H__
        CWaitCursor cursor;
#endif

        // 展开过就去掉“没展开”属性
        tItem.remove_attribute("not-expand-ever");
        // 删掉占位的那个项目
        EShellTreeItem tiFake = tItem.find_first("option");
        if (tiFake.is_valid())
        {
            tiFake.destroy();
        }

        // 遍历目录下的子文件夹
        PSHELLITEMINFO pFolderItem = reinterpret_cast<PSHELLITEMINFO>(tItem.GetData());
        CComPtr<IShellFolder> spFolder;
        if( pFolderItem->pidlNode != NULL ) 
        {
            if( FAILED(pFolderItem->spFolder->BindToObject(pFolderItem->pidlNode,
                NULL, IID_IShellFolder, (LPVOID*)&spFolder)) ) 
                return ;
        }
        else 
        {
            spFolder = pFolderItem->spFolder;
        }

        // Add children
        CComPtr<IEnumIDList> spEnum;
        DWORD dwEnumFlags = SHCONTF_FOLDERS;
        if( (m_dwShellStyle & SCT_EX_SHOWHIDDEN) != 0 ) 
            dwEnumFlags |= SHCONTF_INCLUDEHIDDEN;
        if( SUCCEEDED(spFolder->EnumObjects(NULL, dwEnumFlags, &spEnum)) ) 
        {
            CPidl pidl;
            DWORD  dwFetched;
            while( (spEnum->Next(1, &pidl, &dwFetched) == S_OK) && (dwFetched > 0) ) 
            {
                // Get attributes and filter some items
                DWORD dwAttribs = SFGAO_DISPLAYATTRMASK | SFGAO_HASSUBFOLDER;
                if( !_FilterItem(spFolder, pidl, dwAttribs) ) 
                {
                    _InsertItem(spFolder, pFolderItem->pidlFull, pidl, dwAttribs, tItem);
                }
                pidl.Delete();
            }
        }
    }