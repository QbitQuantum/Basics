/*
  Format of data: 8 hexadecimal numbers with spaces
*/
int dbus_decomp(const char *filename, int resync)
{
    char src_name[1024];
    char dst_name[1024];
    FILE *fi, *fo;
    long file_size;
    struct stat st;
    unsigned char *buffer;
    int i;
	unsigned int j;
    int num_bytes;
	char str[256];
	unsigned char mid, cid;
	unsigned int length;
	int idx;
	int ret = 0;
    
	// build filenames
    strcpy(src_name, filename);
    strcat(src_name, ".hex");
    
    strcpy(dst_name, filename);
    strcat(dst_name, ".pkt");
    
    stat(src_name, &st);
    file_size = st.st_size;
    
	// allocate buffer
    buffer = (unsigned char*)calloc(file_size/2, 1);
    memset(buffer, 0xff, file_size/2);
    if(buffer == NULL)
    {
        fprintf(stderr, "calloc error.\n");
        exit(-1);
    }
    
	// open files
    fi = fopen(src_name, "rt");
    fo = fopen(dst_name, "wt");
    
    if(fi == NULL)
    {
        fprintf(stderr, "Unable to open this file: %s\n", src_name);
        return -1;
    }

    fprintf(fo, "TI packet decompiler for D-BUS, version 1.2\n");

	// skip comments
	fgets(str, sizeof(str), fi);
	fgets(str, sizeof(str), fi);
	fgets(str, sizeof(str), fi);

	// read source file
	for(i = 0; !feof(fi);)
    {
        for(j = 0; j < 16 && !feof(fi); j++)
		{
			fscanf(fi, "%02X", &(buffer[i+j]));
			fgetc(fi);
		}
        i += j;

        for(j=0; j<18 && !feof(fi); j++)
			fgetc(fi);
    }
    num_bytes = i-1; // -1 due to EOF char
    fprintf(stdout, "%i bytes read.\n", num_bytes);

	// process data
	for(i = 0; i < num_bytes;)
    {
restart:
		mid = buffer[i+0];
		cid = buffer[i+1];
		length = buffer[i+2];
        length |= buffer[i+3] << 8;

		// check for valid packet
		if(is_a_machine_id(mid) == -1)
		{
			ret = -1;
			goto exit;
		}

		// check for valid packet
		idx = is_a_command_id(cid);
        if(idx == -1)
		{
			ret = -2;
			goto exit;
		}

		fprintf(fo, "%02X %02X %02X %02X", mid, cid, length >> 8, length & 0xff);
		for(j = 4; j <= WIDTH; j++)
			fprintf(fo, "   ");
		fprintf(fo, "  | ");
		fprintf(fo, "%s: %s\n", machine_way[is_a_machine_id(mid)], command_name[is_a_command_id(cid)]);

		i += 4;

		// get data & checksum
		if(cmd_with_data[idx] && length > 0)
		{
			// data
			for(j = 0; j < length; j++, i++)
			{
				if(resync && buffer[i] == 0x98 && (buffer[i+1] == 0x15 ||  buffer[i+1] == 0x56))
				{
					fprintf(stdout, "Warning: there is packets in data !\n");
					fprintf(fo, "Beware : length of previous packet is wrong !\n");
					goto restart;
				}

				fill_buf(fo, buffer[i], 0);
			}

			fill_buf(fo, 0, !0);
			//fprintf(fo, "\n");

			// write checksum
			fprintf(fo, "    ");
			fprintf(fo, "%02X ", buffer[i++]);
			fprintf(fo, "%02X ", buffer[i++]);
			fprintf(fo, "\n");
		}
	}

exit:
	if(ret < 0)
		fprintf(stdout, "Error %i\n", -ret);

	free(buffer);
	fclose(fi);
	fclose(fo);
    
	return ret;
}