bool FArchiveXML::LoadPhysicsShape(FCDObject* object, xmlNode* physicsShapeNode)
{ 
	FCDPhysicsShape* physicsShape = (FCDPhysicsShape*)object;

	bool status = true;
	if (!IsEquivalent(physicsShapeNode->name, DAE_SHAPE_ELEMENT))
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_UNKNOW_PS_LIB_ELEMENT, physicsShapeNode->line);
		return status;
	}

	// Read in the first valid child element found
	for (xmlNode* child = physicsShapeNode->children; child != NULL; child = child->next)
	{
		if (child->type != XML_ELEMENT_NODE) continue;

		if (IsEquivalent(child->name, DAE_HOLLOW_ELEMENT))
		{
			physicsShape->SetHollow(FUStringConversion::ToBoolean(ReadNodeContentDirect(child)));
		}
		else if (IsEquivalent(child->name, DAE_MASS_ELEMENT))
		{
			physicsShape->SetMass(FUStringConversion::ToFloat(ReadNodeContentDirect(child)));
			physicsShape->SetDensityMoreAccurate(false);
		}
		else if (IsEquivalent(child->name, DAE_DENSITY_ELEMENT))
		{
			physicsShape->SetDensity(FUStringConversion::ToFloat(ReadNodeContentDirect(child)));
			physicsShape->SetDensityMoreAccurate(physicsShape->GetMassPointer() == NULL); // mass before density in COLLADA 1.4.1
		}
		else if (IsEquivalent(child->name, DAE_PHYSICS_MATERIAL_ELEMENT))
		{
			FCDPhysicsMaterial* material = physicsShape->AddOwnPhysicsMaterial();
			FArchiveXML::LoadPhysicsMaterial(material, child);
		}
		else if (IsEquivalent(child->name, 
				DAE_INSTANCE_PHYSICS_MATERIAL_ELEMENT))
		{
			physicsShape->SetInstanceMaterial(FCDEntityInstanceFactory::CreateInstance(physicsShape->GetDocument(), NULL, FCDEntity::PHYSICS_MATERIAL));
			FArchiveXML::LoadSwitch(physicsShape->GetInstanceMaterial(),
										&physicsShape->GetInstanceMaterial()->GetObjectType(),
										child);

			if (!HasNodeProperty(child, DAE_URL_ATTRIBUTE))
			{
				//inline definition of physics_material
				FCDPhysicsMaterial* material = physicsShape->AddOwnPhysicsMaterial();
				FArchiveXML::LoadPhysicsMaterial(material, child);
				physicsShape->GetInstanceMaterial()->SetEntity(material);
			}
		}
		else if (IsEquivalent(child->name, DAE_INSTANCE_GEOMETRY_ELEMENT))
		{
			FUUri url = ReadNodeUrl(child);
			if (!url.IsFile())
			{
				FCDGeometry* entity = physicsShape->GetDocument()->FindGeometry(TO_STRING(url.GetFragment()));
				if (entity != NULL)
				{
					physicsShape->SetAnalyticalGeometry(NULL);
					physicsShape->SetGeometryInstance((FCDGeometryInstance*)FCDEntityInstanceFactory::CreateInstance(physicsShape->GetDocument(), NULL, FCDEntity::GEOMETRY));
					physicsShape->GetGeometryInstance()->SetEntity((FCDEntity*)entity);
					status &= (FArchiveXML::LoadGeometryInstance(physicsShape->GetGeometryInstance(), child));
					continue; 
				}
			}
			FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_FCDGEOMETRY_INST_MISSING, child->line);
		}

#define PARSE_ANALYTICAL_SHAPE(type, nodeName) \
		else if (IsEquivalent(child->name, nodeName)) { \
		FCDPhysicsAnalyticalGeometry* analytical = physicsShape->CreateAnalyticalGeometry(FCDPhysicsAnalyticalGeometry::type); \
		status = FArchiveXML::LoadPhysicsAnalyticalGeometry(analytical, child); \
			if (!status) { \
				FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_INVALID_SHAPE_NODE, child->line); break; \
			} }

		PARSE_ANALYTICAL_SHAPE(BOX, DAE_BOX_ELEMENT)
		PARSE_ANALYTICAL_SHAPE(PLANE, DAE_PLANE_ELEMENT)
		PARSE_ANALYTICAL_SHAPE(SPHERE, DAE_SPHERE_ELEMENT)
		PARSE_ANALYTICAL_SHAPE(CYLINDER, DAE_CYLINDER_ELEMENT)
		PARSE_ANALYTICAL_SHAPE(CAPSULE, DAE_CAPSULE_ELEMENT)
		PARSE_ANALYTICAL_SHAPE(TAPERED_CAPSULE, DAE_TAPERED_CAPSULE_ELEMENT)
		PARSE_ANALYTICAL_SHAPE(TAPERED_CYLINDER, DAE_TAPERED_CYLINDER_ELEMENT)
#undef PARSE_ANALYTICAL_SHAPE


		// Parse the physics shape transforms <rotate>, <translate> are supported.
		else if (IsEquivalent(child->name, DAE_ASSET_ELEMENT)) {}
		else if (IsEquivalent(child->name, DAE_EXTRA_ELEMENT)) {}
		else
		{
			uint32 transformType = FArchiveXML::GetTransformType(child);
			if (transformType == FCDTransform::TRANSLATION || transformType == FCDTransform::ROTATION)
			{
				FCDTransform* transform = physicsShape->AddTransform((FCDTransform::Type) transformType);
				status &= (FArchiveXML::LoadSwitch(transform, &transform->GetObjectType(), child));
			}
		}
	}

	if ((physicsShape->GetMassPointer() == NULL) && (physicsShape->GetDensityPointer() == NULL))
	{
		physicsShape->SetDensity(1.0f);
		physicsShape->SetDensityMoreAccurate(true);
	}

	// default value if only one is defined.
	if ((physicsShape->GetMassPointer() == NULL) && (physicsShape->GetDensityPointer() != NULL))
	{
		physicsShape->SetMass(physicsShape->GetDensity() * physicsShape->CalculateVolume());
	}
	else if ((physicsShape->GetMassPointer() != NULL) && (physicsShape->GetDensityPointer() == NULL))
	{
		physicsShape->SetDensity(physicsShape->GetMass() / physicsShape->CalculateVolume());
	}

	physicsShape->SetDirtyFlag();
	return status;
}		