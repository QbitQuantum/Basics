uint8 T64Drive::open_directory(int channel, char *filename)
{
    char buf[] = "\001\004\001\001\0\0\022\042                \042 00 2A";
    char str[NAMEBUF_LENGTH];
    char pattern[NAMEBUF_LENGTH];
    char *p, *q;
    int i, num;
    int filemode;
    int filetype;

    // Special treatment for "$0"
    if (strlen(filename) == 1 && filename[0] == '0')
        filename += 1;

    // Convert filename ('$' already stripped), filemode/type are ignored
    convert_filename(filename, pattern, &filemode, &filetype);

    // Create temporary file
    if ((file[channel] = tmpfile()) == NULL)
        return ST_OK;

    // Create directory title
    p = &buf[8];
    for (i=0; i<16 && dir_title[i]; i++)
        *p++ = dir_title[i];
    fwrite(buf, 1, 32, file[channel]);

    // Create and write one line for every directory entry
    for (num=0; num<num_files; num++) {

        // Include only files matching the pattern
        if (match(pattern, file_info[num].name)) {

            // Clear line with spaces and terminate with null byte
            memset(buf, ' ', 31);
            buf[31] = 0;

            p = buf;
            *p++ = 0x01;	// Dummy line link
            *p++ = 0x01;

            // Calculate size in blocks (254 bytes each)
            i = (file_info[num].length + 254) / 254;
            *p++ = i & 0xff;
            *p++ = (i >> 8) & 0xff;

            p++;
            if (i < 10) p++;	// Less than 10: add one space
            if (i < 100) p++;	// Less than 100: add another space

            // Convert and insert file name
            strcpy(str, file_info[num].name);
            *p++ = '\"';
            q = p;
            for (i=0; i<16 && str[i]; i++)
                *q++ = str[i];
            *q++ = '\"';
            p += 18;

            // File type
            switch (file_info[num].type) {
            case FTYPE_PRG:
                *p++ = 'P';
                *p++ = 'R';
                *p++ = 'G';
                break;
            case FTYPE_SEQ:
                *p++ = 'S';
                *p++ = 'E';
                *p++ = 'Q';
                break;
            case FTYPE_USR:
                *p++ = 'U';
                *p++ = 'S';
                *p++ = 'R';
                break;
            case FTYPE_REL:
                *p++ = 'R';
                *p++ = 'E';
                *p++ = 'L';
                break;
            default:
                *p++ = '?';
                *p++ = '?';
                *p++ = '?';
                break;
            }

            // Write line
            fwrite(buf, 1, 32, file[channel]);
        }
    }