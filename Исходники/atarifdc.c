static void atari_load_proc(device_image_interface &image)
{
	atari_fdc_t *fdc = get_safe_token(image.device().owner());
	int id = floppy_get_drive(image);
	int size, i;
	const char *ext;

	fdc->drv[id].image = auto_alloc_array(image.device().machine(),UINT8,MAXSIZE);
	if (!fdc->drv[id].image)
		return;

	/* tell whether the image is writable */
	fdc->drv[id].mode = !image.is_readonly();
	/* set up image if it has been created */
	if (image.has_been_created())
	{
		int sector;
		char buff[256];
		memset(buff, 0, sizeof(buff));
		/* default to 720 sectors */
		for( sector = 0; sector < 720; sector++ )
			image.fwrite(buff, 256);
		image.fseek(0, SEEK_SET);
	}

	size = image.fread(fdc->drv[id].image, MAXSIZE);

	if( size <= 0 )
	{
		fdc->drv[id].image = NULL;
		return;
	}


	/* re allocate the buffer; we don't want to be too lazy ;) */
	//fdc->drv[id].image = (UINT8*)image.image_realloc(fdc->drv[id].image, size);

	ext = image.filetype();

	// hack alert, this means we can only load ATR via the softlist at the moment, image.filetype reutrns NULL :/
	if (image.software_entry() != NULL) ext="ATR";

	/* no extension: assume XFD format (no header) */
	if (!ext)
	{
		fdc->drv[id].type = FORMAT_XFD;
		fdc->drv[id].header_skip = 0;
	}
	else
	/* XFD extension */
	if( toupper(ext[0])=='X' && toupper(ext[1])=='F' && toupper(ext[2])=='D' )
	{
		fdc->drv[id].type = FORMAT_XFD;
		fdc->drv[id].header_skip = 0;
	}
	else
	/* ATR extension */
	if( toupper(ext[0])=='A' && toupper(ext[1])=='T' && toupper(ext[2])=='R' )
	{
		fdc->drv[id].type = FORMAT_ATR;
		fdc->drv[id].header_skip = 16;
	}
	else
	/* DSK extension */
	if( toupper(ext[0])=='D' && toupper(ext[1])=='S' && toupper(ext[2])=='K' )
	{
		fdc->drv[id].type = FORMAT_DSK;
		fdc->drv[id].header_skip = sizeof(dsk_format);
	}
	else
	{
		fdc->drv[id].type = FORMAT_XFD;
		fdc->drv[id].header_skip = 0;
	}

	if( fdc->drv[id].type == FORMAT_ATR &&
		(fdc->drv[id].image[0] != 0x96 || fdc->drv[id].image[1] != 0x02) )
	{
		fdc->drv[id].type = FORMAT_XFD;
		fdc->drv[id].header_skip = 0;
	}


	switch (fdc->drv[id].type)
	{
	/* XFD or unknown format: find a matching size from the table */
	case FORMAT_XFD:
		for( i = 0; xfd_formats[i].size; i++ )
		{
			if( size == xfd_formats[i].size )
			{
				fdc->drv[id].density = xfd_formats[i].dsk.density;
				fdc->drv[id].tracks = xfd_formats[i].dsk.tracks;
				fdc->drv[id].spt = xfd_formats[i].dsk.spt;
				fdc->drv[id].heads = (xfd_formats[i].dsk.doublesided) ? 2 : 1;
				fdc->drv[id].bseclen = 128;
				fdc->drv[id].seclen = 256 * xfd_formats[i].dsk.seclen_hi + xfd_formats[i].dsk.seclen_lo;
				fdc->drv[id].sectors = fdc->drv[id].tracks * fdc->drv[id].heads * fdc->drv[id].spt;
				break;
			}
		}
		break;
	/* ATR format: find a size including the 16 bytes header */
	case FORMAT_ATR:
		{
			int s;
			fdc->drv[id].bseclen = 128;
			/* get sectors from ATR header */
			s = (size - 16) / 128;
			/* 3 + odd number of sectors ? */
			if ( fdc->drv[id].image[4] == 128 || (s % 18) == 0 || (s % 26) == 0 || ((s - 3) % 1) != 0 )
			{
				fdc->drv[id].sectors = s;
				fdc->drv[id].seclen = 128;
				/* sector size 128 or count not evenly dividable by 26 ? */
				if( fdc->drv[id].seclen == 128 || (s % 26) != 0 )
				{
					/* yup! single density */
					fdc->drv[id].density = 0;
					fdc->drv[id].spt = 18;
					fdc->drv[id].heads = 1;
					fdc->drv[id].tracks = s / 18;
					if( s % 18 != 0 )
						fdc->drv[id].tracks += 1;
					if( fdc->drv[id].tracks % 2 == 0 && fdc->drv[id].tracks > 80 )
					{
						fdc->drv[id].heads = 2;
						fdc->drv[id].tracks /= 2;
					}
				}
				else
				{
					/* yes: medium density */
					fdc->drv[id].density = 0;
					fdc->drv[id].spt = 26;
					fdc->drv[id].heads = 1;
					fdc->drv[id].tracks = s / 26;
					if( s % 26 != 0 )
						fdc->drv[id].tracks += 1;
					if( fdc->drv[id].tracks % 2 == 0 && fdc->drv[id].tracks > 80 )
					{
						fdc->drv[id].heads = 2;
						fdc->drv[id].tracks /= 2;
					}
				}
			}
			else
			{
				/* it's double density */
				s = (s - 3) / 2 + 3;
				fdc->drv[id].sectors = s;
				fdc->drv[id].density = 2;
				fdc->drv[id].seclen = 256;
				fdc->drv[id].spt = 18;
				fdc->drv[id].heads = 1;
				fdc->drv[id].tracks = s / 18;
				if( s % 18 != 0 )
					fdc->drv[id].tracks += 1;
				if( fdc->drv[id].tracks % 2 == 0 && fdc->drv[id].tracks > 80 )
				{
					fdc->drv[id].heads = 2;
					fdc->drv[id].tracks /= 2;
				}
			}
		}
		break;
	/* DSK format: it's all in the header */
	case FORMAT_DSK:
		{
			dsk_format *dsk = (dsk_format *) fdc->drv[id].image;

			fdc->drv[id].tracks = dsk->tracks;
			fdc->drv[id].spt = dsk->spt;
			fdc->drv[id].heads = (dsk->doublesided) ? 2 : 1;
			fdc->drv[id].seclen = 256 * dsk->seclen_hi + dsk->seclen_lo;
			fdc->drv[id].bseclen = fdc->drv[id].seclen;
			fdc->drv[id].sectors = fdc->drv[id].tracks * fdc->drv[id].heads * fdc->drv[id].spt;
		}
		break;
	}
	logerror("atari opened floppy '%s', %d sectors (%d %s%s) %d bytes/sector\n",
			image.filename(),
			fdc->drv[id].sectors,
			fdc->drv[id].tracks,
			(fdc->drv[id].heads == 1) ? "SS" : "DS",
			(fdc->drv[id].density == 0) ? "SD" : (fdc->drv[id].density == 1) ? "MD" : "DD",
			fdc->drv[id].seclen);
	return;
}