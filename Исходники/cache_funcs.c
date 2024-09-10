void Cache_GetAvatar(struct ClcData *dat, struct ClcContact *contact)
{
	if (dat->use_avatar_service)
	{
		if (dat->avatars_show && !DBGetContactSettingByte(contact->hContact, "CList", "HideContactAvatar", 0))
		{
			contact->avatar_data = (struct avatarCacheEntry *)CallService(MS_AV_GETAVATARBITMAP, (WPARAM)contact->hContact, 0);

			if (contact->avatar_data == NULL || contact->avatar_data->cbSize != sizeof(struct avatarCacheEntry) 
				|| contact->avatar_data->dwFlags == AVS_BITMAP_EXPIRED)
			{
				contact->avatar_data = NULL;
			}

			if (contact->avatar_data != NULL)
				contact->avatar_data->t_lastAccess = time(NULL);
		}
		else
		{
			contact->avatar_data = NULL;
		}
	}
	else
	{
		int old_pos = contact->avatar_pos;

		contact->avatar_pos = AVATAR_POS_DONT_HAVE;
		if (dat->avatars_show && !DBGetContactSettingByte(contact->hContact, "CList", "HideContactAvatar", 0))
		{
			DBVARIANT dbv;
			if (!DBGetContactSetting(contact->hContact, "ContactPhoto", "File", &dbv) && (dbv.type == DBVT_ASCIIZ || dbv.type == DBVT_UTF8))
			{
				HBITMAP hBmp = (HBITMAP) CallService(MS_UTILS_LOADBITMAP, 0, (LPARAM)dbv.pszVal);
				if (hBmp != NULL)
				{
					// Make bounds
					BITMAP bm;
					if (GetObject(hBmp,sizeof(BITMAP),&bm))
					{
						// Create data...
						HDC hdc; 
						HBITMAP hDrawBmp,oldBmp;

						// Make bounds -> keep aspect radio
						LONG width_clip;
						LONG height_clip;
						RECT rc = {0};

						// Clipping width and height
						width_clip = dat->avatars_size;
						height_clip = dat->avatars_size;

						if (height_clip * bm.bmWidth / bm.bmHeight <= width_clip)
						{
							width_clip = height_clip * bm.bmWidth / bm.bmHeight;
						}
						else
						{
							height_clip = width_clip * bm.bmHeight / bm.bmWidth;					
						}

						// Create objs
						hdc = CreateCompatibleDC(dat->avatar_cache.hdc); 
						hDrawBmp = CreateBitmap32(width_clip, height_clip);
						oldBmp=SelectObject(hdc, hDrawBmp);
						SetBkMode(hdc,TRANSPARENT);
						{
							POINT org;
							GetBrushOrgEx(hdc, &org);
							SetStretchBltMode(hdc, HALFTONE);
							SetBrushOrgEx(hdc, org.x, org.y, NULL);
						}

						rc.right = width_clip - 1;
						rc.bottom = height_clip - 1;

						// Draw bitmap             8//8
						{
							HDC dcMem = CreateCompatibleDC(hdc);
							HBITMAP obmp=SelectObject(dcMem, hBmp);						
							StretchBlt(hdc, 0, 0, width_clip, height_clip,dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
							SelectObject(dcMem,obmp);
							DeleteDC(dcMem);
						}
            {
              RECT rtr={0};
              rtr.right=width_clip+1;
              rtr.bottom=height_clip+1;
              FillRect255Alpha(hdc,&rtr);
            }

            hDrawBmp = GetCurrentObject(hdc, OBJ_BITMAP);
			SelectObject(hdc,oldBmp);
            DeleteDC(hdc);

						// Add to list
						if (old_pos >= 0)
						{
							ImageArray_ChangeImage(&dat->avatar_cache, hDrawBmp, old_pos);
							contact->avatar_pos = old_pos;
						}
						else
						{
							contact->avatar_pos = ImageArray_AddImage(&dat->avatar_cache, hDrawBmp, -1);
						}

						DeleteObject(hDrawBmp);
					} // if (GetObject(hBmp,sizeof(BITMAP),&bm))
					DeleteObject(hBmp);
				} //if (hBmp != NULL)
			}
			DBFreeVariant(&dbv);
		}

		// Remove avatar if needed
		if (old_pos >= 0 && contact->avatar_pos == AVATAR_POS_DONT_HAVE)
		{
			ImageArray_RemoveImage(&dat->avatar_cache, old_pos);

			// Update all itens
			ExecuteOnAllContacts(dat, ReduceAvatarPosition, (void *)&old_pos);
		}
	}
}