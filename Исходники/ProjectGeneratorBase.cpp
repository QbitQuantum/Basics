// WriteIfDifferent
//------------------------------------------------------------------------------
/*static*/ bool ProjectGeneratorBase::WriteIfDifferent( const char * generatorId, const AString & content, const AString & fileName )
{
    bool needToWrite = false;

    FileStream old;
    if ( FBuild::Get().GetOptions().m_ForceCleanBuild )
    {
        needToWrite = true;
    }
    else if ( old.Open( fileName.Get(), FileStream::READ_ONLY ) == false )
    {
        needToWrite = true;
    }
    else
    {
        // files differ in size?
        size_t oldFileSize = (size_t)old.GetFileSize();
        if ( oldFileSize != content.GetLength() )
        {
            needToWrite = true;
        }
        else
        {
            // check content
            AutoPtr< char > mem( ( char *)ALLOC( oldFileSize ) );
            if ( old.Read( mem.Get(), oldFileSize ) != oldFileSize )
            {
                FLOG_ERROR( "%s - Failed to read '%s'", generatorId, fileName.Get() );
                return false;
            }

            // compare content
            if ( memcmp( mem.Get(), content.Get(), oldFileSize ) != 0 )
            {
                needToWrite = true;
            }
        }

        // ensure we are closed, so we can open again for write if needed
        old.Close();
    }

    // only save if missing or different
    if ( needToWrite == false )
    {
        return true; // nothing to do.
    }

    FLOG_BUILD( "%s: %s\n", generatorId, fileName.Get() );

    // ensure path exists (normally handled by framework, but Projects
    // are not necessarily a single file)
    if ( Node::EnsurePathExistsForFile( fileName ) == false )
    {
        FLOG_ERROR( "%s - Invalid path for '%s' (error: %u)", generatorId, fileName.Get(), Env::GetLastErr() );
        return false;
    }

    // actually write
    FileStream f;
    if ( !f.Open( fileName.Get(), FileStream::WRITE_ONLY ) )
    {
        FLOG_ERROR( "%s - Failed to open '%s' for write (error: %u)", generatorId, fileName.Get(), Env::GetLastErr() );
        return false;
    }
    if ( f.Write( content.Get(), content.GetLength() ) != content.GetLength() )
    {
        FLOG_ERROR( "%s - Error writing to '%s' (error: %u)", generatorId, fileName.Get(), Env::GetLastErr() );
        return false;
    }
    f.Close();

    return true;
}