VectorRecord VectorRecord::concatenate(
							const VectorRecord& inLHS,
							const VectorRecord& inRHS,
							MemoryPool* inPool,
							VectorDataManager* inVDM,
							hash_type inVectorHash
							)
	{
	if (!inLHS)
		return inRHS;
	if (!inRHS)
		return inLHS;

	if (!inLHS.isCanonicallySliced())
		return concatenate(
			inLHS.canonicallySliced(inPool, inVDM, inVectorHash + hash_type(0, 1, 0)),
			inRHS,
			inPool,
			inVDM,
			inVectorHash
			);

	if (!inRHS.isCanonicallySliced())
		return concatenate(
			inLHS,
			inRHS.canonicallySliced(inPool, inVDM, inVectorHash + hash_type(0, 2, 0)),
			inPool,
			inVDM,
			inVectorHash
			);

	return VectorRecord(
		VectorHandle::concatenate(
			inLHS.mDataPtr,
			inLHS.mSize,
			inRHS.mDataPtr,
			inRHS.mSize,
			inPool,
			inVDM,
			inVectorHash
			)
		);
	}