/**
 * @brief Display information and statistics about a .ani file.
 * @details This is called when -i switch is on when running ac.exe
 */
void anim_display_info(char *real_filename)
{
	CFILE				*fp;
	anim				A;
	float				percent;
	int				i, uncompressed, compressed, *key_frame_nums=NULL, tmp;
	char filename[MAX_FILENAME_LEN];

	strcpy_s( filename, real_filename );
	char *p = strchr( filename, '.' );
	if ( p ) {
		*p = 0;
	}
	strcat_s( filename, ".ani" );

	fp = cfopen(filename, "rb");
	if ( !fp ) {
		printf("Fatal error opening %s", filename);
		return;
	}

	anim_read_header(&A, fp);
	// read the keyframe frame nums and offsets
	key_frame_nums = (int*)vm_malloc(sizeof(int)*A.num_keys);
	Assert(key_frame_nums != NULL);
	if (key_frame_nums == NULL)
		return;

	for ( i = 0; i < A.num_keys; i++ ) {
		key_frame_nums[i] = 0;
		cfread(&key_frame_nums[i], 2, 1, fp);
		cfread(&tmp, 4, 1, fp);
	}

	cfread(&compressed, 4, 1, fp);

	uncompressed = A.width * A.height * A.total_frames;	// 8 bits per pixel
	percent = i2fl(compressed) / uncompressed * 100.0f;

	printf("%% of uncompressed size:    %.0f%%\n", percent);
	printf("Width:                     %d\n", A.width);
	printf("Height:                    %d\n", A.height);
	printf("Total Frames:              %d\n", A.total_frames);

#ifndef NDEBUG
	printf("Key Frames:                %d\n", A.num_keys);
	if ( A.num_keys > 1 && (A.total_frames != A.num_keys) ) {
		printf("key list: (");
		for ( i = 0; i < A.num_keys; i++ ) {
			if ( i < A.num_keys-1 ) 
				printf("%d, ", key_frame_nums[i]);
			else
				printf("%d)\n", key_frame_nums[i]);
		}
	}
#endif

	printf("FPS:                       %d\n", A.fps);

#ifndef NDEBUG
	printf("Transparent RGB:           (%u,%u,%u)\n", A.xparent_r, A.xparent_g, A.xparent_b); 
#endif

	printf("ac version:                %d\n", A.version);

	if ( key_frame_nums != NULL ) {
		vm_free(key_frame_nums);
	}

	cfclose(fp);
}