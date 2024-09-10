// TestMSVC_ShowIncludesWithWarnings
//------------------------------------------------------------------------------
void TestIncludeParser::TestMSVC_ShowIncludesWithWarnings() const
{
    FBuild fb; // needed for CleanPath

    FileStream f;
    TEST_ASSERT( f.Open( "Data/TestIncludeParser/MSVC-ShowIncludes/WithWarnings.output", FileStream::READ_ONLY) )
    const size_t fileSize = (size_t)f.GetFileSize();
    AutoPtr< char > mem( (char *)ALLOC( fileSize + 1 ) );
    TEST_ASSERT( f.Read( mem.Get(), fileSize ) == fileSize );
    mem.Get()[ fileSize ] = 0;

    CIncludeParser parser;
    TEST_ASSERT( parser.ParseMSCL_Output( mem.Get(), fileSize ) );

    // check number of includes found to prevent future regressions
    const Array< AString > & includes = parser.GetIncludes();
    TEST_ASSERT( includes.GetSize() == 0 );
#ifdef DEBUG
    TEST_ASSERT( parser.GetNonUniqueCount() == 0 );
#endif
}