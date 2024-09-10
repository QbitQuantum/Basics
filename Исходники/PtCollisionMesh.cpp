void physx::Pt::collideCellsWithStaticMesh(ParticleCollData* collData, const LocalCellHash& localCellHash,
                                           const GeometryUnion& meshShape, const PxTransform& world2Shape,
                                           const PxTransform& shape2World, PxReal /*cellSize*/,
                                           PxReal /*collisionRange*/, PxReal proxRadius, const PxVec3& /*packetCorner*/)
{
	PX_ASSERT(collData);
	PX_ASSERT(localCellHash.isHashValid);
	PX_ASSERT(localCellHash.numParticles <= PT_SUBPACKET_PARTICLE_LIMIT_COLLISION);
	PX_ASSERT(localCellHash.numHashEntries <= PT_LOCAL_HASH_SIZE_MESH_COLLISION);

	const PxTriangleMeshGeometryLL& meshShapeData = meshShape.get<const PxTriangleMeshGeometryLL>();

	const TriangleMesh* meshData = meshShapeData.meshData;
	PX_ASSERT(meshData);

	// mesh bounds in world space (conservative)
	const PxBounds3 shapeBounds =
	    meshData->getLocalBoundsFast().transformSafe(world2Shape.getInverse() * meshShapeData.scale);

	const bool idtScaleMesh = meshShapeData.scale.isIdentity();

	Cm::FastVertex2ShapeScaling meshScaling;
	if(!idtScaleMesh)
		meshScaling.init(meshShapeData.scale);

	// process the particle cells
	for(PxU32 c = 0; c < localCellHash.numHashEntries; c++)
	{
		const ParticleCell& cell = localCellHash.hashEntries[c];

		if(cell.numParticles == PX_INVALID_U32)
			continue;

		PxBounds3 cellBounds;

		cellBounds.setEmpty();
		PxBounds3 cellBoundsNew(PxBounds3::empty());

		PxU32* it = localCellHash.particleIndices + cell.firstParticle;
		const PxU32* end = it + cell.numParticles;
		for(; it != end; it++)
		{
			const ParticleCollData& particle = collData[*it];
			cellBounds.include(particle.oldPos);
			cellBoundsNew.include(particle.newPos);
		}
		PX_ASSERT(!cellBoundsNew.isEmpty());
		cellBoundsNew.fattenFast(proxRadius);
		cellBounds.include(cellBoundsNew);

		if(!cellBounds.intersects(shapeBounds))
			continue; // early out if (inflated) cell doesn't intersect mesh bounds

		// opcode query: cell bounds against shape bounds in unscaled mesh space
		PxcContactCellMeshCallback callback(collData, &(localCellHash.particleIndices[cell.firstParticle]),
		                                    cell.numParticles, *meshData, meshScaling, proxRadius, NULL, shape2World);
		testBoundsMesh(*meshData, world2Shape, meshScaling, idtScaleMesh, cellBounds, callback);
	}
}