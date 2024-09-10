static void IndexKVFile(const char* kvPath,
                        const char* backIndexPath,
                        const char* indexPath,
                        couchstore_json_reducer reducer)
{
    couchstore_error_t errcode;
    CouchStoreIndex* index = NULL;

    try(couchstore_create_index(indexPath, &index));
    try(couchstore_index_add(kvPath, COUCHSTORE_VIEW_PRIMARY_INDEX, reducer, index));
    try(couchstore_index_add(backIndexPath, COUCHSTORE_VIEW_BACK_INDEX, 0, index));
    try(couchstore_close_index(index));

cleanup:
    assert(errcode == 0);
}


static void ReadIndexFile(const char *indexPath)
{
    // See write_index_header in couch_index.c
    FILE *file = fopen(indexPath, "rb");
    fseek(file, 0, SEEK_END);
    long eof = ftell(file);
    long headerPos = eof - (eof % 4096);    // go to last 4KB boundary
    printf("Index header is at 0x%lx\n", headerPos);
    fseek(file, headerPos, SEEK_SET);

    // Header starts with a "1" byte, a length, and a CRC checksum:
    uint8_t flag;
    check_read(fread(&flag, 1, 1, file));
    assert_eq(flag, 1);
    uint32_t headerLength, headerChecksum;
    check_read(fread(&headerLength, sizeof(headerLength), 1, file));
    headerLength = ntohl(headerLength);
    check_read(fread(&headerChecksum, sizeof(headerChecksum), 1, file));
    headerChecksum = htonl(headerChecksum);
    assert_eq(headerPos + headerLength + 1 + 4, eof);

    // Next is the root count:
    uint32_t nRoots;
    check_read(fread(&nRoots, sizeof(nRoots), 1, file));
    nRoots = ntohl(nRoots);
    assert_eq(nRoots, 2);

    for (uint32_t root = 0; root < nRoots; ++root) {
        // The root has a type, size, node pointer, subtree size, and reduce data:
        uint8_t indexType; // really a couchstore_index_type
        check_read(fread(&indexType, 1, 1, file));
        assert_eq(indexType, root);  // i.e. first root is type 0, second is type 1
        uint16_t rootSize;
        check_read(fread(&rootSize, sizeof(rootSize), 1, file));
        rootSize = ntohs(rootSize);
        assert(rootSize >= 12);
        assert(rootSize < headerLength);
        uint64_t pointer = 0;
        uint64_t subtreesize = 0;
        check_read(fread((char*)&pointer + 2, 6, 1, file));
        check_read(fread((char*)&subtreesize + 2, 6, 1, file));
        pointer = ntohll(pointer);
        subtreesize = ntohll(subtreesize);
        sized_buf reduce = {NULL, rootSize - 12};
        reduce.buf = malloc(reduce.size);
        check_read(fread(reduce.buf, reduce.size, 1, file));

        printf("\tRoot: type=%d, pointer=%llu, subtreesize=%llu, reduce=%llu bytes\n",
               indexType, pointer, subtreesize, (uint64_t)reduce.size);
        assert((cs_off_t)pointer < headerPos);
        assert((cs_off_t)subtreesize < headerPos);

        // Examine the reduce values in the root node:
        assert(reduce.size >= 5 + 1024/8);
        uint64_t subtreeCount = 0;
        memcpy((uint8_t*)&subtreeCount + 3, reduce.buf, 5);
        subtreeCount = ntohll(subtreeCount);
        printf("\t      SubTreeCount = %llu\n", subtreeCount);
        assert_eq(subtreeCount, 1000);

        printf("\t      Bitmap = <");
        for (int i = 0; i < 128; ++i) {
            printf("%.02x", (uint8_t)reduce.buf[5 + i]);
            if (i % 4 == 3)
                printf(" ");
        }
        printf(">\n");

        if (indexType == COUCHSTORE_VIEW_PRIMARY_INDEX) {
            // JSON reductions:
            assert(reduce.size > 5 + 1024/8 + 2);
            char* jsonReduceStart = reduce.buf + 5 + 1024/8;
            sized_buf jsonReduce = {jsonReduceStart + 2, ntohs(*(uint16_t*)jsonReduceStart)};
            assert(jsonReduce.size < 1000);
            printf("\t      JSONReduction = '%.*s'\n", (int)jsonReduce.size, jsonReduce.buf);

            const char* expectedReduce = "{\"count\":1000,\"max\":99.51,\"min\":0.18,\"sum\":49547.93,\"sumsqr\":3272610.9289}";
            assert_eq(jsonReduce.size, strlen(expectedReduce));
            assert(strncmp(jsonReduce.buf, expectedReduce, strlen(expectedReduce)) == 0);
        }
    }

    assert_eq(ftell(file), eof);
    fclose(file);
}


void TestCouchIndexer(void) {
    fprintf(stderr, "Indexer: ");
    srandom(42);  // to get a consistent sequence of random numbers
    GenerateKVFile(KVPATH, 1000);
    srandom(42);  // to get a consistent sequence of random numbers
    GenerateBackIndexKVFile(KVBACKPATH, 1000);
    IndexKVFile(KVPATH, KVBACKPATH, INDEXPATH, COUCHSTORE_REDUCE_STATS);
    ReadIndexFile(INDEXPATH);
    unlink(KVPATH);
    unlink(INDEXPATH);
    fprintf(stderr, "OK\n");
}