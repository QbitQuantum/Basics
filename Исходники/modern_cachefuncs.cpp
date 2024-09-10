void CSmileyString::AddListeningToIcon(ClcData *dat, wchar_t *szText)
{
	iMaxSmileyHeight = 0;
	DestroySmileyList();

	if (szText == nullptr)
		return;

	int text_size = (int)mir_wstrlen(szText);

	plText = List_Create(0, 1);

	// Add Icon
	{
		ClcContactTextPiece *piece = (ClcContactTextPiece *)mir_alloc(sizeof(ClcContactTextPiece));
		piece->type = TEXT_PIECE_TYPE_SMILEY;
		piece->len = 0;
		piece->smiley = g_hListeningToIcon;
		piece->smiley_width = 16;
		piece->smiley_height = 16;

		ICONINFO icon;
		if (GetIconInfo(piece->smiley, &icon)) {
			BITMAP bm;
			if (GetObject(icon.hbmColor, sizeof(BITMAP), &bm)) {
				piece->smiley_width = bm.bmWidth;
				piece->smiley_height = bm.bmHeight;
			}

			DeleteObject(icon.hbmMask);
			DeleteObject(icon.hbmColor);
		}

		dat->text_smiley_height = max(piece->smiley_height, dat->text_smiley_height);
		iMaxSmileyHeight = max(piece->smiley_height, iMaxSmileyHeight);

		List_Insert(plText, piece, plText->realCount);
	}

	// Add text
	{
		ClcContactTextPiece *piece = (ClcContactTextPiece *)mir_alloc(sizeof(ClcContactTextPiece));
		piece->type = TEXT_PIECE_TYPE_TEXT;
		piece->start_pos = 0;
		piece->len = text_size;
		List_Insert(plText, piece, plText->realCount);
	}
}