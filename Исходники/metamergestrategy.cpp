void MetaMergeStrategy::resolveConflict(const MergeTask& task, Key& conflictKey, MergeResult& result)
{
	conflictKey.rewindMeta();
	Key currentMeta;

	string baseLookup = rebasePath (conflictKey, task.mergeRoot, task.baseParent);
	string ourLookup = rebasePath (conflictKey, task.mergeRoot, task.ourParent);
	string theirLookup = rebasePath (conflictKey, task.mergeRoot, task.theirParent);

	Key baseKey = task.base.lookup(baseLookup);
	Key ourKey = task.ours.lookup(ourLookup);
	Key theirKey = task.theirs.lookup(theirLookup);

	Key root ("user/", KEY_END);
	KeySet baseMeta = getMetaKeys (baseKey);
	KeySet ourMeta = getMetaKeys (ourKey);
	KeySet theirMeta = getMetaKeys (theirKey);

	MergeTask metaTask(BaseMergeKeys (baseMeta, root), OurMergeKeys (ourMeta, root),
			TheirMergeKeys (theirMeta, root), root);

	MergeResult metaResult = innerMerger.mergeKeySet(metaTask);

	KeySet mergedMeta = metaResult.getMergedKeys();
	Key current;
	mergedMeta.rewind();
	while ((current = mergedMeta.next()))
	{
		string metaName = current.getName().substr(string("user/").length());
		conflictKey.setMeta(metaName, current.getString());
	}

	ConflictOperation ourOperation = getOurConflictOperation(conflictKey);
	ConflictOperation theirOperation = getTheirConflictOperation(conflictKey);

	if (!metaResult.hasConflicts ())
	{
		if (ourOperation == CONFLICT_META && theirOperation == CONFLICT_META)
		{
			// TODO: addConflict deletes the key content
			// without this strategy restoring the value the value would be lost
			// this happens only for CONFLICT_META <--> CONFLICT_META conflicts
			// add a test for this behaviour
			copyKeyValue(ourKey, conflictKey);
			result.resolveConflict (conflictKey);
			result.addMergeKey (conflictKey);
		}
	}

}