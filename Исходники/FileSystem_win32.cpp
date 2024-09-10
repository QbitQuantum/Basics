bool
FileSystem::getFileSize( string path_, File::Size& size_ )
{
    size_ = 0;
    WIN32_FILE_ATTRIBUTE_DATA data;
    if( !GetFileAttributesExA( path_.c_str(), GetFileExInfoStandard, (LPVOID)&data ))
        return true;
    size_ = ((File::Size)data.nFileSizeHigh << 32) | data.nFileSizeLow;
    return false;
}