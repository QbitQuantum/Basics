			HRESULT __stdcall Stat(STATSTG* stat, DWORD grfStatFlag)
			{
				if(!stat)
					return E_INVALIDARG;
				switch(grfStatFlag)
				{
				case STATFLAG_DEFAULT:
					str::clear(stat->pwcsName);
					break;
				default:
					stat->pwcsName = NULL;
					break;
				}
				FILETIME time;
				CoFileTimeNow(&time);
				stat->type = STGTY_STREAM;
				stat->cbSize.QuadPart = GetSize();
				stat->grfMode = GetAccessMode();
				stat->grfLocksSupported = 0;
				stat->clsid = GUID_NULL;
				stat->mtime = stat->ctime = stat->atime = time;
				return S_OK;
			}