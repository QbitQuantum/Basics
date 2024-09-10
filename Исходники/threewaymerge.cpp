MergeResult ThreeWayMerge::mergeKeySet (const MergeTask & task)
{

	MergeResult result;
	detectConflicts (task, result);
	detectConflicts (task.reverse (), result, true);

	if (!result.hasConflicts ()) return result;


	// TODO: test this behaviour (would probably need mocks)
	Key current;
	KeySet conflicts = result.getConflictSet ();
	conflicts.rewind ();
	while ((current = conflicts.next ()))
	{
		for (auto & elem : strategies)
		{
			(elem)->resolveConflict (task, current, result);

			if (!result.isConflict (current)) break;
		}
	}

	return result;
}