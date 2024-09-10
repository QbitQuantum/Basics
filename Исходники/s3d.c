int S3D_Init(s3d_object *s3dobj, FILE *fp)
{
	struct_header s3d_header;
	struct_directory_header s3d_dir_header;
	struct_directory s3d_dir;
	struct_data_block s3d_data;
	struct_fn_header *s3d_fn_header;
	struct_fn_entry *s3d_fn_entry;
	uint32 *offsets;
	char *temp, *temp2;
	int i, j, pos, inf, tmp, running = 0;
	s3dobj->fp = fp;

	fread(&s3d_header, sizeof(struct_header), 1, fp);
	if(s3d_header.magicCookie[0] != 'P' || s3d_header.magicCookie[1] != 'F' || s3d_header.magicCookie[2] != 'S' || s3d_header.magicCookie[3] != ' ')
	{
		return -1;
	}

	fseek(fp, s3d_header.offset, SEEK_SET);
	fread(&s3d_dir_header, sizeof(struct_directory_header), 1, fp);

	s3dobj->count = s3d_dir_header.count;
	s3dobj->filenames = (char **) malloc(s3d_dir_header.count * sizeof(char *));
	s3dobj->files = (uint32 *) malloc((s3d_dir_header.count - 1) * sizeof(uint32));
	offsets = (uint32 *) malloc((s3d_dir_header.count - 1) * sizeof(uint32));

	for(i = 0; i < s3d_dir_header.count; ++i)
	{
		fread(&s3d_dir, sizeof(struct_directory), 1, fp);

		if(s3d_dir.crc == 0x61580AC9)
		{
			pos = ftell(fp);
			fseek(fp, s3d_dir.offset, SEEK_SET);
			temp = (char *) malloc(s3d_dir.size);
			memset(temp, 0, s3d_dir.size);
			inf = 0;

			while(inf < s3d_dir.size)
			{
				fread(&s3d_data, sizeof(struct_data_block), 1, fp);
				temp2 = (char *) malloc(s3d_data.deflen);
				fread(temp2, s3d_data.deflen, 1, fp);
				decompress(temp2, temp + inf, s3d_data.deflen, s3d_data.inflen);
				free(temp2);
				inf += s3d_data.inflen;
				//Yeahlight: Zone freeze debug
				if(ZONE_FREEZE_DEBUG && rand()%ZONE_FREEZE_DEBUG == 1)
					EQC_FREEZE_DEBUG(__LINE__, __FILE__);
			}

			fseek(fp, pos, SEEK_SET);
			s3d_fn_header = (struct_fn_header *) temp;
			pos = sizeof(struct_fn_header);

			for(j = 0; j < s3d_fn_header->fncount; ++j) //TODO: using arena.s3d, s3d_fn_header->fncount is 10, however it crashes after 8, possible the s3d_fn_header->fncount is wrong due to this being older s3d files
			{
				s3d_fn_entry = (struct_fn_entry *) &temp[pos];

				s3d_fn_entry->fnlen = strlen(&temp[pos + sizeof(struct_fn_entry)]) +1; // Dark-Prince - Added this to update the length

				s3dobj->filenames[j] = (char *) malloc(s3d_fn_entry->fnlen + 1);
				s3dobj->filenames[j][s3d_fn_entry->fnlen] = 0;
				memcpy(s3dobj->filenames[j], &temp[pos + sizeof(struct_fn_entry)], s3d_fn_entry->fnlen);
				pos += sizeof(struct_fn_entry) + s3d_fn_entry->fnlen;
			}
		}

		else
		{
			s3dobj->files[running] = ftell(fp) - 12;
			offsets[running] = s3d_dir.offset;
			++running;
		}

	}

	for(i = s3d_dir_header.count - 2; i > 0; i--) {
		for(j = 0; j < i; j++) {
			if(offsets[j] > offsets[j+1]) {
				tmp = offsets[j];
				offsets[j] = offsets[j + 1];
				offsets[j + 1] = tmp;
				tmp = s3dobj->files[j];
				s3dobj->files[j] = s3dobj->files[j + 1];
				s3dobj->files[j + 1] = tmp;
			}
		}
	}

	return 0;
}