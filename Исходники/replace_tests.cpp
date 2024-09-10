void ReplaceTests::replaceKeywordsTest() {
    const int itemsToGenerate = 10;
    DECLARE_MODELS_AND_GENERATE(itemsToGenerate);

    QString replaceFrom = "keywordOld";
    QString replaceTo = "keywordNew";
    QString replaceToLower = replaceTo.toLower();

    auto flags = Common::SearchFlags::CaseSensitive |
                Common::SearchFlags::Description |
                Common::SearchFlags::Title |
                Common::SearchFlags::Keywords;

    for (int i = 0; i < itemsToGenerate; i++) {
        Models::ArtworkMetadata *metadata = artItemsModelMock.getArtwork(i);
        metadata->initialize(QString("title"), QString("description"),
                             QStringList() << replaceToLower << "dummyKey" << replaceFrom);
    }

    auto artWorksInfo = filteredItemsModel.getSearchablePreviewOriginalItems(replaceFrom, flags);
    std::shared_ptr<Commands::FindAndReplaceCommand> replaceCommand(
                new Commands::FindAndReplaceCommand(artWorksInfo, replaceFrom, replaceTo, flags));
    auto result = commandManagerMock.processCommand(replaceCommand);

    for (int i = 0; i < itemsToGenerate; i++) {
        Models::ArtworkMetadata *metadata = artItemsModelMock.getArtwork(i);
        QCOMPARE(metadata->getDescription(), QString("description"));
        QCOMPARE(metadata->getTitle(), QString("title"));

        QStringList test = metadata->getKeywords();
        QStringList gold;

        gold << replaceToLower << "dummyKey";
        qSort(gold.begin(), gold.end());
        qSort(test.begin(), test.end());

        QCOMPARE(gold, test);
        QVERIFY(metadata->isModified());
    }
}