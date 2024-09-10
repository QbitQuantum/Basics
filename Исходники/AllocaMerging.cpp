bool AllocaMerging::runOnFunction(Function& F)
{
	cheerp::PointerAnalyzer & PA = getAnalysis<cheerp::PointerAnalyzer>();
	cheerp::Registerize & registerize = getAnalysis<cheerp::Registerize>();
	cheerp::TypeSupport types(*F.getParent());
	AllocaInfos allocaInfos;
	// Gather all the allocas
	for(BasicBlock& BB: F)
		analyzeBlock(registerize, BB, allocaInfos);
	if (allocaInfos.size() < 2)
		return false;
	bool Changed = false;
	BasicBlock& entryBlock=F.getEntryBlock();
	// Look if we can merge allocas of the same type
	for(auto targetCandidate=allocaInfos.begin();targetCandidate!=allocaInfos.end();++targetCandidate)
	{
		AllocaInst* targetAlloca = targetCandidate->first;
		Type* targetType = targetAlloca->getAllocatedType();
		// The range storing the sum of all ranges merged into target
		cheerp::Registerize::LiveRange targetRange(targetCandidate->second);
		// If the range is empty, we have an alloca that we can't analyze
		if (targetRange.empty())
			continue;
		std::vector<AllocaInfos::iterator> mergeSet;
		auto sourceCandidate=targetCandidate;
		++sourceCandidate;
		for(;sourceCandidate!=allocaInfos.end();++sourceCandidate)
		{
			AllocaInst* sourceAlloca = sourceCandidate->first;
			Type* sourceType = sourceAlloca->getAllocatedType();
			// Bail out for non compatible types
			if(!areTypesEquivalent(types, PA, targetType, sourceType))
				continue;
			const cheerp::Registerize::LiveRange& sourceRange = sourceCandidate->second;
			// Bail out if this source candidate is not analyzable
			if(sourceRange.empty())
				continue;
			// Bail out if the allocas interfere
			if(targetRange.doesInterfere(sourceRange))
				continue;
			// Add the range to the target range and the source alloca to the mergeSet
			mergeSet.push_back(sourceCandidate);
			PA.invalidate(sourceAlloca);
			targetRange.merge(sourceRange);
		}

		// If the merge set is empty try another target
		if(mergeSet.empty())
			continue;

		PA.invalidate(targetAlloca);

		if(!Changed)
			registerize.invalidateLiveRangeForAllocas(F);

		// Make sure that this alloca is in the entry block
		if(targetAlloca->getParent()!=&entryBlock)
			targetAlloca->moveBefore(entryBlock.begin());
		// We can merge the allocas
		for(const AllocaInfos::iterator& it: mergeSet)
		{
			AllocaInst* allocaToMerge = it->first;
			Instruction* targetVal=targetAlloca;
			if(targetVal->getType()!=allocaToMerge->getType())
			{
				targetVal=new BitCastInst(targetVal, allocaToMerge->getType());
				targetVal->insertAfter(targetAlloca);
			}
			allocaToMerge->replaceAllUsesWith(targetVal);
			allocaToMerge->eraseFromParent();
			if(targetVal != targetAlloca)
				PA.getPointerKind(targetVal);
			allocaInfos.erase(it);
			NumAllocaMerged++;
		}
		PA.getPointerKind(targetAlloca);
		Changed = true;
	}
	if(Changed)
		registerize.computeLiveRangeForAllocas(F);
	return Changed;
}