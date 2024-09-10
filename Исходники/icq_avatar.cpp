// handle Owner's avatar hash changes
void CIcqProto::handleAvatarOwnerHash(WORD wItemID, BYTE bFlags, BYTE *pData, BYTE nDataLen)
{
	if ((nDataLen >= 0x14) && m_bAvatarsEnabled)
	{
		switch (bFlags)
		{
		case 1: // our avatar is on the server
			{
				setSettingBlob(NULL, "AvatarHash", pData, 0x14); /// TODO: properly handle multiple avatar items (more formats)

				setUserInfo();
				// here we need to find a file, check its hash, if invalid get avatar from server
				TCHAR *file = GetOwnAvatarFileName();
				if (!file)
				{ // we have no avatar file, download from server
					TCHAR szFile[MAX_PATH * 2 + 4];
#ifdef _DEBUG
					debugLogA("We have no avatar, requesting from server.");
#endif
					GetAvatarFileName(0, NULL, szFile, MAX_PATH * 2);
					GetAvatarData(NULL, m_dwLocalUIN, NULL, pData, 0x14, szFile);
				}
				else
				{ // we know avatar filename
					BYTE *hash = calcMD5HashOfFile(file);

					if (!hash)
					{ // hash could not be calculated - probably missing file, get avatar from server
						TCHAR szFile[MAX_PATH * 2 + 4];
#ifdef _DEBUG
						debugLogA("We have no avatar, requesting from server.");
#endif
						GetAvatarFileName(0, NULL, szFile, MAX_PATH * 2);
						GetAvatarData(NULL, m_dwLocalUIN, NULL, pData, 0x14, szFile);
					} // check if we had set any avatar if yes set our, if not download from server
					else if (memcmp(hash, pData + 4, 0x10))
					{ // we have different avatar, sync that
						if (m_bSsiEnabled && getByte("ForceOurAvatar", 1))
						{ // we want our avatar, update hash
							DWORD dwPaFormat = ::ProtoGetAvatarFileFormat(file);
							BYTE *pHash = (BYTE*)_alloca(0x14);

							debugLogA("Our avatar is different, setting our new hash.");

							pHash[0] = 0;
							pHash[1] = dwPaFormat == PA_FORMAT_XML ? AVATAR_HASH_FLASH : AVATAR_HASH_STATIC;
							pHash[2] = 1; // state of the hash
							pHash[3] = 0x10; // len of the hash
							memcpy(pHash + 4, hash, 0x10);
							updateServAvatarHash(pHash, 0x14);
						}
						else
						{ // get avatar from server
							TCHAR tszFile[MAX_PATH * 2 + 4];
#ifdef _DEBUG
							debugLogA("We have different avatar, requesting new from server.");
#endif
							GetAvatarFileName(0, NULL, tszFile, MAX_PATH * 2);
							GetAvatarData(NULL, m_dwLocalUIN, NULL, pData, 0x14, tszFile);
						}
					}
					SAFE_FREE((void**)&hash);
					SAFE_FREE(&file);
				}
				break;
			}
		case 0x41: // request to upload avatar data
		case 0x81:
			{ // request to re-upload avatar data
				if (!m_bSsiEnabled) break; // we could not change serv-list if it is disabled...

				TCHAR *file = GetOwnAvatarFileName();
				if (!file)
				{ // we have no file to upload, remove hash from server
					debugLogA("We do not have avatar, removing hash.");
					SetMyAvatar(0, 0);
					break;
				}
				DWORD dwPaFormat = ::ProtoGetAvatarFileFormat(file);
				BYTE *hash = calcMD5HashOfFile(file);

				if (!hash)
				{ // the hash could not be calculated, remove from server
					debugLogA("We could not obtain hash, removing hash.");
					SetMyAvatar(0, 0);
				}
				else if (!memcmp(hash, pData + 4, 0x10))
				{ // we have the right file
					HANDLE hFile = NULL, hMap = NULL;
					BYTE *ppMap = NULL;
					long cbFileSize = 0;

					debugLogA("Uploading our avatar data.");

					if ((hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL )) != INVALID_HANDLE_VALUE)
						if ((hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL)) != NULL)
							if ((ppMap = (BYTE*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0)) != NULL)
								cbFileSize = GetFileSize(hFile, NULL);

					if (cbFileSize != 0)
					{
						SetAvatarData(NULL, (WORD)(dwPaFormat == PA_FORMAT_XML ? AVATAR_HASH_FLASH : AVATAR_HASH_STATIC), ppMap, cbFileSize);
					}

					if (ppMap != NULL) UnmapViewOfFile(ppMap);
					if (hMap  != NULL) CloseHandle(hMap);
					if (hFile != NULL) CloseHandle(hFile);
					SAFE_FREE((void**)&hash);
				}
				else
				{
					BYTE *pHash = (BYTE*)_alloca(0x14);

					debugLogA("Our file is different, set our new hash.");

					pHash[0] = 0;
					pHash[1] = dwPaFormat == PA_FORMAT_XML ? AVATAR_HASH_FLASH : AVATAR_HASH_STATIC;
					pHash[2] = 1; // state of the hash
					pHash[3] = 0x10; // len of the hash
					memcpy(pHash + 4, hash, 0x10);
					updateServAvatarHash(pHash, 0x14);

					SAFE_FREE((void**)&hash);
				}

				SAFE_FREE(&file);
				break;
			}
		default:
			debugLogA("Received UNKNOWN Avatar Status.");
		}
	}
}