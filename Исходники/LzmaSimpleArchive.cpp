char *GetFileDataByIdx(SimpleArchive *archive, int idx, Allocator *allocator)
{
    size_t uncompressedSize;

    FileInfo *fi = &archive->files[idx];
    if (!IsFileCrcValid(fi))
        return NULL;

    char *uncompressed = Decompress(fi->compressedData, fi->compressedSize, &uncompressedSize, allocator);
    if (!uncompressed)
        return NULL;

    if (uncompressedSize != fi->uncompressedSize) {
        Allocator::Free(allocator, uncompressed);
        return NULL;
    }
    return uncompressed;
}