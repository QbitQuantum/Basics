BOOL LLAsyncHostByName::cancelPendingRequest()
{	
	if( mCallback )
	{
		mCallback( FALSE, mDomainName, 0, mUserdata );
	}
	mUserdata = NULL;
	mCallback = NULL;

	if( mRequestHandle )
	{
		S32 ret = WSACancelAsyncRequest( mRequestHandle );
		if( SOCKET_ERROR == ret )
		{
			llwarns << "LLAsyncHostByName::cancelPendingRequest() failed: " << WSAGetLastError() << llendl;
			return FALSE;
		}
		memset(mOutputBuffer, 0, sizeof( mOutputBuffer ) );
		mRequestHandle = 0;
		return TRUE;
	}

	return FALSE;
}