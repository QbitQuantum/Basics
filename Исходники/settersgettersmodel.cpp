wxDataViewItem SettersGettersModel::DoInsertItem(const wxDataViewItem& insertBeforeMe, const wxVector<wxVariant>& data, bool isContainer, wxClientData *clientData)
{
    SettersGettersModel_Item* child = new SettersGettersModel_Item();
    child->SetIsContainer(isContainer);
    child->SetClientObject( clientData );
    child->SetData( data );

    // find the location where to insert the new item
    SettersGettersModel_Item* node = reinterpret_cast<SettersGettersModel_Item*>(insertBeforeMe.m_pItem);
    if ( !node )
        return wxDataViewItem();

    wxVector<SettersGettersModel_Item*>::iterator where = std::find(m_data.begin(), m_data.end(), node);

    if ( where !=  m_data.end() ) {
        // top level item
        m_data.insert( where, child );

    } else {

        if ( !node->GetParent() )
            return wxDataViewItem();

        child->SetParent(node->GetParent());
        where = std::find(node->GetParent()->GetChildren().begin(), node->GetParent()->GetChildren().end(), node);
        if ( where == node->GetParent()->GetChildren().end() ) {
            node->GetParent()->GetChildren().push_back( child );

        } else {
            node->GetParent()->GetChildren().insert(where, child);

        }
    }

    return wxDataViewItem(child);
}