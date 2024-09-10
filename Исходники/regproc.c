/******************************************************************************
 * Open file in binary mode for export.
 */
static FILE *REGPROC_open_export_file(WCHAR *file_name, BOOL unicode)
{
    FILE *file;
    WCHAR dash = '-';

    if (strncmpW(file_name,&dash,1)==0) {
        file=stdout;
        _setmode(_fileno(file), _O_BINARY);
    } else
    {
        WCHAR wb_mode[] = {'w','b',0};
        WCHAR regedit[] = {'r','e','g','e','d','i','t',0};

        file = _wfopen(file_name, wb_mode);
        if (!file) {
            _wperror(regedit);
            output_message(STRING_CANNOT_OPEN_FILE, file_name);
            exit(1);
        }
    }
    if(unicode)
    {
        const BYTE unicode_seq[] = {0xff,0xfe};
        const WCHAR header[] = {'W','i','n','d','o','w','s',' ','R','e','g','i','s','t','r','y',' ','E','d','i','t','o','r',' ','V','e','r','s','i','o','n',' ','5','.','0','0','\r','\n'};
        fwrite(unicode_seq, sizeof(BYTE), sizeof(unicode_seq)/sizeof(unicode_seq[0]), file);
        fwrite(header, sizeof(WCHAR), sizeof(header)/sizeof(header[0]), file);
    } else
    {
        fputs("REGEDIT4\r\n", file);
    }

    return file;
}