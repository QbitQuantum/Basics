SendProp SendPropInt(
	char *pVarName,
	int offset,
	int sizeofVar,
	int nBits,
	int flags,
	SendVarProxyFn varProxy
	)
{
	SendProp ret;

	if ( !varProxy )
	{
		if ( sizeofVar == 1 )
		{
			varProxy = SendProxy_Int8ToInt32;
		}
		else if ( sizeofVar == 2 )
		{
			varProxy = SendProxy_Int16ToInt32;
		}
		else if ( sizeofVar == 4 )
		{
			varProxy = SendProxy_Int32ToInt32;
		}
		else
		{
			Assert(!"SendPropInt var has invalid size");
			varProxy = SendProxy_Int8ToInt32;	// safest one...
		}
	}

	// Figure out # of bits if the want us to.
	if ( nBits <= 0 )
	{
		Assert( sizeofVar == 1 || sizeofVar == 2 || sizeofVar == 4 );
		nBits = sizeofVar * 8;
	}

	ret.m_Type = DPT_Int;
	ret.m_pVarName = pVarName;
	ret.SetOffset( offset );
	ret.m_nBits = nBits;
	ret.SetFlags( flags );

	// Use UInt proxies if they want unsigned data. This isn't necessary to encode
	// the values correctly, but it lets us check the ranges of the data to make sure
	// they're valid.
	ret.SetProxyFn( varProxy );
	if( ret.GetFlags() & SPROP_UNSIGNED )
	{
		if( varProxy == SendProxy_Int8ToInt32 )
			ret.SetProxyFn( SendProxy_UInt8ToInt32 );
		
		else if( varProxy == SendProxy_Int16ToInt32 )
			ret.SetProxyFn( SendProxy_UInt16ToInt32 );

		else if( varProxy == SendProxy_Int32ToInt32 )
			ret.SetProxyFn( SendProxy_UInt32ToInt32 );
	}

	return ret;
}