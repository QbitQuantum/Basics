unsigned char* XGM_asByteArray(XGM* xgm, int *outSize)
{
    int i;
    int offset;
    unsigned char byte;
    FILE* f = fopen("tmp.bin", "wb+");
    LList* l;

    if (f == NULL)
    {
        printf("Error: cannot open file tmp.bin\n");
        return NULL;
    }

    // 0000: XGM (should be ignored in ROM resource)
    fwrite("XGM ", 1, 4, f);

    // 0004-0100: sample id table
    // fixed size : 252 bytes, limit music to 63 samples max
    offset = 0;
    i = 0;
    l = xgm->samples;
    while(l != NULL)
    {
        XGMSample* sample = l->element;
        const int len = sample->dataSize;

        byte = offset >> 8;
        fwrite(&byte, 1, 1, f);
        byte = offset >> 16;
        fwrite(&byte, 1, 1, f);
        byte = len >> 8;
        fwrite(&byte, 1, 1, f);
        byte = len >> 16;
        fwrite(&byte, 1, 1, f);
        offset += len;

        i++;
        l = l->next;
    }
    for (; i < 0x3F; i++)
    {
        // special mark for silent sample
        byte = 0xFF;
        fwrite(&byte, 1, 1, f);
        fwrite(&byte, 1, 1, f);
        byte = 0x00;
        fwrite(&byte, 1, 1, f);
        fwrite(&byte, 1, 1, f);
    }

    // 0100-0101: sample block size *256 (2 bytes)
    byte = offset >> 8;
    fwrite(&byte, 1, 1, f);
    byte = offset >> 16;
    fwrite(&byte, 1, 1, f);

    // init PAL flag if needed (default is NTSC)
    if (xgm->pal == -1)
        xgm->pal = 0;

    // 0102: XGM version
    byte = 0x01;
    fwrite(&byte, 1, 1, f);
    // 0103
    byte = 0x00;
    // b0=NTSC/PAL
    byte |= xgm->pal?1:0;
    // b1=GD3 tags
    byte |= (xgm->gd3 != NULL)?2:0;
    // b2=multi track, others=reserved
    fwrite(&byte, 1, 1, f);

    // 0104-XXXX: sample data
    l = xgm->samples;
    while(l != NULL)
    {
        XGMSample* sample = l->element;
        fwrite(sample->data, 1, sample->dataSize, f);
        l = l->next;
    }

    // compute XGM music data size in byte
    const int len = XGM_getMusicDataSize(xgm);

    // XXXX+0000: music data size (in byte)
    byte = len >> 0;
    fwrite(&byte, 1, 1, f);
    byte = len >> 8;
    fwrite(&byte, 1, 1, f);
    byte = len >> 16;
    fwrite(&byte, 1, 1, f);
    byte = len >> 24;
    fwrite(&byte, 1, 1, f);

    // XXXX+0004: music data
    l = xgm->commands;
    while(l != NULL)
    {
        XGMCommand* command = l->element;
        fwrite(command->data, 1, command->size, f);
        l = l->next;
    }

    // XXXX+0004+MLEN: GD3 tags if present
    if (xgm->gd3)
    {
        unsigned char* data = GD3_asByteArray(xgm->gd3, &i);
        fwrite(data, 1, i, f);
    }

    unsigned char* result = inEx(f, 0, getFileSizeEx(f), outSize);

    fclose(f);

    return result;
}