bool LocateConverter::LocateUpdate(const wchar_t *locate, const wchar_t *patch, const wchar_t *path, bool compress/* = false */, OnProgress progress/* = NULL */)
{
    LocateReader loc(locate);
    if ( !loc.IsAvailable() ) return false;

    const uint8_t *diff_buffer = 0;
    PDIFFHEADER diff_header = 0;

    HANDLE hfile = CreateFileW(patch, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hfile!=INVALID_HANDLE_VALUE)
    {
        uint32_t file_length = GetFileSize(hfile, NULL);

        HANDLE hfilemap = CreateFileMapping(hfile, NULL, PAGE_READONLY, 0, 0, NULL);
        CloseHandle(hfile);

        diff_buffer = (const uint8_t*) MapViewOfFile(hfilemap, FILE_MAP_READ, 0, 0, 0);
        CloseHandle(hfilemap);

        diff_header = (PDIFFHEADER)diff_buffer;
        int data_size = file_length - sizeof(DIFFHEADER) - LZMA_PROPS_SIZE;
        if( data_size<0 || diff_header->magic != DIFF_MAGIC || CRC32_MEM(diff_buffer, sizeof(DIFFHEADER) - 4)!=diff_header->crc32 )
        {
            UnmapViewOfFile((void*)diff_buffer);
            return false;
        }
        else
        {
            uint32_t lzma_buffer_len = diff_header->size;
            uint8_t *lzma_buffer = (uint8_t *)malloc(sizeof(DIFFHEADER) + lzma_buffer_len);

            if( LzmaUncompress(lzma_buffer + sizeof(DIFFHEADER), &lzma_buffer_len, (unsigned char*)diff_header->data + LZMA_PROPS_SIZE, (uint32_t*)&data_size, (unsigned char*)diff_header->data, LZMA_PROPS_SIZE)==SZ_OK )
            {
                memcpy(lzma_buffer, diff_buffer, sizeof(DIFFHEADER));
                UnmapViewOfFile((void*)diff_buffer);
                diff_buffer = lzma_buffer;

                diff_header = (PDIFFHEADER)diff_buffer;
                diff_header->table1 += (uint32_t)diff_buffer;
                diff_header->table2 += (uint32_t)diff_buffer;
            }
            else
            {
                free(lzma_buffer);
                UnmapViewOfFile((void*)diff_buffer);
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    if ( loc.GetInfo()->count!=diff_header->total1 || loc.GetInfo()->time!=diff_header->time1 ) return false;

    PDIFFITEM diffitem = diff_header->data;
    LocateItem *Locate = (LocateItem *)malloc( diff_header->total2 * sizeof(LocateItem) );

    uint32_t last_diff = ( diff_header->table1 - sizeof(DIFFHEADER) - (uint32_t)diff_buffer ) / sizeof(DIFFITEM) - 1;
    uint32_t last_line = diff_header->total2 - 1;

    uint32_t i = loc.GetInfo()->count;
    for(; i>0; i--)
    {
        LocateItem *item = loc.GetItem(i);

        if(i!=diffitem[last_diff].line)
        {
            Locate[last_line].begin_ip = item->begin_ip;
            Locate[last_line].region = item->region;
            Locate[last_line].address = item->address;
            last_line--;
        }
        else
        {
            switch(diffitem[last_diff].method)
            {
            case INSERT:
                //printf("INSERT %d %d\n", i, diffitem[last_diff-1].line);
                Locate[last_line].begin_ip = diffitem[last_diff].begin_ip;
                Locate[last_line].region = (const char*)( diffitem[last_diff].table1 + diff_header->table1 );
                Locate[last_line].address = (const char*)( diffitem[last_diff].table2 + diff_header->table2 );
                last_line--;
                i++;
                break;
            case REMOVE:
                //printf("REMOVE %d %d %d\n", i, diffitem[last_diff-1].line, diffitem[last_diff-2].line);
                break;
            case MODIFY:
                Locate[last_line].begin_ip = item->begin_ip;
                Locate[last_line].region = (const char*)( diffitem[last_diff].table1 + diff_header->table1 );
                Locate[last_line].address = (const char*)( diffitem[last_diff].table2 + diff_header->table2 );
                //printf("MODIFY %d %s %s\n", last_line+1, Locate[last_line].region, Locate[last_line].address);
                //getchar();
                last_line--;
                break;
            }
            last_diff--;
        }
    }

    //printf("%d %d\n",last_diff,last_line);
    if ( last_diff!=-1 || last_line!=-1 ) return false;

    StringTable string_table1;
    StringTable string_table2;
    RecordTable record_table;

    Buffer buffer;

    uint32_t last_begin_ip = 0;

    for(i=last_line+1; i<diff_header->total2; i++)
    {
        LocateItem *item = &Locate[i];

        LOCATE record;
        record.begin_ip = item->begin_ip;
        record.table1 = string_table1.Append(item->region);
        record.table2 = string_table2.Append(item->address);

        if ( i > 0 )
        {
            uint32_t diff = record.begin_ip - last_begin_ip;
            if ( compress && isPowerOf2(diff) )
            {
                record.begin_ip = LogBase2(diff);
            }
        }

        record_table.Append(&record);

        last_begin_ip = item->begin_ip;
    }
    free(Locate);

    //合并数据区
    Buffer *record_table_buffer = record_table;
    Buffer *string_table1_buffer = string_table1;
    Buffer *string_table2_buffer = string_table2;

    std::copy(record_table_buffer->begin(), record_table_buffer->end(), std::back_inserter(buffer));
    std::copy(string_table1_buffer->begin(), string_table1_buffer->end(), std::back_inserter(buffer));
    std::copy(string_table2_buffer->begin(), string_table2_buffer->end(), std::back_inserter(buffer));

    //生成文件头
    HEADER header;
    header.magic = LOCATE_MAGIC;
    header.version = LOCATE_VERISON;
    header.compress = compress?1:0;
    header.total = diff_header->total2;
    header.time = diff_header->time2;

    header.table1 = sizeof(header) + record_table_buffer->size(); // 这里不加LZMA_PROPS_SIZE的原因是解压后，抛弃props信息
    header.table2 = header.table1 + string_table1_buffer->size();
    header.size = buffer.size();
    header.crc32 = CRC32_MEM((uint8_t*)&header, sizeof(header) - 4);

    uint32_t lzma_buffer_len = buffer.size();
    uint8_t *lzma_buffer = 0;

    size_t prop_size = LZMA_PROPS_SIZE;
    BYTE outProps[LZMA_PROPS_SIZE];

    //准备压缩
    if(compress)
    {
        lzma_buffer = (uint8_t *)malloc(lzma_buffer_len);
        
        ProgressCallback LzmaCompressProgress;
        LzmaCompressProgress.Progress = LzmaOnProgress;
        LzmaCompressProgress.totalInSize = buffer.size();
        LzmaCompressProgress.progress = progress;
        LzmaCompress(lzma_buffer, &lzma_buffer_len, &buffer[0], buffer.size(), (ICompressProgress*)&LzmaCompressProgress, outProps, &prop_size, 5, 1<<27, 8, 0, 2, 64, 4);
    }

    //保存文件
    FILE * out = _wfopen(path, L"wb");
    fwrite(&header, 1, sizeof(header), out);

    if(compress)
    {
        fwrite(outProps, 1, sizeof(outProps), out);
        fwrite(lzma_buffer, 1, lzma_buffer_len, out);
    }
    else
    {
        fwrite(&buffer[0], 1, buffer.size(), out);
    }
    fclose(out);

    if(compress)
    {
        free(lzma_buffer);
    }

    free((void*)diff_buffer);
    return true;
}