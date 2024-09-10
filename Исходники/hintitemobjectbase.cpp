//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *object - 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CHintItemObjectBase::IsObjectOfType( C_BaseEntity *object )
{
	if ( !stricmp( GetObjectType(), "Resource Zone" ) )
	{
		return dynamic_cast< C_ResourceZone *>( object ) ? true : false;
	}
	else if ( !stricmp( GetObjectType(), "Resource Pump" ) )
	{
		return dynamic_cast< C_ObjectResourcePump * >( object) ? true : false;
	}
	else if ( !stricmp( GetObjectType(), "BaseObject" ) )
	{
		return dynamic_cast< C_BaseObject * >( object) ? true : false;
	}
	
	return false;
}