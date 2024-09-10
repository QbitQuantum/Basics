/**
 * When the component table dialog is closed,
 * work out if we need to save any changed.
 * If so, capture those changes and push them to the undo stack.
 */
bool DIALOG_BOM_EDITOR::TransferDataFromWindow()
{
    if( m_bom->HaveFieldsChanged() )
    {
         /**
         * As we may be saving changes across multiple sheets,
         * we need to first determine which changes need to be made to which sheet.
         * To this end, we perform the following:
         * 1. Save the "path" of the currently displayed sheet
         * 2. Create a MAP of <SheetPath:ChangeList> changes that need to be made
         * 3. Push UNDO actions to appropriate sheets
         * 4. Perform all the update actions
         * 5. Reset the view to the current sheet
         */

        auto currentSheet = m_parent->GetCurrentSheet();

        //! Create a map of changes required for each sheet
        std::map<wxString, SheetUndoList> undoSheetMap;

        // List of components that have changed
        auto changed = m_bom->GetChangedComponents();

        ITEM_PICKER picker;

        // Iterate through each of the components that were changed
        for( auto ref : changed )
        {
            // Extract the SCH_COMPONENT* object
            auto cmp = ref.GetComp();

            wxString path = ref.GetSheetPath().Path();

            // Push the component into the picker list
            picker = ITEM_PICKER( cmp, UR_CHANGED );
            picker.SetFlags( cmp->GetFlags() );

            /*
             * If there is not currently an undo list for the given sheet,
             * create an empty one
             */

            if( undoSheetMap.count( path ) == 0 )
            {
                SheetUndoList newList;

                newList.path = ref.GetSheetPath();

                undoSheetMap[path] = newList;
            }

            auto& pickerList = undoSheetMap[path];

            pickerList.items.PushItem( picker );
        }

        // Iterate through each sheet that needs updating
        for( auto it = undoSheetMap.begin(); it != undoSheetMap.end(); ++it )
        {
            auto undo = it->second;

            m_parent->SetCurrentSheet( undo.path );
            m_parent->SaveCopyInUndoList( undo.items, UR_CHANGED );
            m_parent->OnModify();
        }

        // Make all component changes
        m_bom->ApplyFieldChanges();

        // Redraw the current sheet and mark as dirty
        m_parent->Refresh();
        m_parent->OnModify();

        // Reset the view to where we left the user
        m_parent->SetCurrentSheet(currentSheet);

    }

    return true;
}