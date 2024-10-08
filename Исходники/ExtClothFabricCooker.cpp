bool PxFabricCookerImpl::cook(const PxClothMeshDesc& desc, PxVec3 gravity, bool useGeodesicTether)
{	
	if(!desc.isValid())
	{
		shdfnd::getFoundation().error(PxErrorCode::eINVALID_PARAMETER, __FILE__, __LINE__, 
			"PxFabricCookerImpl::cook: desc.isValid() failed!");
		return false;
	}

	gravity = gravity.getNormalized();

	mNumParticles = desc.points.count;

	// assemble points
	shdfnd::Array<PxVec4> particles;
	particles.reserve(mNumParticles);
	PxStrideIterator<const PxVec3> pIt((const PxVec3*)desc.points.data, desc.points.stride);
	PxStrideIterator<const PxReal> wIt((const PxReal*)desc.invMasses.data, desc.invMasses.stride);
	for(PxU32 i=0; i<mNumParticles; ++i)
		particles.pushBack(PxVec4(*pIt++, wIt.ptr() ? *wIt++ : 1.0f));

	// build adjacent vertex list
	shdfnd::Array<PxU32> valency(mNumParticles+1, 0);
	shdfnd::Array<PxU32> adjacencies;
	if(desc.flags & PxMeshFlag::e16_BIT_INDICES)
		gatherAdjacencies<PxU16>(valency, adjacencies, desc.triangles, desc.quads);
	else
		gatherAdjacencies<PxU32>(valency, adjacencies, desc.triangles, desc.quads);

	// build unique neighbors from adjacencies
	shdfnd::Array<PxU32> mark(valency.size(), 0);
	shdfnd::Array<PxU32> neighbors; neighbors.reserve(adjacencies.size());
	for(PxU32 i=1, j=0; i<valency.size(); ++i)
	{
		for(; j<valency[i]; ++j)
		{
			PxU32 k = adjacencies[j];
			if(mark[k] != i)
			{
				mark[k] = i;
				neighbors.pushBack(k);
			}
		}
		valency[i] = neighbors.size();
	}

	// build map of unique edges and classify
	shdfnd::HashMap<Pair, Edge> edges;
	for(PxU32 i=0; i<mNumParticles; ++i)
	{
		PxReal wi = particles[i].w;
		// iterate all neighbors
		PxU32 jlast = valency[i+1];
		for(PxU32 j=valency[i]; j<jlast; ++j)
		{
			// add 1-ring edge
			PxU32 m = neighbors[j];
			if(wi + particles[m].w > 0.0f)
				edges[Pair(PxMin(i, m), PxMax(i, m))].classify();

			// iterate all neighbors of neighbor
			PxU32 klast = valency[m+1];
			for(PxU32 k=valency[m]; k<klast; ++k)
			{
				PxU32 n = neighbors[k];
				if(n != i && wi + particles[n].w > 0.0f)
				{
					// add 2-ring edge
					edges[Pair(PxMin(i, n), PxMax(i, n))].classify(
						particles[i], particles[m], particles[n]);
				}
			}
		}
	}

	// copy classified edges to constraints array
	// build histogram of constraints per vertex
	shdfnd::Array<Entry> constraints; 	
	constraints.reserve(edges.size());
	valency.resize(0); valency.resize(mNumParticles+1, 0);

	const PxReal sqrtHalf = PxSqrt(0.4f);
	for(shdfnd::HashMap<Pair, Edge>::Iterator eIt = edges.getIterator(); !eIt.done(); ++eIt)
	{
		const Edge& edge = eIt->second;
		const Pair& pair = eIt->first;
		if((edge.mStretching + edge.mBending + edge.mShearing) > 0.0f)
		{	
			PxClothFabricPhaseType::Enum type = PxClothFabricPhaseType::eINVALID;
			if(edge.mBending > PxMax(edge.mStretching, edge.mShearing))
				type = PxClothFabricPhaseType::eBENDING;
			else if(edge.mShearing > PxMax(edge.mStretching, edge.mBending))
				type = PxClothFabricPhaseType::eSHEARING;
			else 
			{
				PxVec4 diff = particles[pair.first]-particles[pair.second];
				PxReal dot = gravity.dot(reinterpret_cast<const PxVec3&>(diff).getNormalized());
				type = fabsf(dot) < sqrtHalf ? PxClothFabricPhaseType::eHORIZONTAL : PxClothFabricPhaseType::eVERTICAL;
			}
			++valency[pair.first];
			++valency[pair.second];
			constraints.pushBack(Entry(pair, type));
		}
	} 

	prefixSum(valency.begin(), valency.end(), valency.begin());

	PxU32 numConstraints = constraints.size();

	// build adjacent constraint list
	adjacencies.resize(0); adjacencies.resize(valency.back(), 0);
	for(PxU32 i=0; i<numConstraints; ++i)
	{
		adjacencies[--valency[constraints[i].first.first]] = i;
		adjacencies[--valency[constraints[i].first.second]] = i;
	}
	
	shdfnd::Array<PxU32>::ConstIterator aFirst = adjacencies.begin();
	shdfnd::Array<PxU32> colors(numConstraints, numConstraints); // constraint -> color, initialily not colored
	mark.resize(0); mark.resize(numConstraints+1, PX_MAX_U32); // color -> constraint index
	shdfnd::Array<PxU32> adjColorCount(numConstraints, 0); // # of neighbors that are already colored

	shdfnd::Array<ConstraintGraphColorCount> constraintHeap; 
	constraintHeap.reserve(numConstraints); // set of constraints to color (added in edge distance order)

	// Do graph coloring based on edge distance.
	// For each constraint, we add its uncolored neighbors to the heap
	// ,and we pick the constraint with most colored neighbors from the heap.
	while (1)
	{
		PxU32 constraint = 0;
		while ( (constraint < numConstraints) && (colors[constraint] != numConstraints))
			constraint++; // start with the first uncolored constraint
	
		if (constraint >= numConstraints)
			break;

		constraintHeap.clear();
		pushHeap(constraintHeap, ConstraintGraphColorCount((int)constraint, (int)adjColorCount[constraint]));
		PxClothFabricPhaseType::Enum type = constraints[constraint].second;
		
		while (!constraintHeap.empty())
		{		
			ConstraintGraphColorCount heapItem = popHeap(constraintHeap);
			constraint = heapItem.constraint;
			if (colors[constraint] != numConstraints)
				continue; // skip if already colored 

			const Pair& pair = constraints[constraint].first;			
			for(PxU32 j=0; j<2; ++j)
			{
				PxU32 index = j ? pair.first : pair.second;
				if(particles[index].w == 0.0f)
					continue; // don't mark adjacent particles if attached

				for(shdfnd::Array<PxU32>::ConstIterator aIt = aFirst + valency[index], aEnd = aFirst + valency[index+1]; aIt != aEnd; ++aIt)
				{				
					PxU32 adjacentConstraint = *aIt;
					if ((constraints[adjacentConstraint].second != type) || (adjacentConstraint == constraint))
						continue;

					mark[colors[adjacentConstraint]] = constraint; 
					++adjColorCount[adjacentConstraint];
					pushHeap(constraintHeap, ConstraintGraphColorCount((int)adjacentConstraint, (int)adjColorCount[adjacentConstraint]));
				}
			}

			// find smallest color with matching type
			PxU32 color = 0;
			while((color < mPhases.size() && mPhases[color].phaseType != type) || mark[color] == constraint)
				++color;

			// create a new color set
			if(color == mPhases.size())
			{
				PxClothFabricPhase phase(type, mPhases.size());
				mPhases.pushBack(phase);
				mSets.pushBack(0);
			}

			colors[constraint] = color;
			++mSets[color];
		} 
	}

#if 0 // PX_DEBUG
	printf("set[%u] = ", mSets.size());
	for(PxU32 i=0; i<mSets.size(); ++i)
		printf("%u ", mSets[i]);
#endif

	prefixSum(mSets.begin(), mSets.end(), mSets.begin());

#if 0 // PX_DEBUG
	printf(" = %u\n", mSets.back());
#endif

	// write indices and rest lengths
	// convert mSets to exclusive sum
	PxU32 back = mSets.back();
	mSets.pushBack(back);
	mIndices.resize(numConstraints*2);
	mRestvalues.resize(numConstraints);
	for(PxU32 i=0; i<numConstraints; ++i)
	{
		PxU32 first = constraints[i].first.first;
		PxU32 second = constraints[i].first.second;

		PxU32 index = --mSets[colors[i]];

		mIndices[2*index  ] = first;
		mIndices[2*index+1] = second;

		PxVec4 diff = particles[second] - particles[first];
		mRestvalues[index] = reinterpret_cast<
			const PxVec3&>(diff).magnitude();
	} 
	
	// reorder constraints and rest values for more efficient cache access (linear)
	shdfnd::Array<PxU32> newIndices(mIndices.size());
	shdfnd::Array<PxF32> newRestValues(mRestvalues.size());

	// sort each constraint set in vertex order
	for (PxU32 i=0; i < mSets.size()-1; ++i)
	{
		// create a re-ordering list
		shdfnd::Array<PxU32> reorder(mSets[i+1]-mSets[i]);

		for (PxU32 r=0; r < reorder.size(); ++r)
			reorder[r] = r;

		const PxU32 indicesOffset = mSets[i]*2;
		const PxU32 restOffset = mSets[i];

		ConstraintSorter predicate(&mIndices[indicesOffset]);
		shdfnd::sort(&reorder[0], reorder.size(), predicate);
		
		for (PxU32 r=0; r < reorder.size(); ++r)
		{
			newIndices[indicesOffset + r*2] = mIndices[indicesOffset + reorder[r]*2];
			newIndices[indicesOffset + r*2+1] = mIndices[indicesOffset + reorder[r]*2+1];
			newRestValues[restOffset + r] = mRestvalues[restOffset + reorder[r]];
		}
	}

	mIndices = newIndices;
	mRestvalues = newRestValues;

	PX_ASSERT(mIndices.size() == mRestvalues.size()*2);
	PX_ASSERT(mRestvalues.size() == mSets.back());

#if 0 // PX_DEBUG
	for (PxU32 i = 1; i < mSets.size(); i++)
	{
		PxClothFabricPhase phase = mPhases[i-1];
		printf("%d : type %d, size %d\n", 
			i-1, phase.phaseType, mSets[i] - mSets[i-1]);
	}
#endif

	if (useGeodesicTether)
	{
		PxClothGeodesicTetherCooker tetherCooker(desc);
		if (tetherCooker.getCookerStatus() == 0)
		{
			PxU32 numTethersPerParticle = tetherCooker.getNbTethersPerParticle();
			PxU32 tetherSize = mNumParticles * numTethersPerParticle;
			mTetherAnchors.resize(tetherSize);
			mTetherLengths.resize(tetherSize);
			tetherCooker.getTetherData(mTetherAnchors.begin(), mTetherLengths.begin());
		}
		else
			useGeodesicTether = false;
	}

	if (!useGeodesicTether)
	{
		PxClothSimpleTetherCooker tetherCooker(desc);
		mTetherAnchors.resize(mNumParticles);
		mTetherLengths.resize(mNumParticles);
		tetherCooker.getTetherData(mTetherAnchors.begin(), mTetherLengths.begin());
	}

	return true;
}