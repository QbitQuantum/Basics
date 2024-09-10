void FilteredModelTests::removeMetadataDeletesMetadataTest() {
    DECLARE_MODELS_AND_GENERATE(10);

    for (int i = 0; i < 10; ++i) {
        Models::ArtworkMetadata *metadata = artItemsModelMock.getArtwork(i);
        metadata->initialize("title", "description", QStringList() << "keyword1" << "keyword2");
        metadata->setIsSelected(true);
    }

    filteredItemsModel.removeMetadataInSelected();

    for (int i = 0; i < 10; ++i) {
        Mocks::ArtworkMetadataMock *metadata = artItemsModelMock.getMockArtwork(i);
        QVERIFY(metadata->isDescriptionEmpty());
        QVERIFY(metadata->isTitleEmpty());
        QVERIFY(metadata->areKeywordsEmpty());
        QVERIFY(metadata->isModified());
    }
}