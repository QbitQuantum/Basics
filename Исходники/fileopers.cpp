bool OperCFThread::CopyLink( FS* srcFs, FSPath& srcPath, FSNode* srcNode, FS* destFs, FSPath& destPath, bool move )
{
	ASSERT( srcNode->st.IsLnk() );

	if ( IsSameFile( srcFs, srcPath, &( srcNode->st ), destFs, destPath ) )
	{
		RedMessage( _LT( "Can't copy link to itself:\n" ) , srcFs->Uri( srcPath ).GetUtf8() );
		return false;
	}

	int ret_err;

	while ( destFs->Symlink( destPath, srcNode->st.link, &ret_err, Info() ) && !skipNonRegular )
		switch ( RedMessage( _LT( "Can't create symbolic link:\n" ), destFs->Uri( destPath ).GetUtf8(), "to\n",
		                     srcNode->st.link.GetUtf8(),  bSkipSkipallCancel, destFs->StrError( ret_err ).GetUtf8() ) )
		{
			case CMD_CANCEL:
				return false;

			case CMD_SKIPALL:
				skipNonRegular = true;

			case CMD_SKIP:
				return true;
		}

	return !move || Unlink( srcFs, srcPath );
}