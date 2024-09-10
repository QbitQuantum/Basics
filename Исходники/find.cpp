void SCH_EDIT_FRAME::OnFindReplace( wxFindDialogEvent& aEvent )
{
    static int              nextFoundIndex = 0;
    SCH_ITEM*               item;
    SCH_SHEET_PATH*         sheet;
    SCH_SHEET_LIST          schematic( g_RootSheet );
    SCH_FIND_COLLECTOR_DATA data;
    SCH_FIND_REPLACE_DATA   searchCriteria;

    searchCriteria.SetFlags( aEvent.GetFlags() );
    searchCriteria.SetFindString( aEvent.GetFindString() );
    searchCriteria.SetReplaceString( aEvent.GetReplaceString() );
    m_foundItems.SetReplaceString( aEvent.GetReplaceString() );

    if( IsSearchCacheObsolete( searchCriteria ) )
    {
        if( aEvent.GetFlags() & FR_CURRENT_SHEET_ONLY && g_RootSheet->CountSheets() > 1 )
        {
            m_foundItems.Collect( searchCriteria, m_CurrentSheet );
        }
        else
        {
            m_foundItems.Collect( searchCriteria );
        }

        // Restore the next found index on cache refresh.  Prevents single replace events
        // from starting back at the beginning of the cache.
        m_foundItems.SetFoundIndex( nextFoundIndex );
    }

    if( aEvent.GetEventType() == wxEVT_COMMAND_FIND_REPLACE_ALL )
    {
        while( ( item = (SCH_ITEM*) m_foundItems.GetItem( data ) ) != NULL )
        {
            SCH_ITEM* undoItem = data.GetParent();

            // Don't save child items in undo list.
            if( undoItem == NULL )
                undoItem = item;

            SetUndoItem( undoItem );

            sheet = schematic.GetSheetByPath( data.GetSheetPath() );

            wxCHECK_RET( sheet != NULL, wxT( "Could not find sheet path " ) + data.GetSheetPath() );

            if( m_foundItems.ReplaceItem( sheet ) )
            {
                OnModify();
                SaveUndoItemInUndoList( undoItem );
                updateFindReplaceView( aEvent );
            }

            m_foundItems.IncrementIndex();

            if( m_foundItems.PassedEnd() )
                break;
        }
    }
    else
    {
        item = (SCH_ITEM*) m_foundItems.GetItem( data );

        wxCHECK_RET( item != NULL, wxT( "Invalid replace item in find collector list." ) );

        SCH_ITEM* undoItem = data.GetParent();

        if( undoItem == NULL )
            undoItem = item;

        SetUndoItem( undoItem );

        sheet = schematic.GetSheetByPath( data.GetSheetPath() );

        wxCHECK_RET( sheet != NULL, wxT( "Could not find sheet path " ) + data.GetSheetPath() );

        if( m_foundItems.ReplaceItem( sheet ) )
        {
            OnModify();
            SaveUndoItemInUndoList( undoItem );
            updateFindReplaceView( aEvent );
        }

        m_foundItems.IncrementIndex();
        nextFoundIndex = m_foundItems.GetFoundIndex();
    }

    // End the replace if we are at the end if the list.  This prevents an infinite loop if
    // wrap search is selected and all of the items have been replaced with a value that
    // still satisfies the search criteria.
    if( m_foundItems.PassedEnd() )
        aEvent.SetFlags( aEvent.GetFlags() & ~FR_REPLACE_ITEM_FOUND );
}