//----------------------------------------------------------------------------//
void DefaultResourceProvider::loadRawDataContainer(const String& filename,
                                                   RawDataContainer& output,
                                                   const String& resourceGroup)
{
    if (filename.empty())
        CEGUI_THROW(InvalidRequestException("DefaultResourceProvider::load: "
            "Filename supplied for data loading must be valid"));

    const String final_filename(getFinalFilename(filename, resourceGroup));

#if defined(__WIN32__) || defined(_WIN32)
    FILE* file = _wfopen(Utf8ToUtf16(final_filename.c_str()).c_str(), L"rb");
#else
    FILE* file = fopen(final_filename.c_str(), "rb");
#endif

    if (file == 0)
        CEGUI_THROW(InvalidRequestException("DefaultResourceProvider::load: " +
            final_filename + " does not exist"));

    fseek(file, 0, SEEK_END);
    const long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* const buffer = new unsigned char[size];

    const size_t size_read = fread(buffer, sizeof(char), size, file);
    fclose(file);

    if (size_read != size)
    {
        delete[] buffer;
        CEGUI_THROW(GenericException(
            "DefaultResourceProvider::loadRawDataContainer: "
            "A problem occurred while reading file: " + final_filename));
    }

    output.setData(buffer);
    output.setSize(size);
}