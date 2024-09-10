    void shouldStoreDefaultSourceInTheSettings()
    {
        // GIVEN

        // A value in the settings
        auto &settings = Akonadi::StorageSettings::instance();
        settings.setDefaultNoteCollection(Akonadi::Collection(21));

        // The new default data source we want
        auto source = Domain::DataSource::Ptr::create();

        // A collection corresponding to the data source
        Akonadi::Collection col(42);

        // Storage mock sitting here doing nothing
        Utils::MockObject<Akonadi::StorageInterface> storageMock;

        // Serializer mock returning the collection for the source
        Utils::MockObject<Akonadi::SerializerInterface> serializerMock;
        serializerMock(&Akonadi::SerializerInterface::createCollectionFromDataSource).when(source).thenReturn(col);

        // WHEN
        QScopedPointer<Akonadi::NoteRepository> repository(new Akonadi::NoteRepository(storageMock.getInstance(),
                                                                                       serializerMock.getInstance()));
        repository->setDefaultSource(source);

        // THEN
        QCOMPARE(settings.defaultNoteCollection(), col);
        QVERIFY(serializerMock(&Akonadi::SerializerInterface::createCollectionFromDataSource).when(source).exactly(1));
    }