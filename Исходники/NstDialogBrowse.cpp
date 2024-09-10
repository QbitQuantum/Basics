		const Path Browser::SelectDirectory()
		{
			Path path;
			path.Reserve( MAX_PATH*2 );

			Object::Pod<BROWSEINFO> bi;

			bi.hwndOwner      = Application::Instance::GetActiveWindow();
			bi.pszDisplayName = path.Ptr();
			bi.ulFlags        = BIF_RETURNONLYFSDIRS;

			if (LPITEMIDLIST const idl = ::SHBrowseForFolder( &bi ))
			{
				if (::SHGetPathFromIDList( idl, path.Ptr() ) && path.Validate())
					path.MakePretty( true );
				else
					path.Clear();

				IMalloc* pMalloc;

				if (SUCCEEDED(::SHGetMalloc( &pMalloc )))
				{
					pMalloc->Free( idl );
					pMalloc->Release();
				}
			}
			else
			{
				path.Clear();
			}

			return path;
		}