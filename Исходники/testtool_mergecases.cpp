TEST_F(ThreeWayMergeTest, EqualKeySetsWontCauseSync)
{
	unsyncKeys(ours);
	unsyncKeys(theirs);
	unsyncKeys(base);

	MergeResult result = merger.mergeKeySet (base, ours, theirs, ourParent);
	EXPECT_FALSE(result.hasConflicts()) << "Invalid conflict detected";

	KeySet merged = result.getMergedKeys();

	Key current;
	merged.rewind();
	while ((current = merged.next ()))
	{
		EXPECT_FALSE(current.needSync());
	}
}