bool UPKReader::ReadCompressedHeader()
{
    LogDebug("Reading compressed header...");
    ReadError = UPKReadErrors::NoErrors;
    Compressed = false;
    CompressedChunk = false;
    LastAccessedExportObjIdx = 0;
    UPKStream.seekg(0, std::ios::end);
    size_t Size = UPKStream.tellg();
    UPKStream.seekg(0);
    UPKStream.read(reinterpret_cast<char*>(&CompressedHeader.Signature), 4);
    if (CompressedHeader.Signature != 0x9E2A83C1)
    {
        LogErrorState(UPKReadErrors::BadSignature);
        return false;
    }
    UPKStream.read(reinterpret_cast<char*>(&CompressedHeader.BlockSize), 4);
    UPKStream.read(reinterpret_cast<char*>(&CompressedHeader.CompressedSize), 4);
    UPKStream.read(reinterpret_cast<char*>(&CompressedHeader.UncompressedSize), 4);
    CompressedHeader.NumBlocks = (CompressedHeader.UncompressedSize + CompressedHeader.BlockSize - 1) / CompressedHeader.BlockSize; // Gildor
    uint32_t CompHeadSize = 16 + CompressedHeader.NumBlocks * 8;
    Size -= CompHeadSize; /// actual compressed file size
    if (CompressedHeader.CompressedSize != Size ||
        CompressedHeader.UncompressedSize < Size ||
        CompressedHeader.UncompressedSize < CompressedHeader.CompressedSize)
    {
        LogErrorState(UPKReadErrors::BadVersion);
        return false;
    }
    CompressedHeader.Blocks.clear();
    for (unsigned i = 0; i < CompressedHeader.NumBlocks; ++i)
    {
        FCompressedChunkBlock Block;
        UPKStream.read(reinterpret_cast<char*>(&Block.CompressedSize), 4);
        UPKStream.read(reinterpret_cast<char*>(&Block.UncompressedSize), 4);
        CompressedHeader.Blocks.push_back(Block);
    }
    Compressed = true;
    CompressedChunk = true;
    LogDebug("Package is fully compressed, decompressing...");
    if (!Decompress())
    {
        LogErrorState(UPKReadErrors::IsCompressed);
        return false;
    }
    return true;
}