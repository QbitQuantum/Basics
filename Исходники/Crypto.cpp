errno_t EasyDecryptInMemory(const string& filename, const string& key, MemoryWriter *writer)
{
    LOGPOS();

    FilePath inFilePath(filename);
    FileReader reader;
    if (reader.Open(inFilePath.value()) != CPT_OK) {
        LOGW("Open file %s failed!", inFilePath.value().c_str());
        return CPT_ERROR;
    }

    uint64_t u64 = 0;
    reader.GetLength(&u64);

    if (writer->Reserve(u64) != CPT_OK) {
        LOGW("MemoryWriter SetLength failed!");
        return CPT_ERROR;
    }

    Decrypt decrypt;
    if (decrypt.SetReader(&reader) != CPT_OK) {
        LOGW("Decrypt set reader failed!");
        return CPT_ERROR;
    }

    if (decrypt.LoadHeader() != CPT_OK) {
        LOGW("Decrypt LoadHeader error");
        return CPT_ERROR;
    }

    if (decrypt.DecryptHeader(key.c_str(), key.length()) == NULL) {
        LOGW("LoadHeader error");
        return CPT_ERROR;
    }

    if (decrypt.SetWriter(writer) != CPT_OK) {
        LOGW("Decrypt set writer failed!");
        return CPT_ERROR;
    }

    int err = decrypt.PreDecrypt();
    ASSERT(err == CPT_OK);

    if (decrypt.DoDecrypt(key.c_str(), key.length())) {
        LOGW("Decrypt decrypt file failed!");
        return CPT_ERROR;
    }

    err = decrypt.PostDecrypt();
    ASSERT(err == CPT_OK);

    return CPT_OK;
}