int fontx_load(const char *path, fontx_t* fontx, int type, int wmargin, int hmargin, int bold)
{

	FILE *file = NULL;

	int ret = -1;
	long size = 0;

	fontx_hdr *fontx_header = NULL;

	if (!strcmp("rom0:KROM",path) || !strcmp("rom0:/KROM",path))
	{

		if (type == SINGLE_BYTE)
		{

			ret = fontx_load_single_krom(fontx);

		}
		else
		{

			ret = fontx_load_double_krom(fontx);

		}

		if (ret < 0)
		{

			printf("Error opening %s\n", path);
			return -1;

		}

	}

	else
	{

		file = fopen(path, "r");

		if (file == NULL)
		{

			printf("Error opening %s\n", path);
			return -1;

		}

		// get size of file
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);

		fontx->font = (char *)malloc(size);

		if (fontx->font == NULL)
		{

			printf("Error allocating %ld bytes of memory.\n", size);
			fclose(file);
			return -1;

		}

		fread(fontx->font, size, 1, file);

		fclose(file);

	}

	fontx_header = (fontx_hdr*)fontx->font;

	if (strncmp(fontx_header->id, "FONTX2", 6) != 0)
	{

		printf("Not FONTX2 type font!\n");
		free(fontx->font);

		return -1;

	}

	if (fontx_header->type != type)
	{

		printf("Type mismatch\n");
		free(fontx->font);

		return -1;

	}

	// Fill in some information about the font
	strcpy(fontx->name,fontx_header->name);

	fontx->rowsize = ((fontx_header->width+7)>>3);
	fontx->charsize = fontx->rowsize * fontx_header->height;
	fontx->w_margin = wmargin;
	fontx->h_margin = hmargin;
	fontx->bold = bold;

	// This is the offset that character data starts
	if (fontx_header->type == SINGLE_BYTE)
	{

		fontx->offset = 17;

	}
	else
	{

		// 17 + 1 + (number of tables * 4) bytes
		fontx->offset = 18 + (fontx_header->table_num * 4);

	}

	return 0;

}