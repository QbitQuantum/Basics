///////////////////////////////////////////////////////////////////////////////
// Creates UI for the field variable specified.
// 
void ReflectStlSetInterpreter::InterpretField( const Reflect::Field* field, const std::vector<Reflect::Object*>& instances, Container* parent )
{
    if ( field->m_Flags & Reflect::FieldFlags::Hide )
    {
        return;
    }

    // create the container
    ContainerPtr container = CreateControl< Container >();
    parent->AddChild( container );

    tstring temp;
    field->GetProperty( TXT( "UIName" ), temp );
    if ( temp.empty() )
    {
        bool converted = Helium::ConvertString( field->m_Name, temp );
        HELIUM_ASSERT( converted );
    }

    container->a_Name.Set( temp );

    // create the data objects
    std::vector< Reflect::Object* >::const_iterator itr = instances.begin();
    std::vector< Reflect::Object* >::const_iterator end = instances.end();
    for ( ; itr != end; ++itr )
    {
        Reflect::DataPtr ser = Reflect::AssertCast< Reflect::Data >( Reflect::Registry::GetInstance()->CreateInstance( field->m_DataClass ) );
        uintptr_t fieldAddress = ( uintptr_t )( *itr ) + field->m_Offset;
        ser->ConnectData( ( void* )fieldAddress );
        m_Datas.push_back( ser );
    }

    // create the list
    ListPtr list = CreateControl< List >();
    list->a_HelpText.Set( field->GetProperty( TXT( "HelpText" ) ) );
    container->AddChild( list );

    // bind the ui to the serialiers
    list->Bind( new MultiStringFormatter< Reflect::Data >( (std::vector<Reflect::Data*>&)m_Datas ) );

    // create the buttons if we are not read only
    if ( !( field->m_Flags & Reflect::FieldFlags::ReadOnly ) )
    {
        ContainerPtr buttonContainer = CreateControl< Container >();
        container->AddChild( buttonContainer );

        ButtonPtr buttonAdd = CreateControl< Button >();
        buttonContainer->AddChild( buttonAdd );
        buttonAdd->a_Label.Set( TXT( "Add" ) );
        buttonAdd->a_HelpText.Set( TXT( "Add an item to the list." ) );
        buttonAdd->ButtonClickedEvent().Add( ButtonClickedSignature::Delegate ( this, &ReflectStlSetInterpreter::OnAdd ) );
        buttonAdd->SetClientData( new ClientData( list ) );

        ButtonPtr buttonRemove = CreateControl< Button >();
        buttonContainer->AddChild( buttonRemove );
        buttonRemove->a_Label.Set( TXT( "Remove" ) );
        buttonRemove->a_HelpText.Set( TXT( "Remove the selected item(s) from the list." ) );
        buttonRemove->ButtonClickedEvent().Add( ButtonClickedSignature::Delegate ( this, &ReflectStlSetInterpreter::OnRemove ) );
        buttonRemove->SetClientData( new ClientData( list ) );
    }

    // for now let's just disable this container if there is more than one item selected. I'm not sure if it will behave properly in this case.
    if ( instances.size() > 1 )
    {
        container->a_IsEnabled.Set( false );
    }
}