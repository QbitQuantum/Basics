void
FileOperationMetaTest::testFileOperationSubCreateTruncate(
        auto_ptr<MetaManager> & meta,
        const fs::path & path,
        auto_ptr<FileOperationInterface> & oper,
        const fs::path & fileMeta,
        const fs::path & fileEntity,
        const string & tapeName)
{
    string tape;
    auto_ptr<Inode> inode;
    char buffer[1024] = "hello,world!\n";
    char bufferRead[sizeof(buffer)];
    size_t size;
    struct stat stat;

    CPPUNIT_ASSERT( ! fs::exists(fileMeta) );
    CPPUNIT_ASSERT( ! fs::exists(fileEntity) );

    errno = 0;
    CPPUNIT_ASSERT( false == oper->GetStat(stat) );
    CPPUNIT_ASSERT_ERRNO_( ENOENT == errno);
    errno = 0;
    CPPUNIT_ASSERT( false == oper->Read(0,bufferRead,sizeof(bufferRead),size) );
    CPPUNIT_ASSERT_ERRNO_( EBADF == errno);
    errno = 0;
    CPPUNIT_ASSERT( false == oper->Write(0,buffer,sizeof(buffer),size) );
    CPPUNIT_ASSERT_ERRNO_( EBADF == errno);
    CPPUNIT_ASSERT( ! fs::exists(fileMeta) );
    CPPUNIT_ASSERT( ! fs::exists(fileEntity) );

    errno = 0;
    CPPUNIT_ASSERT( false == oper->OpenFile(O_RDWR) );
    CPPUNIT_ASSERT_ERRNO_( ENOENT == errno);
    CPPUNIT_ASSERT( ! fs::exists(fileMeta) );
    CPPUNIT_ASSERT( ! fs::exists(fileEntity) );

    CPPUNIT_ASSERT( true == oper->CreateFile(O_RDWR,0644,false) );
    CPPUNIT_ASSERT( fs::exists(fileMeta) );
    CPPUNIT_ASSERT_MESSAGE( fileEntity.file_string(), fs::exists(fileEntity) );
    inode.reset(meta->GetInode(path));
    errno = 0;
    CPPUNIT_ASSERT( false == oper->CreateFile(O_RDWR,0644,false) );
    CPPUNIT_ASSERT_ERRNO_( EEXIST == errno);

    tape.clear();
    CPPUNIT_ASSERT( true == oper->GetTape(tape) );
    CPPUNIT_ASSERT( tapeName == tape );
    tape.clear();
    CPPUNIT_ASSERT( true == inode->GetTape(tape) );
    CPPUNIT_ASSERT( tapeName == tape );

    CPPUNIT_ASSERT( true == oper->Write(0,buffer,sizeof(buffer),size) );
    CPPUNIT_ASSERT( fs::exists(fileMeta) );
    CPPUNIT_ASSERT( fs::exists(fileEntity) );
    CPPUNIT_ASSERT( true == oper->GetStat(stat) );
    CPPUNIT_ASSERT( sizeof(buffer) == stat.st_size );
    CPPUNIT_ASSERT( true == oper->Truncate( sizeof(buffer) - 5 ) );
    CPPUNIT_ASSERT( true == oper->GetStat(stat) );
    CPPUNIT_ASSERT( sizeof(buffer) - 5 == stat.st_size );
    CPPUNIT_ASSERT( true == oper->Truncate( sizeof(buffer) + 5 ) );
    CPPUNIT_ASSERT( true == oper->GetStat(stat) );
    CPPUNIT_ASSERT( sizeof(buffer) + 5 == stat.st_size );
    CPPUNIT_ASSERT( true == oper->Truncate( sizeof(buffer) ) );
    CPPUNIT_ASSERT( true == oper->GetStat(stat) );
    CPPUNIT_ASSERT( sizeof(buffer) == stat.st_size );

    tape.clear();
    CPPUNIT_ASSERT( true == oper->GetTape(tape) );
    CPPUNIT_ASSERT( tapeName == tape );
    tape.clear();
    CPPUNIT_ASSERT( true == inode->GetTape(tape) );
    CPPUNIT_ASSERT( tape == tapeName );
}