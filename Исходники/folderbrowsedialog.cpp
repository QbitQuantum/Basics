	bool show()
	{
		#ifdef WIN32

		CL_String16 title16 = CL_StringHelp::utf8_to_ucs2(title);
		CL_String16 initial_directory16 = CL_StringHelp::utf8_to_ucs2(initial_directory);

		#ifndef __MINGW32__
		
		if(is_vista_or_later())
		{
			HRESULT result;
			CL_ComPtr<IFileOpenDialog> open_dialog;

			result = CoCreateInstance(__uuidof(FileOpenDialog), NULL, CLSCTX_ALL, __uuidof(open_dialog),  reinterpret_cast<void**>(open_dialog.output_variable()));
			throw_if_failed(result, "CoCreateInstance(FileOpenDialog) failed");

			result = open_dialog->SetTitle(title16.c_str());
			throw_if_failed(result, "IFileOpenDialog.SetTitle failed");

			result = open_dialog->SetOptions(FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST);
			throw_if_failed(result, "IFileOpenDialog.SetOptions((FOS_PICKFOLDERS) failed");

			if(initial_directory16.length() > 0)
			{
				LPITEMIDLIST item_id_list = NULL;
				SFGAOF flags = 0;
				result = SHParseDisplayName(initial_directory16.c_str(), NULL, &item_id_list, SFGAO_FILESYSTEM, &flags);
				throw_if_failed(result, "SHParseDisplayName failed");

				CL_ComPtr<IShellItem> folder_item;
				result = SHCreateShellItem(NULL, NULL, item_id_list, folder_item.output_variable());
				ILFree(item_id_list);
				throw_if_failed(result, "SHCreateItemFromParsingName failed");

				/* This code requires Windows Vista or newer:
				CL_ComPtr<IShellItem> folder_item;
				result = SHCreateItemFromParsingName(initial_directory16.c_str(), NULL, IID_PPV_ARGS(folder_item.output_variable()));
				throw_if_failed(result, "SHCreateItemFromParsingName failed");
				*/

				if(!folder_item.is_null())
				{
					result = open_dialog->SetFolder(folder_item);
					throw_if_failed(result, "IFileOpenDialog.SetFolder failed");
				}
			}

			if(owner)
				result = open_dialog->Show(owner->get_display_window().get_hwnd());
			else
				result = open_dialog->Show(0);

			if(SUCCEEDED(result))
			{
				CL_ComPtr<IShellItem> chosen_folder;
				result = open_dialog->GetResult(chosen_folder.output_variable());
				throw_if_failed(result, "IFileOpenDialog.GetResult failed");

				WCHAR *buffer = 0;
				result = chosen_folder->GetDisplayName(SIGDN_FILESYSPATH, &buffer);
				throw_if_failed(result, "IShellItem.GetDisplayName failed");

				CL_String16 output_directory16;
				try
				{
					output_directory16 = buffer;
				}
				catch (...)
				{
					CoTaskMemFree(buffer);
					throw;
				}

				CoTaskMemFree(buffer);
				selected_path = CL_StringHelp::ucs2_to_utf8(output_directory16);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		#endif
		{
			BROWSEINFO bi;
			ZeroMemory(&bi, sizeof(bi));
		
			CL_String16::char_type path_buffer[FILENAME_MAX] = { 0 };

			WCHAR Buffer[MAX_PATH];
			memset(Buffer, 0, sizeof(WCHAR) * MAX_PATH);

			if(owner)
				bi.hwndOwner = owner->get_display_window().get_hwnd();
			else
				bi.hwndOwner = 0;

			bi.pszDisplayName = Buffer;
			bi.lpszTitle = title16.c_str();
			bi.ulFlags = BIF_EDITBOX | BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_SHAREABLE;

			LPCITEMIDLIST pFolder = SHBrowseForFolder(&bi);
			if (pFolder == NULL) 
				return false;

			if (!SHGetPathFromIDList(pFolder, path_buffer)) 
				throw CL_Exception("Bad path for Browse Folder Dialog");

			selected_path = CL_StringHelp::ucs2_to_utf8(path_buffer);

			return true;
		}
#else
		bool success = false;
		return success;
#endif
	}