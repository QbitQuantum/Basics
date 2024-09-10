TEST_F(FileV4Test, CoreRWTest)
{
  PWScore core;
  const StringX passkey(L"3rdMambo");

  fullItem.SetAttUUID(attItem.GetUUID());
  EXPECT_EQ(0U, attItem.GetRefcount());

  core.SetPassKey(passkey);
  core.Execute(AddEntryCommand::Create(&core, fullItem, pws_os::CUUID::NullUUID(), &attItem));
  EXPECT_TRUE(core.HasAtt(attItem.GetUUID()));
  EXPECT_EQ(1U, core.GetAtt(attItem.GetUUID()).GetRefcount());
  EXPECT_EQ(PWSfile::SUCCESS, core.WriteFile(fname.c_str(), PWSfile::V40));

  core.ClearDBData();
  EXPECT_EQ(PWSfile::FAILURE, core.ReadFile(fname.c_str(), L"WrongPassword", true));
  EXPECT_EQ(PWSfile::SUCCESS, core.ReadFile(fname.c_str(), passkey, true));
  ASSERT_EQ(1, core.GetNumEntries());
  ASSERT_EQ(1, core.GetNumAtts());
  ASSERT_TRUE(core.Find(fullItem.GetUUID()) != core.GetEntryEndIter());

  const CItemData readFullItem = core.GetEntry(core.Find(fullItem.GetUUID()));
  EXPECT_TRUE(readFullItem.HasAttRef());
  EXPECT_EQ(attItem.GetUUID(), readFullItem.GetAttUUID());
  EXPECT_EQ(fullItem, readFullItem);
  ASSERT_TRUE(core.HasAtt(attItem.GetUUID()));
  EXPECT_EQ(1U, core.GetAtt(attItem.GetUUID()).GetRefcount());

  core.Execute(DeleteEntryCommand::Create(&core, readFullItem));
  ASSERT_EQ(0, core.GetNumEntries());
  ASSERT_EQ(0, core.GetNumAtts());

  // Get core to delete any existing commands
  core.ClearCommands();
}