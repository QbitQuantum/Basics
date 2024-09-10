void wxGxDiscConnection::OnFileSystemEvent(wxFileSystemWatcherEvent& event)
{
    wxLogDebug(wxT("*** %s ***"), event.ToString().c_str());
    switch(event.GetChangeType())
    {
    case wxFSW_EVENT_CREATE:
        {
            //get object parent
            wxFileName oName = event.GetPath();
            wxGxObjectContainer *parent = wxDynamicCast(FindGxObjectByPath(oName.GetPath()), wxGxObjectContainer);
            if(!parent)
                return;
            //check doubles
            if(parent->IsNameExist(event.GetPath().GetFullName()))
                return;

            CPLString szPath(event.GetPath().GetFullPath().mb_str(wxConvUTF8));
            char **papszFileList = NULL;  
            papszFileList = CSLAddString( papszFileList, szPath );
	        if(m_pCatalog)
            {
                wxArrayLong ChildrenIds;
                m_pCatalog->CreateChildren(parent, papszFileList, ChildrenIds);
                for(size_t i = 0; i < ChildrenIds.GetCount(); ++i)
                    m_pCatalog->ObjectAdded(ChildrenIds[i]);
	        }
            CSLDestroy( papszFileList );
        }
        break;
    case wxFSW_EVENT_DELETE:
        {
            //search gxobject
            wxGxObject *current = FindGxObjectByPath(event.GetPath().GetFullPath());
            if(current)
            {
                current->Destroy();
                return;
            }
        }
        break;
    case wxFSW_EVENT_RENAME:
        {
            wxGxObject *current = FindGxObjectByPath(event.GetPath().GetFullPath());
            if(current)
            {
                current->SetName(event.GetNewPath().GetFullName());
                current->SetPath( CPLString( event.GetNewPath().GetFullPath().mb_str(wxConvUTF8) ) );
                wxGIS_GXCATALOG_EVENT_ID(ObjectChanged, current->GetId());

#ifdef __WXGTK__
                m_pWatcher->Remove(event.GetPath());
                if(!IsPathWatched(event.GetNewPath().GetFullPath()))
                {
                    m_pWatcher->Add(event.GetNewPath());

                }
#endif
                return;
            }
        }
        break;
    case wxFSW_EVENT_MODIFY:
        break;
    default:
    case wxFSW_EVENT_ACCESS:
    case wxFSW_EVENT_WARNING:
    case wxFSW_EVENT_ERROR:
        break;
    };
}