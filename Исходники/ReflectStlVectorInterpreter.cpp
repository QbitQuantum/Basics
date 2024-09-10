void ReflectStlVectorInterpreter::OnMoveDown( const ButtonClickedArgs& args )
{
    Reflect::ObjectPtr clientData = args.m_Control->GetClientData();
    if ( clientData.ReferencesObject() && clientData->IsClass( Reflect::GetClass<ClientData>() ) )
    {
        ClientData* data = static_cast< ClientData* >( clientData.Ptr() );
        List* list = static_cast< List* >( data->GetControl() );
        std::set< size_t > selectedItemIndices = list->a_SelectedItemIndices.Get();
        if ( !selectedItemIndices.empty() )
        {
            // for each array in the selection set (the objects the array data is connected to)
            std::vector< DataPtr >::const_iterator serItr = m_Datas.begin();
            std::vector< DataPtr >::const_iterator serEnd = m_Datas.end();
            for ( ; serItr != serEnd; ++serItr )
            {
                Reflect::StlVectorData* arrayData = Reflect::AssertCast<Reflect::StlVectorData>(*serItr);

                arrayData->MoveDown( selectedItemIndices );
            }

            list->a_SelectedItemIndices.Set( selectedItemIndices );

            args.m_Control->GetCanvas()->Read();
        }
    }
}