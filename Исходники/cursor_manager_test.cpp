/**
 * Tests that invalidating a cursor while it is in use will deregister it from the cursor manager,
 * transferring ownership to the pinned cursor.
 */
TEST_F(CursorManagerTest, InvalidatePinnedCursor) {
    CursorManager* cursorManager = useCursorManager();

    auto cursorPin = cursorManager->registerCursor(
        _opCtx.get(), {makeFakePlanExecutor(), kTestNss, {}, false, BSONObj()});

    // If the cursor is pinned, it sticks around, even after invalidation.
    ASSERT_EQUALS(1U, cursorManager->numCursors());
    const std::string invalidateReason("InvalidatePinned Test");
    cursorManager->invalidateAll(_opCtx.get(), false, invalidateReason);
    ASSERT_EQUALS(0U, cursorManager->numCursors());

    // The invalidation should have killed the plan executor.
    BSONObj objOut;
    ASSERT_EQUALS(PlanExecutor::DEAD, cursorPin.getCursor()->getExecutor()->getNext(&objOut, NULL));
    ASSERT(WorkingSetCommon::isValidStatusMemberObject(objOut));
    const Status status = WorkingSetCommon::getMemberObjectStatus(objOut);
    ASSERT(status.reason().find(invalidateReason) != std::string::npos);

    cursorPin.release();
    ASSERT_EQUALS(0U, cursorManager->numCursors());
}