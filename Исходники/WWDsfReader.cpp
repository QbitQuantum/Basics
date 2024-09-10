    int ReadFromFile(FILE *fp) {
        FREAD(&chunkBytes,     8, fp);

        if (0x7fffffff < chunkBytes) {
            printf("DsfDataChunk too large %llu\n", chunkBytes);
            return -1;
        }

        return 0;
    }