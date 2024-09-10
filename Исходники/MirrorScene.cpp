bool copyStaticProperties(PxRigidActor& to, const PxRigidActor& from,NxMirrorScene::MirrorFilter &mirrorFilter)
{
	physx::shdfnd::InlineArray<PxShape*, 64> shapes;
	shapes.resize(from.getNbShapes());

	PxU32 shapeCount = from.getNbShapes();
	from.getShapes(shapes.begin(), shapeCount);

	physx::shdfnd::InlineArray<PxMaterial*, 64> materials;
	for(PxU32 i = 0; i < shapeCount; i++)
	{
		PxShape* s = shapes[i];

		if ( mirrorFilter.shouldMirror(*s) )
		{
			PxU32 materialCount = s->getNbMaterials();
			materials.resize(materialCount);
			s->getMaterials(materials.begin(), materialCount);
			PxShape* shape = to.createShape(s->getGeometry().any(), materials.begin(), static_cast<physx::PxU16>(materialCount));
			shape->setLocalPose( s->getLocalPose());
			shape->setContactOffset(s->getContactOffset());
			shape->setRestOffset(s->getRestOffset());
			shape->setFlags(s->getFlags());
			shape->setSimulationFilterData(s->getSimulationFilterData());
			shape->setQueryFilterData(s->getQueryFilterData());
			mirrorFilter.reviseMirrorShape(*shape);
		}
	}

	to.setActorFlags(from.getActorFlags());
	to.setOwnerClient(from.getOwnerClient());
	to.setDominanceGroup(from.getDominanceGroup());

	if ( to.getNbShapes() )
	{
		mirrorFilter.reviseMirrorActor(to);
	}

	return to.getNbShapes() != 0;
}