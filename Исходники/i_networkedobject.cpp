//------------------------------------------------------------------
void	INetworkedObject::Update( uint dt )
{
	for ( size_t i = 0; i < _fields.size(); ++i )
	{
		SField& field( _fields[i] );
		if ( MemCmp( field.data, field.prevValue, field.size ) != 0 )
		{
			i = i;
		}
	}
}