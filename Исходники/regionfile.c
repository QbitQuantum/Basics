int write_chunk(regionfile* region, int32_t cx, int32_t cz, chunk* chunk) {
    if (region == NULL)
        return -1;
    if (chunk == NULL)
        return -1;
    cx &= 0x1f;
    cz &= 0x1f;
    uint32_t offset = region->offsets[cx + cz * 32];
    if (offset == 0)
        return -2;
    uint32_t numSectors = offset & 0xff;
    if (numSectors == 0)
        return -3;
    nbt_node* raw = new_chunk_data_to_nbt(chunk);
    if (raw == NULL)
        return -1;
    uint32_t sectorStart = offset >> 8;
    FILE* f;
    if (region->keepopen == 1) {
        if (region->file)
            f = region->file;
        else {
            f = fopen(region->filename, "rb+");
            region->file = f;
        }
    } else
        f = fopen(region->filename, "rb+");
    struct buffer buf = nbt_dump_compressed(raw, STRAT_INFLATE);
    uint16_t sectorsNeeded = (buf.len + 5) / SECTOR_BYTES + 1;
    if (sectorsNeeded >= 256)
        goto error;
    if (sectorStart != 0 && numSectors >= sectorsNeeded) {
        if (fseek(f, sectorStart*SECTOR_BYTES, SEEK_SET) != 0)
            goto error;
        uint32_t size = htobe32(buf.len);
        if (fwrite(&size, 1, sizeof(uint32_t), f) != sizeof(uint32_t))
            goto error;
        static const char COMPRESSION = 2;
        if (fwrite(&COMPRESSION, 1, sizeof(COMPRESSION), f) != sizeof(COMPRESSION))
            goto error;
        if (fwrite(buf.data, 1, buf.len, f) != buf.len)
            goto error;
        goto success;
    } else {
        size_t i;
        size_t runLength = 0;
        uint32_t runStart = 0;
        unsigned char* curSector = region->freeSectors;
        for (i = 0; curSector[i] != 0x00; i++) {
            if (runLength > 0) {
                if (curSector[i] == 0x01)
                    runLength++;
                else
                    runLength = 0;
            } else if (curSector[i] == 0x01) {
                runStart = i;
                runLength = 1;
            }
            if (runLength >= sectorsNeeded)
                break;
        }
        if (runLength >= sectorsNeeded) {
            region->offsets[cx + cz * 32] = runStart << 8 | sectorsNeeded;
            if (__region_write_offsets(region) != 0)
                goto error;
            if (fseek(f, runStart*SECTOR_BYTES, SEEK_SET) != 0)
                goto error;
            uint32_t size = htobe32(buf.len);
            if (fwrite(&size, 1, sizeof(uint32_t), f) != sizeof(uint32_t))
                goto error;
            static const char COMPRESSION = 2;
            if (fwrite(&COMPRESSION, 1, sizeof(COMPRESSION), f) != sizeof(COMPRESSION))
                goto error;
            if (fwrite(buf.data, 1, buf.len, f) != buf.len)
                goto error;
            goto success;
        } else {
            if (fseek(f, 0L, SEEK_END) != 0)
                goto error;
            long filesize = ftell(f);
            uint32_t sectorNumber = filesize/SECTOR_BYTES;
            filesize += sectorsNeeded * SECTOR_BYTES;
            if (ftruncate(fileno(f), filesize) != 0)
                goto error;
            region->offsets[cx + cz * 32] = sectorNumber << 8 | sectorsNeeded;
            if (__region_write_offsets(region) != 0)
                goto error;
            if (fseek(f, sectorNumber*SECTOR_BYTES, SEEK_SET) != 0)
                goto error;
            uint32_t size = htobe32(buf.len);
            if (fwrite(&size, 1, sizeof(uint32_t), f) != sizeof(uint32_t))
                goto error;
            static const char COMPRESSION = 2;
            if (fwrite(&COMPRESSION, 1, sizeof(COMPRESSION), f) != sizeof(COMPRESSION))
                goto error;
            if (fwrite(buf.data, 1, buf.len, f) != buf.len)
                goto error;

            uint32_t freeSectorsLength = filesize/SECTOR_BYTES;
            region->freeSectors = realloc(region->freeSectors, sizeof(unsigned char) * (freeSectorsLength+1));
            region->freeSectors[freeSectorsLength] = 0x00;
            for (; sectorNumber < freeSectorsLength; sectorNumber++)
                region->freeSectors[sectorNumber] = 0x02;
            goto success;
        }
    }
error:
    nbt_free(raw);
    if (f && region->file != f)
        fclose(f);
    buffer_free(&buf);
    return 1;
success:
    nbt_free(raw);
    buffer_free(&buf);
    if (region->file != f)
        fclose(f);
    region->timestamps[cx + cz * 32] = time(NULL);
    __region_write_timestamps(region);
    return 0;
};