void Dlg_MemBookmark::ExportJSON()
{
	if ( g_pCurrentGameData->GetGameID() == 0 )
	{
		MessageBox( nullptr, _T("ROM not loaded: please load a ROM first!"), _T("Error!"), MB_OK );
		return;
	}

	if ( m_vBookmarks.size() == 0)
	{
		MessageBox( nullptr, _T("No bookmarks to save: please create a bookmark before attempting to save."), _T("Error!"), MB_OK );
		return;
	}

	std::string defaultDir = RA_DIR_BOOKMARKS;
	defaultDir.erase ( 0, 2 ); // Removes the characters (".\\")
	defaultDir = g_sHomeDir + defaultDir;

	IFileSaveDialog* pDlg = nullptr;
	HRESULT hr = CoCreateInstance( CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, reinterpret_cast<void**>( &pDlg ) );
	if ( hr == S_OK )
	{
		hr = pDlg->SetFileTypes( ARRAYSIZE( c_rgFileTypes ), c_rgFileTypes );
		if ( hr == S_OK )
		{
			char defaultFileName[ 512 ];
			sprintf_s ( defaultFileName, 512, "%s-Bookmarks.txt", std::to_string( g_pCurrentGameData->GetGameID() ).c_str() );
			hr = pDlg->SetFileName( Widen( defaultFileName ).c_str() );
			if ( hr == S_OK )
			{
				PIDLIST_ABSOLUTE pidl;
				hr = SHParseDisplayName( Widen( defaultDir ).c_str(), NULL, &pidl, SFGAO_FOLDER, 0 );
				if ( hr == S_OK )
				{
					IShellItem* pItem = nullptr;
					SHCreateShellItem( NULL, NULL, pidl, &pItem );
					hr = pDlg->SetDefaultFolder( pItem );
					if ( hr == S_OK )
					{
						pDlg->SetDefaultExtension( L"txt" );
						hr = pDlg->Show( nullptr );
						if ( hr == S_OK )
						{

							hr = pDlg->GetResult( &pItem );
							if ( hr == S_OK )
							{
								LPWSTR pStr = nullptr;
								hr = pItem->GetDisplayName( SIGDN_FILESYSPATH, &pStr );
								if ( hr == S_OK )
								{
									Document doc;
									Document::AllocatorType& allocator = doc.GetAllocator();
									doc.SetObject();

									Value bookmarks( kArrayType );
									for ( MemBookmark* bookmark : m_vBookmarks )
									{
										Value item( kObjectType );
										char buffer[ 256 ];
										sprintf_s( buffer, Narrow( bookmark->Description() ).c_str(), sizeof( buffer ) );
										Value s( buffer, allocator );

										item.AddMember( "Description", s, allocator );
										item.AddMember( "Address", bookmark->Address(), allocator );
										item.AddMember( "Type", bookmark->Type(), allocator );
										item.AddMember( "Decimal", bookmark->Decimal(), allocator );
										bookmarks.PushBack( item, allocator );
									}
									doc.AddMember( "Bookmarks", bookmarks, allocator );

									_WriteBufferToFile( Narrow( pStr ), doc );
								}

								pItem->Release();
								ILFree( pidl );
							}
						}
					}
				}
			}
		}
		pDlg->Release();
	}
}