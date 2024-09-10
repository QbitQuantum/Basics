void CPluginUtils::AddMultipartParamL( RBuf& aBuf, const TDesC& aParam, TInt aValue )
	{
	TBuf<12> t;
	t.Format( _L("%d"), aValue );

	aBuf.ReAllocL( aBuf.Length() + KBoundary().Length() + aParam.Length() + t.Length() + 2 + 2 + 2 + 2 + 2 + 1 + KDisposition().Length() );
	aBuf.Append( _L("--") );
	aBuf.Append( KBoundary() );
	aBuf.Append( KCrLf );
	aBuf.Append( KDisposition() );
	aBuf.Append( aParam );
	aBuf.Append( _L("\"") );
	aBuf.Append( KCrLf );
	aBuf.Append( KCrLf );
	aBuf.Append( t );
	aBuf.Append( KCrLf );
	}