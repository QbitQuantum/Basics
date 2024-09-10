/** \brief Message Handling Callback.
 * This handles all callbacks to the remote view window.
 */
void RemoteIconView::HandleMessage( Message* pcMessage )
{
	switch( pcMessage->GetCode() )
	{
		case M_REMOTE_DIRLISTING:
		{
			if( !m_bUpdatePending ) {
				DEBUG( "RemoteIconView: Got REMOTE_DIRLISTING while no dirlisting is pending!\n" );
				return;
			}
			
			String zPath;
			if( pcMessage->FindString( "path", &zPath ) != 0 ) {
				DEBUG( "RemoteIconView: Got REMOTE_DIRLISTING without path!\n" );
				return;
			}
			if( zPath != m_zPath ) {
				DEBUG( "RemoteIconView: Got REMOTE_DIRLISTING with wrong path %s! Expecting %s.\n", zPath.c_str(), m_zPath.c_str() );
				return;
			}
			
			std::vector< RemoteNode >* pacNodes;
			/* The Server creates an array of RemoteNodes and passes us the pointer. We should delete it when done. */
			if( pcMessage->FindPointer( "list", (void**)&pacNodes ) ) {
				DEBUG( "RemoteIconView: Got REMOTE_DIRLISTING without pointer to data!\n" );
				return;
			}
			
			bool bInitial;
			if( pcMessage->FindBool( "initial", &bInitial ) != 0 ) bInitial = false;
			
			bool bFinal;
			if( pcMessage->FindBool( "final", &bFinal ) != 0 ) bFinal = false;
			
			SetContents( pacNodes, bInitial, bFinal );
			if( pacNodes ) delete( pacNodes );
		
			break;
		}
		/* Messages from the context menu */
		case M_REMOTE_RENAME:
		{
			/* Check that only one icon is selected & get the selected icon */
			uint nSelectedIcon = -1;
			uint nNumSelected = 0;
			for( uint i = 0; i < GetIconCount(); i++ ) {
				if( GetIconSelected( i ) ) {
					nSelectedIcon = i;
					nNumSelected++;
				}
			}
			if( nNumSelected != 1 ) {
				DEBUG( "RemoteView: Got M_REMOTE_RENAME while %i icons are selected!\n", nNumSelected );
				break;
			}
			RemoteIconData* pcData = (RemoteIconData*)GetIconData( nSelectedIcon );

			/* Display rename dialog */
			Window* pcDialog = new RenameRequester( pcData->m_cNode.m_zPath, this );
			pcDialog->CenterInWindow( GetWindow() );
			pcDialog->Show();
			pcDialog->MakeFocus( true );
			break;
		}
		case M_REMOTE_DELETE:
		{
			/* Save a list of the selected files */
			std::vector< RemoteNode >* pacDeleteList = new std::vector< RemoteNode >;
			for( uint i = 0; i < GetIconCount(); i++ ) {
				if( GetIconSelected( i ) ) {
					pacDeleteList->push_back( ((RemoteIconData*)GetIconData( i ))->m_cNode );
				}
			}
			if( pacDeleteList->size() == 0 ) {
				DEBUG( "RemoteView: Got M_REMOTE_DELETE while no icons are selected!\n" );
				delete( pacDeleteList );
				break;
			}

			/* Display confirmation dialog */
			Window* pcDialog = new DeleteConfirmDialog( pacDeleteList, this );
			pcDialog->CenterInWindow( GetWindow() );
			pcDialog->Show();
			pcDialog->MakeFocus( true );
			break;			
		}
		case M_REMOTE_MKDIR:
		{
			Window* pcDialog = new MkDirRequester( m_zPath, this );
			pcDialog->CenterInWindow( GetWindow() );
			pcDialog->Show();
			pcDialog->MakeFocus( true );
			break;
		}
		case M_DELETE_CONFIRMED:
		{
			std::vector< RemoteNode >* pacDeleteList = NULL;
			pcMessage->FindPointer( "files", (void**)&pacDeleteList );
			if( m_pcServer == NULL ) {	/* Just in case */
				DEBUG( "RemoteView: Got M_DELETE_CONFIRMED while m_pcServer == NULL!\n" );
				delete( pacDeleteList );
				break;
			}
			while( !pacDeleteList->empty() ) {
				RemoteNode* pcNode = &pacDeleteList->back();
				if( pcNode->m_bIsDir ) {
//					DEBUG( "RemoteView: calling RemoveRemoteDir( %s )\n", pcNode->m_zPath.c_str() );
					m_pcServer->RemoveRemoteDir( pcNode->m_zPath );
				} else {
//					DEBUG( "RemoteView: calling DeleteRemote( '%s' )\n", pcNode->m_zPath.c_str() );
					m_pcServer->DeleteRemoteFile( pcNode->m_zPath );
				}
				pacDeleteList->pop_back();
			}
			delete( pacDeleteList );
			Update();
			break;
		}
		case M_MKDIR_CONFIRMED:
		{
			String zPath;
			pcMessage->FindString( "remotepath", &zPath );
			if( m_pcServer == NULL ) {
				DEBUG( "RemoteView: Got M_MKDIR_CONFIRMED while m_pcServer == NULL!\n" );
				break;
			}
			m_pcServer->CreateRemoteDir( zPath );
			Update();
			break;
		}
		case M_RENAME_CONFIRMED:
		{
			String zOldPath, zNewPath;
			pcMessage->FindString( "old_path", &zOldPath );
			pcMessage->FindString( "new_path", &zNewPath );
			if( m_pcServer == NULL ) {
				DEBUG( "RemoteView: Got M_RENAME_CONFIRMED while m_pcServer == NULL!\n" );
				break;
			}
			m_pcServer->MoveRemote( zOldPath, zNewPath );
			Update();
			break;
		}
		default:
		{
			IconView::HandleMessage( pcMessage );
		}
	}
}