Unique::Unique(void)
    :_id( GUID() )
{
    CoCreateGuid( &_id );

    _registry.insert(this);
}