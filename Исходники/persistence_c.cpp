CV_IMPL CvFileStorage*
cvOpenFileStorage( const char* query, CvMemStorage* dststorage, int flags, const char* encoding )
{
    CvFileStorage* fs = 0;
    int default_block_size = 1 << 18;
    bool append = (flags & 3) == CV_STORAGE_APPEND;
    bool mem = (flags & CV_STORAGE_MEMORY) != 0;
    bool write_mode = (flags & 3) != 0;
    bool write_base64 = (write_mode || append) && (flags & CV_STORAGE_BASE64) != 0;
    bool isGZ = false;
    size_t fnamelen = 0;
    const char * filename = query;

    std::vector<std::string> params;
    if ( !mem )
    {
        params = analyze_file_name( query );
        if ( !params.empty() )
            filename = params.begin()->c_str();

        if ( write_base64 == false && is_param_exist( params, "base64" ) )
            write_base64 = (write_mode || append);
    }

    if( !filename || filename[0] == '\0' )
    {
        if( !write_mode )
            CV_Error( CV_StsNullPtr, mem ? "NULL or empty filename" : "NULL or empty buffer" );
        mem = true;
    }
    else
        fnamelen = strlen(filename);

    if( mem && append )
        CV_Error( CV_StsBadFlag, "CV_STORAGE_APPEND and CV_STORAGE_MEMORY are not currently compatible" );

    fs = (CvFileStorage*)cvAlloc( sizeof(*fs) );
    CV_Assert(fs);
    memset( fs, 0, sizeof(*fs));

    fs->memstorage = cvCreateMemStorage( default_block_size );
    fs->dststorage = dststorage ? dststorage : fs->memstorage;

    fs->flags = CV_FILE_STORAGE;
    fs->write_mode = write_mode;

    if( !mem )
    {
        fs->filename = (char*)cvMemStorageAlloc( fs->memstorage, fnamelen+1 );
        strcpy( fs->filename, filename );

        char* dot_pos = strrchr(fs->filename, '.');
        char compression = '\0';

        if( dot_pos && dot_pos[1] == 'g' && dot_pos[2] == 'z' &&
            (dot_pos[3] == '\0' || (cv_isdigit(dot_pos[3]) && dot_pos[4] == '\0')) )
        {
            if( append )
            {
                cvReleaseFileStorage( &fs );
                CV_Error(CV_StsNotImplemented, "Appending data to compressed file is not implemented" );
            }
            isGZ = true;
            compression = dot_pos[3];
            if( compression )
                dot_pos[3] = '\0', fnamelen--;
        }

        if( !isGZ )
        {
            fs->file = fopen(fs->filename, !fs->write_mode ? "rt" : !append ? "wt" : "a+t" );
            if( !fs->file )
                goto _exit_;
        }
        else
        {
            #if USE_ZLIB
            char mode[] = { fs->write_mode ? 'w' : 'r', 'b', compression ? compression : '3', '\0' };
            fs->gzfile = gzopen(fs->filename, mode);
            if( !fs->gzfile )
                goto _exit_;
            #else
            cvReleaseFileStorage( &fs );
            CV_Error(CV_StsNotImplemented, "There is no compressed file storage support in this configuration");
            #endif
        }
    }

    fs->roots = 0;
    fs->struct_indent = 0;
    fs->struct_flags = 0;
    fs->wrap_margin = 71;

    if( fs->write_mode )
    {
        int fmt = flags & CV_STORAGE_FORMAT_MASK;

        if( mem )
            fs->outbuf = new std::deque<char>;

        if( fmt == CV_STORAGE_FORMAT_AUTO && filename )
        {
            const char* dot_pos = NULL;
            const char* dot_pos2 = NULL;
            // like strrchr() implementation, but save two last positions simultaneously
            for (const char* pos = filename; pos[0] != 0; pos++)
            {
                if (pos[0] == '.')
                {
                    dot_pos2 = dot_pos;
                    dot_pos = pos;
                }
            }
            if (cv_strcasecmp(dot_pos, ".gz") && dot_pos2 != NULL)
            {
                dot_pos = dot_pos2;
            }
            fs->fmt
                = (cv_strcasecmp(dot_pos, ".xml") || cv_strcasecmp(dot_pos, ".xml.gz"))
                ? CV_STORAGE_FORMAT_XML
                : (cv_strcasecmp(dot_pos, ".json") || cv_strcasecmp(dot_pos, ".json.gz"))
                ? CV_STORAGE_FORMAT_JSON
                : CV_STORAGE_FORMAT_YAML
                ;
        }
        else if ( fmt != CV_STORAGE_FORMAT_AUTO )
        {
            fs->fmt = fmt;
        }
        else
        {
            fs->fmt = CV_STORAGE_FORMAT_XML;
        }

        // we use factor=6 for XML (the longest characters (' and ") are encoded with 6 bytes (&apos; and &quot;)
        // and factor=4 for YAML ( as we use 4 bytes for non ASCII characters (e.g. \xAB))
        int buf_size = CV_FS_MAX_LEN*(fs->fmt == CV_STORAGE_FORMAT_XML ? 6 : 4) + 1024;

        if (append)
        {
            fseek( fs->file, 0, SEEK_END );
            if (ftell(fs->file) == 0)
                append = false;
        }

        fs->write_stack = cvCreateSeq( 0, sizeof(CvSeq), fs->fmt == CV_STORAGE_FORMAT_XML ?
                sizeof(CvXMLStackRecord) : sizeof(int), fs->memstorage );
        fs->is_first = 1;
        fs->struct_indent = 0;
        fs->struct_flags = CV_NODE_EMPTY;
        fs->buffer_start = fs->buffer = (char*)cvAlloc( buf_size + 1024 );
        fs->buffer_end = fs->buffer_start + buf_size;

        fs->base64_writer           = 0;
        fs->is_default_using_base64 = write_base64;
        fs->state_of_writing_base64 = base64::fs::Uncertain;

        fs->is_write_struct_delayed = false;
        fs->delayed_struct_key      = 0;
        fs->delayed_struct_flags    = 0;
        fs->delayed_type_name       = 0;

        if( fs->fmt == CV_STORAGE_FORMAT_XML )
        {
            size_t file_size = fs->file ? (size_t)ftell( fs->file ) : (size_t)0;
            fs->strstorage = cvCreateChildMemStorage( fs->memstorage );
            if( !append || file_size == 0 )
            {
                if( encoding )
                {
                    if( strcmp( encoding, "UTF-16" ) == 0 ||
                        strcmp( encoding, "utf-16" ) == 0 ||
                        strcmp( encoding, "Utf-16" ) == 0 )
                    {
                        cvReleaseFileStorage( &fs );
                        CV_Error( CV_StsBadArg, "UTF-16 XML encoding is not supported! Use 8-bit encoding\n");
                    }

                    CV_Assert( strlen(encoding) < 1000 );
                    char buf[1100];
                    sprintf(buf, "<?xml version=\"1.0\" encoding=\"%s\"?>\n", encoding);
                    icvPuts( fs, buf );
                }
                else
                    icvPuts( fs, "<?xml version=\"1.0\"?>\n" );
                icvPuts( fs, "<opencv_storage>\n" );
            }
            else
            {
                int xml_buf_size = 1 << 10;
                char substr[] = "</opencv_storage>";
                int last_occurence = -1;
                xml_buf_size = MIN(xml_buf_size, int(file_size));
                fseek( fs->file, -xml_buf_size, SEEK_END );
                char* xml_buf = (char*)cvAlloc( xml_buf_size+2 );
                // find the last occurrence of </opencv_storage>
                for(;;)
                {
                    int line_offset = (int)ftell( fs->file );
                    char* ptr0 = icvGets( fs, xml_buf, xml_buf_size ), *ptr;
                    if( !ptr0 )
                        break;
                    ptr = ptr0;
                    for(;;)
                    {
                        ptr = strstr( ptr, substr );
                        if( !ptr )
                            break;
                        last_occurence = line_offset + (int)(ptr - ptr0);
                        ptr += strlen(substr);
                    }
                }
                cvFree( &xml_buf );
                if( last_occurence < 0 )
                {
                    cvReleaseFileStorage( &fs );
                    CV_Error( CV_StsError, "Could not find </opencv_storage> in the end of file.\n" );
                }
                icvCloseFile( fs );
                fs->file = fopen( fs->filename, "r+t" );
                CV_Assert(fs->file);
                fseek( fs->file, last_occurence, SEEK_SET );
                // replace the last "</opencv_storage>" with " <!-- resumed -->", which has the same length
                icvPuts( fs, " <!-- resumed -->" );
                fseek( fs->file, 0, SEEK_END );
                icvPuts( fs, "\n" );
            }
            fs->start_write_struct = icvXMLStartWriteStruct;
            fs->end_write_struct = icvXMLEndWriteStruct;
            fs->write_int = icvXMLWriteInt;
            fs->write_real = icvXMLWriteReal;
            fs->write_string = icvXMLWriteString;
            fs->write_comment = icvXMLWriteComment;
            fs->start_next_stream = icvXMLStartNextStream;
        }
        else if( fs->fmt == CV_STORAGE_FORMAT_YAML )
        {
            if( !append)
                icvPuts( fs, "%YAML:1.0\n---\n" );
            else
                icvPuts( fs, "...\n---\n" );
            fs->start_write_struct = icvYMLStartWriteStruct;
            fs->end_write_struct = icvYMLEndWriteStruct;
            fs->write_int = icvYMLWriteInt;
            fs->write_real = icvYMLWriteReal;
            fs->write_string = icvYMLWriteString;
            fs->write_comment = icvYMLWriteComment;
            fs->start_next_stream = icvYMLStartNextStream;
        }
        else
        {
            if( !append )
                icvPuts( fs, "{\n" );
            else
            {
                bool valid = false;
                long roffset = 0;
                for ( ;
                      fseek( fs->file, roffset, SEEK_END ) == 0;
                      roffset -= 1 )
                {
                    const char end_mark = '}';
                    if ( fgetc( fs->file ) == end_mark )
                    {
                        fseek( fs->file, roffset, SEEK_END );
                        valid = true;
                        break;
                    }
                }

                if ( valid )
                {
                    icvCloseFile( fs );
                    fs->file = fopen( fs->filename, "r+t" );
                    CV_Assert(fs->file);
                    fseek( fs->file, roffset, SEEK_END );
                    fputs( ",", fs->file );
                }
                else
                {
                    CV_Error( CV_StsError, "Could not find '}' in the end of file.\n" );
                }
            }
            fs->struct_indent = 4;
            fs->start_write_struct = icvJSONStartWriteStruct;
            fs->end_write_struct = icvJSONEndWriteStruct;
            fs->write_int = icvJSONWriteInt;
            fs->write_real = icvJSONWriteReal;
            fs->write_string = icvJSONWriteString;
            fs->write_comment = icvJSONWriteComment;
            fs->start_next_stream = icvJSONStartNextStream;
        }
    }
    else
    {
        if( mem )
        {
            fs->strbuf = filename;
            fs->strbufsize = fnamelen;
        }

        size_t buf_size = 1 << 20;
        const char* yaml_signature = "%YAML";
        const char* json_signature = "{";
        const char* xml_signature  = "<?xml";
        char buf[16];
        icvGets( fs, buf, sizeof(buf)-2 );
        char* bufPtr = cv_skip_BOM(buf);
        size_t bufOffset = bufPtr - buf;

        if(strncmp( bufPtr, yaml_signature, strlen(yaml_signature) ) == 0)
            fs->fmt = CV_STORAGE_FORMAT_YAML;
        else if(strncmp( bufPtr, json_signature, strlen(json_signature) ) == 0)
            fs->fmt = CV_STORAGE_FORMAT_JSON;
        else if(strncmp( bufPtr, xml_signature, strlen(xml_signature) ) == 0)
            fs->fmt = CV_STORAGE_FORMAT_XML;
        else if(fs->strbufsize  == bufOffset)
            CV_Error(CV_BADARG_ERR, "Input file is empty");
        else
            CV_Error(CV_BADARG_ERR, "Unsupported file storage format");

        if( !isGZ )
        {
            if( !mem )
            {
                fseek( fs->file, 0, SEEK_END );
                buf_size = ftell( fs->file );
            }
            else
                buf_size = fs->strbufsize;
            buf_size = MIN( buf_size, (size_t)(1 << 20) );
            buf_size = MAX( buf_size, (size_t)(CV_FS_MAX_LEN*2 + 1024) );
        }
        icvRewind(fs);
        fs->strbufpos = bufOffset;

        fs->str_hash = cvCreateMap( 0, sizeof(CvStringHash),
                        sizeof(CvStringHashNode), fs->memstorage, 256 );

        fs->roots = cvCreateSeq( 0, sizeof(CvSeq),
                        sizeof(CvFileNode), fs->memstorage );

        fs->buffer = fs->buffer_start = (char*)cvAlloc( buf_size + 256 );
        fs->buffer_end = fs->buffer_start + buf_size;
        fs->buffer[0] = '\n';
        fs->buffer[1] = '\0';

        //mode = cvGetErrMode();
        //cvSetErrMode( CV_ErrModeSilent );
        CV_TRY
        {
            switch (fs->fmt)
            {
            case CV_STORAGE_FORMAT_XML : { icvXMLParse ( fs ); break; }
            case CV_STORAGE_FORMAT_YAML: { icvYMLParse ( fs ); break; }
            case CV_STORAGE_FORMAT_JSON: { icvJSONParse( fs ); break; }
            default: break;
            }
        }
        CV_CATCH_ALL
        {
            fs->is_opened = true;
            cvReleaseFileStorage( &fs );
            CV_RETHROW();
        }
        //cvSetErrMode( mode );

        // release resources that we do not need anymore
        cvFree( &fs->buffer_start );
        fs->buffer = fs->buffer_end = 0;
    }
    fs->is_opened = true;

_exit_:
    if( fs )
    {
        if( cvGetErrStatus() < 0 || (!fs->file && !fs->gzfile && !fs->outbuf && !fs->strbuf) )
        {
            cvReleaseFileStorage( &fs );
        }
        else if( !fs->write_mode )
        {
            icvCloseFile(fs);
            // we close the file since it's not needed anymore. But icvCloseFile() resets is_opened,
            // which may be misleading. Since we restore the value of is_opened.
            fs->is_opened = true;
        }
    }

    return  fs;
}