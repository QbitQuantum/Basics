TEST(D_FileSystemTest, Folders_Create_2_Ex)
{
	ASSERT_TRUE(DatabasePrepare());

	FoldersNames_vt foldsNames;
	const unsigned char foldsInPack = 3;
	CreateFoldNames(foldsInPack, foldsNames);
	ASSERT_FALSE(foldsNames.empty());

	FolderGuard root;
	ASSERT_NO_THROW(root = cont->GetRoot());
	FolderGuard new_root;
	ASSERT_NO_THROW(new_root = root->CreateFolder("new root"));
	
	ASSERT_NE(new_root.get(), nullptr);
	Folders_vt folds;

	for (int i = 0; i < foldsInPack; ++i)
	{
		ASSERT_NO_THROW(folds.push_back(new_root->CreateFolder(foldsNames[i])));
	}

	EXPECT_NO_THROW(new_root->Rename(non_conflict_name));
	EXPECT_THROW(new_root->Rename(non_conflict_name), ContainerException);
	std::string compared_path(root->Name() + non_conflict_name + dbc::PATH_SEPARATOR + foldsNames[foldsInPack - 1]);
	EXPECT_EQ(compared_path, folds[foldsInPack - 1]->Path());

	ElementGuard ce;
	DbcElementsIterator itr;
	ASSERT_NO_THROW(itr = new_root->EnumFsEntries());
	for (int i = 0; i < foldsInPack; ++i)
	{
		ASSERT_TRUE(itr->HasNext());
		EXPECT_NO_THROW(ce = itr->Next());
		EXPECT_EQ(ce->Name(), foldsNames[i]);
	}
	EXPECT_FALSE(itr->HasNext());
	EXPECT_NO_THROW(itr->Rewind());
	ASSERT_TRUE(itr->HasNext());
}