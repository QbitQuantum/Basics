TEST(LocalDatasetTest, AddChildToDiskChunk) {
    typedef LocalDatasetManager::DatasetImpl DatasetImpl;

    LocalDatasetManager manager;
    manager.Initialize("AddChildToDiskShard", 64 * KB);
    DatasetImpl* root = manager.GetDataset("root");
    root->Dump();

    DatasetImpl* father_0 = root->GetChild("0");
    DatasetImpl* father_1 = root->GetChild("1");

    DatasetImpl* childs[] = {
        father_0->GetChild("0"), father_0->GetChild("1"), father_0->GetChild("2"),
        father_1->GetChild("0"), father_1->GetChild("1"), father_1->GetChild("2"),
    };

    father_0->Dump();
    for (size_t i = 0; i < 6; ++i) {
        if (i == 1) {
            childs[i]->Dump();
        }
        EmitTo(boost::lexical_cast<std::string>(i), childs[i]);
    }

    childs[2]->Commit();
    childs[1]->Commit();
    childs[0]->Commit();
    father_0->Commit();

    childs[3]->Commit();
    childs[4]->Commit();
    childs[5]->Commit();
    father_1->Commit();

    root->Commit();

    EXPECT_THAT(ToList(father_1->NewIterator()), ElementsAre("3", "4", "5"));
    EXPECT_THAT(ToList(father_0->NewIterator()), ElementsAre("2", "1", "0"));
    EXPECT_THAT(ToList(root->NewIterator()), ElementsAre("2", "1", "0", "3", "4", "5"));
}