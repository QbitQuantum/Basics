/// @copydoc Serializer::Serialize()
bool BinarySerializer::Serialize( GameObject* pObject )
{
    HELIUM_ASSERT( pObject );

    BeginSerialize( true );

    // Serialize the object type reference.
    const GameObjectType* pType = pObject->GetGameObjectType();
    HELIUM_ASSERT( pType );
    uint32_t typeIndex = ResolveTypeDependency( pType->GetName() );
    HELIUM_ASSERT( IsValid( typeIndex ) );
    m_pPropertyStream->Write( &typeIndex, sizeof( typeIndex ), 1 );

    // Serialize the object template.
    uint32_t templateIndex;
    SetInvalid( templateIndex );

    if( !pObject->IsDefaultTemplate() )
    {
        GameObject* pTemplate = Reflect::AssertCast< GameObject >( pObject->GetTemplate() );
        HELIUM_ASSERT( pTemplate );
        templateIndex = ResolveObjectDependency( pTemplate->GetPath() );
        HELIUM_ASSERT( IsValid( templateIndex ) );
    }

    m_pPropertyStream->Write( &templateIndex, sizeof( templateIndex ), 1 );

    // Serialize the object owner.
    uint32_t ownerIndex;
    SetInvalid( ownerIndex );

    GameObject* pOwner = pObject->GetOwner();
    if( pOwner )
    {
        ownerIndex = ResolveObjectDependency( pOwner->GetPath() );
        HELIUM_ASSERT( IsValid( ownerIndex ) );
    }

    m_pPropertyStream->Write( &ownerIndex, sizeof( ownerIndex ), 1 );

    // Serialize the object properties.
    pObject->Serialize( *this );

    EndSerialize();

    return true;
}