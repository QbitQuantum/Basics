void
test_fiterator()
{
#if defined(_WINDOWS) || defined(WIN32)

    TCHAR winFolder[ MAX_PATH + 1 ];
    if ( GetWindowsDirectory( winFolder, MAX_PATH ) > 0 )
    {
        FileIterator iter( new FileIterImpWin32 );
        FileAttributes fileAttr;
        String fileName;
        String folder = winFolder;

        folder += NTEXT("\\*.dll");

        for (   FileIterator::Status stat = iter.findFirst( folder, fileName, &fileAttr );
                stat == FileIterator::cFound;
                stat = iter.findNext( fileName, &fileAttr ) )
        {
            COUT << fileName.c_str() << ": " << fileAttr.getFileSize() << std::endl;
        }
    }
#else
    FileIterator iter( new FileIterImpUnix );
    FileAttributes fileAttr;
    String fileName;
    String folder = NTEXT("/etc/*.conf");

    for (   FileIterator::Status stat = iter.findFirst( folder, fileName, &fileAttr );
            stat == FileIterator::cFound;
            stat = iter.findNext( fileName, &fileAttr ) )
    {
        COUT << fileName.c_str() << ": " << fileAttr.getFileSize() << std::endl;
    }

#endif
}