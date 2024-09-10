// internal
bool asCModule::AreTypesEqual(const asCDataType &a, const asCDataType &b, asCArray<sObjectTypePair> &equals)
{
	if( !a.IsEqualExceptInterfaceType(b) )
		return false;

	asCObjectType *ai = a.GetObjectType();
	asCObjectType *bi = b.GetObjectType();

	if( ai && ai->IsInterface() )
	{
		// If the interface is in the equals list, then the pair must match the pair in the list
		bool found = false;
		unsigned int e;
		for( e = 0; e < equals.GetLength(); e++ )
		{
			if( equals[e].a == ai )
			{
				found = true;
				break;
			}
		}

		if( found )
		{
			// Do the pairs match?
			if( equals[e].b != bi )
				return false;
		}
		else
		{
			// Assume they are equal from now on
			sObjectTypePair pair = {ai, bi};
			equals.PushLast(pair);
		}
	}

	return true;
}