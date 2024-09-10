bool isExtensionManaged(const YString& file)
{
    // Check whether it is a valid jpg file
    String extension;
    IO::ExtractExtension(extension, file, false, false);

    // Only JPG files managed at the moment
    return (extension.toUpper() == "JPG");
}