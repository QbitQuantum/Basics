    void shouldAssociateAnArtifactToAProject()
    {
        // GIVEN
        QFETCH(Akonadi::Item, childItem);
        QFETCH(Akonadi::Item, parentItem);
        QFETCH(Domain::Artifact::Ptr, child);
        QFETCH(Domain::Project::Ptr, parent);
        QFETCH(Testlib::AkonadiFakeItemFetchJob*, itemFetchJob1);
        QFETCH(Testlib::AkonadiFakeItemFetchJob*, itemFetchJob2);
        QFETCH(Testlib::AkonadiFakeItemFetchJob*, itemFetchJob3);
        QFETCH(bool, execJob);
        QFETCH(bool, execParentJob);
        QFETCH(Akonadi::Item::List, list);

        // A mock create job
        auto itemModifyJob = new FakeJob(this);
        auto transactionJob = new FakeJob(this);
        auto itemsMoveJob = new FakeJob(this);

        Akonadi::Item::List movedList;
        movedList << childItem << list;

        // Storage mock returning the create job
        Utils::MockObject<Akonadi::StorageInterface> storageMock;
        storageMock(&Akonadi::StorageInterface::fetchItem).when(childItem)
                                                          .thenReturn(itemFetchJob1);
        storageMock(&Akonadi::StorageInterface::fetchItem).when(parentItem)
                                                          .thenReturn(itemFetchJob2);
        if (child.objectCast<Domain::Task>()
         && parentItem.parentCollection().id() != childItem.parentCollection().id()) {
            storageMock(&Akonadi::StorageInterface::fetchItems).when(childItem.parentCollection())
                                                               .thenReturn(itemFetchJob3);
            storageMock(&Akonadi::StorageInterface::createTransaction).when().thenReturn(transactionJob);
            storageMock(&Akonadi::StorageInterface::updateItem).when(childItem, transactionJob)
                                                               .thenReturn(itemModifyJob);
            storageMock(&Akonadi::StorageInterface::moveItems).when(movedList, parentItem.parentCollection(), transactionJob)
                                                              .thenReturn(itemsMoveJob);
        } else {
            storageMock(&Akonadi::StorageInterface::updateItem).when(childItem, Q_NULLPTR)
                                                               .thenReturn(itemModifyJob);
        }

        // Serializer mock returning the item for the task
        Utils::MockObject<Akonadi::SerializerInterface> serializerMock;
        serializerMock(&Akonadi::SerializerInterface::createItemFromTask).when(child.objectCast<Domain::Task>()).thenReturn(childItem);
        serializerMock(&Akonadi::SerializerInterface::createItemFromNote).when(child.objectCast<Domain::Note>()).thenReturn(childItem);
        serializerMock(&Akonadi::SerializerInterface::createItemFromProject).when(parent).thenReturn(parentItem);
        serializerMock(&Akonadi::SerializerInterface::updateItemProject).when(childItem, parent).thenReturn();
        if (execParentJob)
            serializerMock(&Akonadi::SerializerInterface::filterDescendantItems).when(list, childItem).thenReturn(list);

        // WHEN
        QScopedPointer<Akonadi::ProjectRepository> repository(new Akonadi::ProjectRepository(storageMock.getInstance(),
                                                                                             serializerMock.getInstance()));
        auto associateJob = repository->associate(parent, child);
        if (execJob)
            associateJob->exec();

        // THEN
        QVERIFY(storageMock(&Akonadi::StorageInterface::fetchItem).when(childItem).exactly(1));
        if (execJob) {
            QVERIFY(serializerMock(&Akonadi::SerializerInterface::updateItemProject).when(childItem, parent).exactly(1));
            QVERIFY(serializerMock(&Akonadi::SerializerInterface::createItemFromProject).when(parent).exactly(1));
            QVERIFY(storageMock(&Akonadi::StorageInterface::fetchItem).when(parentItem).exactly(1));
            if (execParentJob) {
                if (child.objectCast<Domain::Task>()
                 && parentItem.parentCollection().id() != childItem.parentCollection().id()) {
                    QVERIFY(storageMock(&Akonadi::StorageInterface::fetchItems).when(childItem.parentCollection()).exactly(1));
                    QVERIFY(storageMock(&Akonadi::StorageInterface::createTransaction).when().thenReturn(transactionJob).exactly(1));
                    QVERIFY(storageMock(&Akonadi::StorageInterface::updateItem).when(childItem, transactionJob).exactly(1));
                    QVERIFY(storageMock(&Akonadi::StorageInterface::moveItems).when(movedList, parentItem.parentCollection(), transactionJob).exactly(1));
                } else {
                    QVERIFY(storageMock(&Akonadi::StorageInterface::updateItem).when(childItem, Q_NULLPTR).exactly(1));
                }
            }
        }
    }