TEST(FileSystemIterator, subSubDirs)
{
    TestDirectory rootDir(File("foobarfolder"));
    TestDirectoryPtr subDir1 = rootDir.addDirectory("subdir1");
    TestDirectoryPtr subDir2 = rootDir.addDirectory("subdir2");
    TestDirectoryPtr subDir3 = rootDir.addDirectory("subdir3");

    subDir1->addDirectory("sub1subdir1")->addFile("sub1subdir1file1")->addFile("sub1subdir1file2");
    subDir1->addDirectory("sub1subdir2")->addFile("sub1subdir2file1")->addFile("sub1subdir2file2");
    subDir1->addDirectory("sub1subdir3")->addFile("sub1subdir3file1")->addFile("sub1subdir3file2");

    subDir2->addDirectory("sub2subdir1")->addFile("sub2subdir1file1")->addFile("sub2subdir1file2");
    subDir2->addDirectory("sub2subdir2")->addFile("sub2subdir2file1")->addFile("sub2subdir2file2");
    subDir2->addDirectory("sub2subdir3")->addFile("sub2subdir3file1")->addFile("sub2subdir3file2");

    subDir3->addDirectory("sub3subdir1")->addFile("sub3subdir1file1")->addFile("sub3subdir1file2");
    subDir3->addDirectory("sub3subdir2")->addFile("sub3subdir2file1")->addFile("sub3subdir2file2");
    subDir3->addDirectory("sub3subdir3")->addFile("sub3subdir3file1")->addFile("sub3subdir3file2");


    HashSet<String> filenames;
    filenames.put("subdir1");
    filenames.put("subdir2");
    filenames.put("subdir3");
    filenames.put("sub1subdir1");
    filenames.put("sub1subdir2");
    filenames.put("sub1subdir3");
    filenames.put("sub2subdir1");
    filenames.put("sub2subdir2");
    filenames.put("sub2subdir3");
    filenames.put("sub3subdir1");
    filenames.put("sub3subdir2");
    filenames.put("sub3subdir3");
    filenames.put("sub1subdir1file1");
    filenames.put("sub1subdir2file1");
    filenames.put("sub1subdir3file1");
    filenames.put("sub2subdir1file1");
    filenames.put("sub2subdir2file1");
    filenames.put("sub2subdir3file1");
    filenames.put("sub3subdir1file1");
    filenames.put("sub3subdir2file1");
    filenames.put("sub3subdir3file1");
    filenames.put("sub1subdir1file2");
    filenames.put("sub1subdir2file2");
    filenames.put("sub1subdir3file2");
    filenames.put("sub2subdir1file2");
    filenames.put("sub2subdir2file2");
    filenames.put("sub2subdir3file2");
    filenames.put("sub3subdir1file2");
    filenames.put("sub3subdir2file2");
    filenames.put("sub3subdir3file2");

    FileSystemIterator iter(rootDir.getFile());
    while (iter.isValid())
    {
        EXPECT_TRUE(filenames.hasElement(iter->getFileName()));
        EXPECT_EQ(CAPU_OK, filenames.remove(iter->getFileName()));
        iter.next();
    }
    EXPECT_EQ(0u, filenames.count());

}