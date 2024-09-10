		void Recreate(int res, bool bold, bool italic, bool underline, const core::stringw& fontName)
		{
			if (font)
				DeleteFont(font);
			font = CreateFontW(
				res,
				0, 0, 0,
				bold ? FW_BOLD : 0,
				italic,
				underline,
				0,
				ANSI_CHARSET | ARABIC_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				fontName.c_str());
			fontDirty = false;
		}