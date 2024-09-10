// -------------------------------------------------------------------------- //
// Havok Shape - Mesh                                                         //
// -------------------------------------------------------------------------- //
hkRefNew<hkpShape> vHavokShapeFactory::CreateShapeFromMesh(VBaseMesh* pMesh, const hkvVec3& vScale, const char **szShapeCacheId,
                                                           int iCreationFlags, VisWeldingType_e eWeldingType)
{
  VVERIFY_OR_RET_VAL(pMesh != NULL, NULL);

  const bool bAllowStaticMeshCaching = vHavokPhysicsModule_GetDefaultWorldRuntimeSettings().m_bEnableShapeCaching==TRUE;
  const bool bCacheShape = iCreationFlags & VShapeCreationFlags_CACHE_SHAPE;  
  const vHavokPhysicsModule *pModule = vHavokPhysicsModule::GetInstance();
  VASSERT(pModule != NULL);
  const bool bForceHktShapeCaching = pModule->IsHktShapeCachingEnforced();
  
  char szShapeId[512];
  if (bCacheShape)
  {
    VASSERT(szShapeCacheId != NULL);

    // Check whether shape has been already cached for this model with the respective scaling
    vHavokShapeFactory::GetIDStringForMeshShape(szShapeId, pMesh->GetFilename(), vScale, VisStaticMeshInstance_cl::VIS_COLLISION_BEHAVIOR_CUSTOM, eWeldingType);
    hkpShape *pCachedShape = FindShape(szShapeId, szShapeCacheId);
    if (pCachedShape)
    {
      pCachedShape->addReference();
      return pCachedShape;
    }

    // Check if shape is already cached on disk
    if (bAllowStaticMeshCaching )
    {
      pCachedShape = vHavokCachedShape::LoadMeshShape(pMesh, vScale, VisStaticMeshInstance_cl::VIS_COLLISION_BEHAVIOR_CUSTOM, eWeldingType);
      if (pCachedShape)
      {
        *szShapeCacheId = AddShape(szShapeId, pCachedShape);

#ifdef HK_DEBUG_SLOW
        const hkClass* loadedClassType = hkVtableClassRegistry::getInstance().getClassFromVirtualInstance(pCachedShape);
        HK_ASSERT2(0x695cc897, loadedClassType && (hkString::strCmp( loadedClassType->getName(), "hkvBvCompressedMeshShape" ) == 0), "Serialized in a unexpected cached Havok shape type!");
#endif

        hkvBvCompressedMeshShape* pCompressedMeshShape = reinterpret_cast<hkvBvCompressedMeshShape*>(pCachedShape);
        pCompressedMeshShape->SetupMaterials(); // just to be sure we don't try to access it as material ptr ever
        return pCompressedMeshShape;
      }
      else if(!Vision::Editor.IsInEditor() && !bForceHktShapeCaching)
      {
        Vision::Error.Warning("Cached HKT file for %s is missing. Please generate HKT file (see documentation for details).", pMesh->GetFilename());
      }
    }
  }
 
  hkGeometry geom;

  // Get the collision mesh for the specified mesh
  IVCollisionMesh *pColMesh = (iCreationFlags & VShapeCreationFlags_USE_VCOLMESH) ? pMesh->GetCollisionMesh(true, true) : pMesh->GetTraceMesh(true, true);
  VASSERT(pColMesh != NULL);

  hkvMat4 tranform;
  tranform.setScalingMatrix(vScale);

  int iNumColMeshes = hkvMath::Max(pColMesh->GetSubmeshCount(), 1);
  for (int i=0;i<iNumColMeshes;i++)
    BuildGeomFromCollisionMesh(pColMesh, i, tranform, false, geom);
  VVERIFY_OR_RET_VAL(geom.m_vertices.getSize() > 0, NULL);

  ///XX A DynamicMesh can be animated. We are treating it as static here.

  hkpDefaultBvCompressedMeshShapeCinfo ci( &geom );
  ci.m_collisionFilterInfoMode = hkpBvCompressedMeshShape::PER_PRIMITIVE_DATA_NONE; // Collision info
  ci.m_userDataMode = hkpBvCompressedMeshShape::PER_PRIMITIVE_DATA_NONE; // Materials
  ci.m_weldingType = vHavokConversionUtils::VisToHkWeldingType(eWeldingType);
  hkvBvCompressedMeshShape* pCompressedMeshShape = new hkvBvCompressedMeshShape(ci, pColMesh->GetFileTime());

  if (pCompressedMeshShape->getNumChildShapes() <= 0)
  {
    pCompressedMeshShape->removeReference();

    const char *szMeshFilename = (pMesh->GetFilename() != NULL) ? pMesh->GetFilename() : "UnnamedMesh";
    Vision::Error.Warning("Physics Shape for [%s] is empty. Volume too small?",  szMeshFilename);
    return NULL;
  }
  
  if (bCacheShape)
    *szShapeCacheId = AddShape(szShapeId, pCompressedMeshShape);

  // Only cache shape to HKT file when inside vForge or when enforced.
  if ((Vision::Editor.IsInEditor() && bAllowStaticMeshCaching && bCacheShape) || bForceHktShapeCaching)   
    vHavokCachedShape::SaveMeshShape(pMesh, vScale, VisStaticMeshInstance_cl::VIS_COLLISION_BEHAVIOR_CUSTOM, eWeldingType, pCompressedMeshShape);

  return pCompressedMeshShape;
}