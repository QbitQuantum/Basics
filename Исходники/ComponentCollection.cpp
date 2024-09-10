void ComponentCollection::CopyTo(Reflect::Object* object)
{
    Base::CopyTo( object );

    ComponentCollection* collection = Reflect::SafeCast< ComponentCollection >( object );
    if ( collection )
    {
        // Remove all attributes, we're going to bring them over manually
        collection->Clear(); 

        // For each component in this component collection
        Reflect::Registry* registry = Reflect::Registry::GetInstance();
        M_Component::const_iterator attrItr = m_Components.begin();
        M_Component::const_iterator attrEnd = m_Components.end();
        for ( ; attrItr != attrEnd; ++attrItr )
        {
            // Create a new copy of the component and try to add it to the destination
            const ComponentPtr& attrib = attrItr->second;
            ComponentPtr destAttrib = Reflect::AssertCast< ComponentBase >( registry->CreateInstance( attrib->GetMetaClass() ) );
            if ( !CopyComponentTo( *collection, destAttrib, attrib ) )
            {
                // Component could not be added to the destination collection, check sibling classes
                for ( const Composite* sibling = attrib->GetMetaClass()->m_Base->m_FirstDerived; sibling; sibling = sibling->m_NextSibling )
                {
                    if ( sibling != attrib->GetMetaClass() )
                    {
                        destAttrib = Reflect::AssertCast< ComponentBase >( registry->CreateInstance( Reflect::ReflectionCast< const MetaClass >( sibling ) ) );
                        if ( destAttrib.ReferencesObject() )
                        {
                            if ( CopyComponentTo( *collection, destAttrib, attrib ) )
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}