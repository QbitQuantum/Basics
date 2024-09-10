/*
========================
idSnapShot::WriteObject
========================
*/
void idSnapShot::WriteObject( idFile* file, int visIndex, objectState_t* newState, objectState_t* oldState, int& lastobjectNum )
{
	assert( newState != NULL || oldState != NULL );
	
	bool visChange		= false; // visibility changes will be signified with a 0xffff state size
	bool visSendState	= false; // the state is sent when an entity is no longer stale
	
	// Compute visibility changes
	// (we need to do this before writing out object id, because we may not need to write out the id if we early out)
	// (when we don't write out the id, we assume this is an "ack" when we deserialize the objects)
	if( newState != NULL && oldState != NULL )
	{
		// Check visibility
		assert( newState->objectNum == oldState->objectNum );
		
		if( visIndex > 0 )
		{
			bool oldVisible = ( oldState->visMask & ( 1 << visIndex ) ) != 0;
			bool newVisible = ( newState->visMask & ( 1 << visIndex ) ) != 0;
			
			// Force visible if we need to either create or destroy this object
			newVisible |= ( newState->buffer.Size() == 0 ) != ( oldState->buffer.Size() == 0 );
			
			if( !oldVisible && !newVisible )
			{
				// object is stale and ack'ed for this client, write nothing (see 'same object' below)
				return;
			}
			else if( oldVisible && !newVisible )
			{
				NET_VERBOSESNAPSHOT_PRINT( "object %d to client %d goes stale\n", newState->objectNum, visIndex );
				visChange = true;
				visSendState = false;
			}
			else if( !oldVisible && newVisible )
			{
				NET_VERBOSESNAPSHOT_PRINT( "object %d to client %d no longer stale\n", newState->objectNum, visIndex );
				visChange = true;
				visSendState = true;
			}
		}
		
		// Same object, write a delta (never early out during vis changes)
		if( !visChange && newState->buffer.Size() == oldState->buffer.Size() &&
				( ( newState->buffer.Ptr() == oldState->buffer.Ptr() ) || memcmp( newState->buffer.Ptr(), oldState->buffer.Ptr(), newState->buffer.Size() ) == 0 ) )
		{
			// same state, write nothing
			return;
		}
	}
	
	// Get the id of the object we are writing out
	uint16 objectNum;
	if( newState != NULL )
	{
		objectNum = newState->objectNum;
	}
	else if( oldState != NULL )
	{
		objectNum = oldState->objectNum;
	}
	else
	{
		objectNum = 0;
	}
	
	assert( objectNum == 0 || objectNum > lastobjectNum );
	
	// Write out object id (using delta)
	uint16 objectDelta = objectNum - lastobjectNum;
	file->WriteBig( objectDelta );
	lastobjectNum = objectNum;
	
	if( newState == NULL )
	{
		// Deleted, write 0 size
		assert( oldState != NULL );
		file->WriteBig<objectSize_t>( 0 );
	}
	else if( oldState == NULL )
	{
		// New object, write out full state
		assert( newState != NULL );
		// delta against an empty snap
		file->WriteBig( newState->buffer.Size() );
		file->Write( newState->buffer.Ptr(), newState->buffer.Size() );
	}
	else
	{
		// Compare to last object
		assert( newState != NULL && oldState != NULL );
		assert( newState->objectNum == oldState->objectNum );
		
		if( visChange )
		{
			// fake size indicates vis state change
			// NOTE: we may still send a real size and a state below, for 'no longer stale' transitions
			// TMP: send 0xFFFF for going stale and 0xFFFF - 1 for no longer stale
			file->WriteBig<objectSize_t>( visSendState ? SIZE_NOT_STALE : SIZE_STALE );
		}
		if( !visChange || visSendState )
		{
		
			objectSize_t compareSize = Min( newState->buffer.Size(), oldState->buffer.Size() );		// Get the number of bytes that overlap
			
			file->WriteBig( newState->buffer.Size() );										// Write new size
			
			// Compare bytes that overlap
			for( objectSize_t b = 0; b < compareSize; b++ )
			{
				file->WriteBig<byte>( ( 0xFF + 1 + newState->buffer[b] - oldState->buffer[b] ) & 0xFF );
			}
			
			// Write leftover
			if( newState->buffer.Size() > compareSize )
			{
				file->Write( newState->buffer.Ptr() + oldState->buffer.Size(), newState->buffer.Size() - compareSize );
			}
		}
	}
	
#ifdef SNAPSHOT_CHECKSUMS
	if( ( !visChange || visSendState ) && newState != NULL )
	{
		assert( newState->buffer.Size() > 0 );
		unsigned int checksum = MD5_BlockChecksum( newState->buffer.Ptr(), newState->buffer.Size() );
		file->WriteBig( checksum );
	}
#endif
}