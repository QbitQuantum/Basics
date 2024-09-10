LOCAL_C void doTestsL()
{
    theRemovedEntries = new(ELeave)CMsvEntrySelection;
    CleanupStack::PushL(theRemovedEntries);


    CMsgsTestUtils::Start(_L("Large selection operations - will be slow"));
    TestMultipleNotifsL();
    CMsgsTestUtils::Complete();

    test.Printf(_L("** Waiting 10s for delayed updating **\n"));
    TestWaitL();

    CMsgsTestUtils::Next(_L("Hidden entry stream"));
    TestHiddenEntryStreamsL();
    CMsgsTestUtils::Complete();

    CMsgsTestUtils::Next(_L("Removing all entries"));
    test.Printf(_L("...and checking for orphan files\n"));
    TestRemovingAllFilesL();
    CMsgsTestUtils::Complete();

    CMsgsTestUtils::Next(_L("Testing Session With Shared RFs "));
    TestSessionWithSharedFsL();
    CMsgsTestUtils::Complete();

    CMsgsTestUtils::Next(_L("Testing Session With Priority Change "));
    TestSessionWithPriorityL();
    CMsgsTestUtils::Complete();

    CleanupStack::PopAndDestroy(); // theRemovedEntries
}