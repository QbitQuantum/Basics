SEARCH_RESULT SCH_FIND_COLLECTOR::Inspect( EDA_ITEM* aItem, const void* aTestData )
{
    wxPoint position;

    if( aItem->Matches( m_findReplaceData, m_sheetPath, &position ) )
    {
        if( aItem->Type() == LIB_PIN_T )
        {
            wxCHECK_MSG( aTestData && ( (EDA_ITEM*) aTestData )->Type() == SCH_COMPONENT_T,
                         SEARCH_CONTINUE, wxT( "Cannot inspect invalid data.  Bad programmer!" ) );

            // Pin positions are relative to their parent component's position and
            // orientation in the schematic.  The pin's position must be converted
            // schematic coordinates.
            SCH_COMPONENT* component = (SCH_COMPONENT*) aTestData;
            TRANSFORM transform = component->GetTransform();
            position.y = -position.y;
            position = transform.TransformCoordinate( position ) + component->GetPosition();
        }

        Append( aItem );
        m_data.push_back( SCH_FIND_COLLECTOR_DATA( position, m_sheetPath->PathHumanReadable(),
                                                   (SCH_ITEM*) aTestData ) );
    }

    return SEARCH_CONTINUE;
}