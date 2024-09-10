PxVec3 getShapeCenter(PxShape* shape, const PxVec3& localOffset)
{
	PxVec3 offset = localOffset;

	switch(shape->getGeometryType())
	{
		case PxGeometryType::eCONVEXMESH:
		{
			PxConvexMeshGeometry geometry;
			bool status = shape->getConvexMeshGeometry(geometry);
			PX_ASSERT(status);

			PxReal mass;
			PxMat33 localInertia;
			PxVec3 localCenterOfMass;
			geometry.convexMesh->getMassInformation(mass, localInertia, localCenterOfMass);

			offset += localCenterOfMass;
		}
		break;
	}
	const PxTransform pose = PxShapeExt::getGlobalPose(*shape);
	return pose.transform(offset);
}