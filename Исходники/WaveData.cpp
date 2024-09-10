WaveData* WaveData::Create(CStr filename)
{
    File* file;
    ASSERT(file = File::Open(filename, File::Disposition::OpenExisting, File::Access::AccessRead, File::Flags::ShareRead));

    auto buffer_size = file->GetFileSize();
    auto buffer = Memory::Alloc(buffer_size);

    ASSERT(file->Read(buffer, buffer_size));
    delete file;

    return Create(buffer, buffer_size);
    Memory::Free(buffer);
}