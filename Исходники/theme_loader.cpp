bool ThemeLoader::extract( const string &fileName )
{
    bool result = true;
    char *tmpdir = tempnam( NULL, "vlt" );
    string tempPath = sFromLocale( tmpdir );
    free( tmpdir );

    // Extract the file in a temporary directory
    if( ! extractTarGz( fileName, tempPath ) &&
        ! extractZip( fileName, tempPath ) )
    {
        deleteTempFiles( tempPath );
        return false;
    }

    string path;
    string xmlFile;
    OSFactory *pOsFactory = OSFactory::instance( getIntf() );
    // Find the XML file in the theme
    if( findFile( tempPath, DEFAULT_XML_FILE, xmlFile ) )
    {
        path = getFilePath( xmlFile );
    }
    else
    {
        // No XML file, check if it is a winamp2 skin
        string mainBmp;
        if( findFile( tempPath, "main.bmp", mainBmp ) )
        {
            msg_Dbg( getIntf(), "trying to load a winamp2 skin" );
            path = getFilePath( mainBmp );

            // Look for winamp2.xml in the resource path
            list<string> resPath = pOsFactory->getResourcePath();
            list<string>::const_iterator it;
            for( it = resPath.begin(); it != resPath.end(); ++it )
            {
                if( findFile( *it, WINAMP2_XML_FILE, xmlFile ) )
                    break;
            }
        }
    }

    if( !xmlFile.empty() )
    {
        // Parse the XML file
        if (! parse( path, xmlFile ) )
        {
            msg_Err( getIntf(), "error while parsing %s", xmlFile.c_str() );
            result = false;
        }
    }
    else
    {
        msg_Err( getIntf(), "no XML found in theme %s", fileName.c_str() );
        result = false;
    }

    // Clean-up
    deleteTempFiles( tempPath );
    return result;
}