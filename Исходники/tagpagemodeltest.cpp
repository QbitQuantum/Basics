    void shouldGetAnErrorMessageWhenRemoveArtifactFailed()
    {
        // GIVEN

        // One domain tag
        auto tag = Domain::Tag::Ptr::create();
        tag->setName("Tag1");

        // Two tasks
        Domain::Artifact::Ptr task1(new Domain::Task);
        task1->setTitle("Task 1");
        Domain::Artifact::Ptr task2(new Domain::Task);
        task2->setTitle("Task 2");
        Domain::Artifact::Ptr note(new Domain::Note);
        note->setTitle("Note 1");

        auto artifactProvider = Domain::QueryResultProvider<Domain::Artifact::Ptr>::Ptr::create();
        auto artifactResult = Domain::QueryResult<Domain::Artifact::Ptr>::create(artifactProvider);
        artifactProvider->append(task1);
        artifactProvider->append(task2);
        artifactProvider->append(note);

        Utils::MockObject<Domain::TagQueries> tagQueriesMock;
        tagQueriesMock(&Domain::TagQueries::findTopLevelArtifacts).when(tag).thenReturn(artifactResult);

        Utils::MockObject<Domain::TagRepository> tagRepositoryMock;
        auto job = new FakeJob(this);
        job->setExpectedError(KJob::KilledJobError, "Foo");
        tagRepositoryMock(&Domain::TagRepository::dissociate).when(tag, task2).thenReturn(job);

        Utils::MockObject<Domain::TaskQueries> taskQueriesMock;
        taskQueriesMock(&Domain::TaskQueries::findChildren).when(task1.dynamicCast<Domain::Task>()).thenReturn(Domain::QueryResult<Domain::Task::Ptr>::Ptr());
        taskQueriesMock(&Domain::TaskQueries::findChildren).when(task2.dynamicCast<Domain::Task>()).thenReturn(Domain::QueryResult<Domain::Task::Ptr>::Ptr());

        Utils::MockObject<Domain::TaskRepository> taskRepositoryMock;
        Utils::MockObject<Domain::NoteRepository> noteRepositoryMock;

        Presentation::TagPageModel page(tag,
                                        tagQueriesMock.getInstance(),
                                        tagRepositoryMock.getInstance(),
                                        taskQueriesMock.getInstance(),
                                        taskRepositoryMock.getInstance(),
                                        noteRepositoryMock.getInstance());
        FakeErrorHandler errorHandler;
        page.setErrorHandler(&errorHandler);

        // WHEN
        const QModelIndex indexTask2 = page.centralListModel()->index(1, 0);
        page.removeItem(indexTask2);

        // THEN
        QTest::qWait(150);
        QCOMPARE(errorHandler.m_message, QString("Cannot remove task Task 2 from tag Tag1: Foo"));

        // WHEN
        auto job2 = new FakeJob(this);
        job->setExpectedError(KJob::KilledJobError, "Foo");
        tagRepositoryMock(&Domain::TagRepository::dissociate).when(tag, note).thenReturn(job2);
        const QModelIndex indexNote = page.centralListModel()->index(2, 0);
        page.removeItem(indexNote);

        // THEN
        QTest::qWait(150);
        QCOMPARE(errorHandler.m_message, QString("Cannot remove note Note 1 from tag Tag1: Foo"));
    }