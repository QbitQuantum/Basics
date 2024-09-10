ECode CDebug::DoDumpHeap(
    /* [in] */ FILE* fp)
{
    uint8_t* info = NULL;
    size_t overallSize, infoSize, totalMemory, backtraceSize;

    get_malloc_leak_info(&info, &overallSize, &infoSize, &totalMemory,
        &backtraceSize);
    if (info == NULL) {
        fprintf(fp, "Native heap dump not available. To enable, run these"
                    " commands (requires root):\n");
        fprintf(fp, "$ adb shell setprop libc.debug.malloc 1\n");
        fprintf(fp, "$ adb shell stop\n");
        fprintf(fp, "$ adb shell start\n");
        return NOERROR;
    }
    ASSERT_TRUE(infoSize != 0);
    ASSERT_TRUE(overallSize % infoSize == 0);

    fprintf(fp, "Android Native Heap Dump v1.0\n\n");

    size_t recordCount = overallSize / infoSize;
    fprintf(fp, "Total memory: %zu\n", totalMemory);
    fprintf(fp, "Allocation records: %zd\n", recordCount);
    if (backtraceSize != BACKTRACE_SIZE) {
        fprintf(fp, "WARNING: mismatched backtrace sizes (%d vs. %d)\n",
            backtraceSize, BACKTRACE_SIZE);
    }
    fprintf(fp, "\n");

    /* re-sort the entries */
    qsort(info, recordCount, infoSize, CompareHeapRecords);

    /* dump the entries to the file */
    const uint8_t* ptr = info;
    for (size_t idx = 0; idx < recordCount; idx++) {
        size_t size = *(size_t*) ptr;
        size_t allocations = *(size_t*) (ptr + sizeof(size_t));
        intptr_t* backtrace = (intptr_t*) (ptr + sizeof(size_t) * 2);

        fprintf(fp, "z %d  sz %8zu,  num %4zu",
                (size & SIZE_FLAG_ZYGOTE_CHILD) != 0,
                size & ~SIZE_FLAG_ZYGOTE_CHILD,
                allocations);
        for (size_t bt = 0; bt < backtraceSize; bt++) {
            if (backtrace[bt] == 0) {
                break;
            } else {
                fprintf(fp, ", 0x%08x", backtrace[bt]);
            }
        }
        fprintf(fp, "\n");
        ptr += infoSize;
    }
    free_malloc_leak_info(info);
    fprintf(fp, "MAPS\n");
    const char* maps = "/proc/self/maps";
    FILE* in = fopen(maps, "r");
    if (in == NULL) {
        fprintf(fp, "Could not open %s\n", maps);
        return NOERROR;
    }
    char buf[BUFSIZ];
    while (size_t n = fread(buf, sizeof(char), BUFSIZ, in)) {
        fwrite(buf, sizeof(char), n, fp);
    }
    fclose(in);
    fprintf(fp, "END\n");
    return NOERROR;
}