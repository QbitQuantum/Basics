	PxShape* AttachShape_AssumesLocked(const PxGeometry& PGeom, const PxTransform& PLocalPose, const float ContactOffset, PxShapeFlags PShapeFlags = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eSIMULATION_SHAPE) const
	{
		const PxMaterial* PMaterial = GetDefaultPhysMaterial(); 
		PxShape* PNewShape = bShapeSharing ? GPhysXSDK->createShape(PGeom, *PMaterial, /*isExclusive =*/ false, PShapeFlags) : PDestActor->createShape(PGeom, *PMaterial, PShapeFlags);

		if (PNewShape)
		{
			PNewShape->setLocalPose(PLocalPose);

			if (NewShapes)
			{
				NewShapes->Add(PNewShape);
			}

			PNewShape->setContactOffset(ContactOffset);

			const bool bSyncFlags = bShapeSharing || SceneType == PST_Sync;
			const FShapeFilterData& Filters = ShapeData.FilterData;
			const bool bComplexShape = PNewShape->getGeometryType() == PxGeometryType::eTRIANGLEMESH;

			PNewShape->setQueryFilterData(bComplexShape ? Filters.QueryComplexFilter : Filters.QuerySimpleFilter);
			PNewShape->setFlags( (bSyncFlags ? ShapeData.SyncShapeFlags : ShapeData.AsyncShapeFlags) | (bComplexShape ? ShapeData.ComplexShapeFlags : ShapeData.SimpleShapeFlags));
			PNewShape->setSimulationFilterData(Filters.SimFilter);
			FBodyInstance::ApplyMaterialToShape_AssumesLocked(PNewShape, SimpleMaterial, ComplexMaterials, bShapeSharing);

			if(bShapeSharing)
			{
				PDestActor->attachShape(*PNewShape);
				PNewShape->release();
			}
		}

		return PNewShape;
	}