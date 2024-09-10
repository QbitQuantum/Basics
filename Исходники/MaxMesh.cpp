CVertexCandidate *CMaxMesh::GetVertexCandidate(CSkeletonCandidate *pSkeletonCandidate, int faceId, int faceVertexId)
{
    // check for valid mesh and physique modifier
    if((m_pIMesh == 0))
    {
        theExporter.SetLastError("Invalid handle.", __FILE__, __LINE__);
        return 0;
    }

    // check if face id is valid
    if((faceId < 0) || (faceId >= m_pIMesh->getNumFaces()))
    {
        theExporter.SetLastError("Invalid face id found.", __FILE__, __LINE__);
        return 0;
    }

    // check if face vertex id is valid
    if((faceVertexId < 0) || (faceVertexId >= 3))
    {
        theExporter.SetLastError("Invalid face vertex id found.", __FILE__, __LINE__);
        return 0;
    }

    // allocate a new vertex candidate
    CVertexCandidate *pVertexCandidate;
    pVertexCandidate = new CVertexCandidate();
    if(pVertexCandidate == 0)
    {
        theExporter.SetLastError("Memory allocation failed.", __FILE__, __LINE__);
        return 0;
    }

    // create the new vertex candidate
    if(!pVertexCandidate->Create())
    {
        delete pVertexCandidate;
        return 0;
    }

    // get vertex id
    int vertexId;
    vertexId = m_pIMesh->faces[faceId].v[faceVertexId];

    // get the absolute vertex position
    Point3 vertex;
    vertex = m_pIMesh->getVert(vertexId) * m_tm;

    // set the vertex candidate position
    pVertexCandidate->SetPosition(vertex.x, vertex.y, vertex.z);
    pVertexCandidate->SetUniqueId(vertexId);

    // get the absolute vertex normal
    Point3 normal;
    normal = GetVertexNormal(faceId, vertexId);
    normal = normal * Inverse(Transpose(m_tm));
    normal = normal.Normalize();

    // set the vertex candidate normal
    pVertexCandidate->SetNormal(normal.x, normal.y, normal.z);
 
  if(m_pIMesh->numCVerts > 0)
  { 
        VertColor vc;
        vc = m_pIMesh->vertCol[m_pIMesh->vcFace[faceId].t[faceVertexId]];
    CalVector vcCal(vc.x, vc.y, vc.z);
    pVertexCandidate->SetVertColor(vcCal);
  }  
 
    // get the vertex weight array
    float *pVertexWeights;
    pVertexWeights = m_pIMesh->getVertexWeights();
  //if( pVertexWeights == NULL ) {
    //    delete pVertexCandidate;
    //    theExporter.SetLastError("Mesh has no vertex weights", __FILE__, __LINE__);
    //    return 0;
  //}

    // get the vertex weight (if possible)
    float weight;
    if(pVertexWeights != 0)
    {
        weight = pVertexWeights[vertexId];
    }
    else
    {
        weight = 0.0f;
    }

    // another 3ds max weird behaviour:
    // zero out epsilon weights
    if(weight < 0.0005f) weight = 0.0f;

    // set the vertex candidate weight
    pVertexCandidate->SetPhysicalProperty(weight);

    // get the material id of the face
    int materialId;
    materialId = GetFaceMaterialId(faceId);

    if((materialId < 0) || (materialId >= (int)m_vectorStdMat.size()))
    {
        delete pVertexCandidate;
        theExporter.SetLastError("Invalid material id found.", __FILE__, __LINE__);
        return 0;
    }

    // get the material of the face
    StdMat *pStdMat;
    pStdMat = m_vectorStdMat[materialId];

    // loop through all the mapping channels and extract texture coordinates
    int mapId;
    for(mapId = 0; mapId < pStdMat->NumSubTexmaps(); mapId++)
    {
        // get texture map
        Texmap *pTexMap;
        pTexMap = pStdMat->GetSubTexmap(mapId);

        // check if map is valid
        if((pTexMap != 0) && (pStdMat->MapEnabled(mapId)))
        {
            // get the mapping channel
            int channel;
            channel = pTexMap->GetMapChannel();

            bool bValidUV;
            bValidUV = false;

            // extract the texture coordinate
            UVVert uvVert;
            if(m_pIMesh->mapSupport(channel))
            {
                TVFace *pTVFace;
                pTVFace = m_pIMesh->mapFaces(channel);

                UVVert *pUVVert;
                pUVVert = m_pIMesh->mapVerts(channel);

                uvVert = pUVVert[pTVFace[faceId].t[faceVertexId]];
                bValidUV = true;
            }
            else if(m_pIMesh->numTVerts > 0)
            {
                uvVert = m_pIMesh->tVerts[m_pIMesh->tvFace[faceId].t[faceVertexId]];
                bValidUV = true;
            }

            // if we found valid texture coordinates, add them to the vertex candidate
            if(bValidUV)
            {
                // apply a possible uv generator
                StdUVGen *pStdUVGen;
                pStdUVGen = (StdUVGen *)pTexMap->GetTheUVGen();
                if(pStdUVGen != 0)
                {
                    Matrix3 tmUV;
                    pStdUVGen->GetUVTransform(tmUV);
                    uvVert = uvVert * tmUV;
                }

                // add texture coordinate to the vertex candidate, inverting the y coordinate
                pVertexCandidate->AddTextureCoordinate(uvVert.x, 1.0f - uvVert.y);
            }
        }
    }

    // check for physique modifier
    if(m_modifierType == MODIFIER_PHYSIQUE)
    {
        // create a physique export interface
        IPhysiqueExport *pPhysiqueExport;
        pPhysiqueExport = (IPhysiqueExport *)m_pModifier->GetInterface(I_PHYINTERFACE);
        if(pPhysiqueExport == 0)
        {
            delete pVertexCandidate;
            theExporter.SetLastError("Physique modifier interface not found.", __FILE__, __LINE__);
            return 0;
        }

        // create a context export interface
        IPhyContextExport *pContextExport;
        pContextExport = (IPhyContextExport *)pPhysiqueExport->GetContextInterface(m_pINode);
        if(pContextExport == 0)
        {
            m_pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);
            delete pVertexCandidate;
            theExporter.SetLastError("Context export interface not found.", __FILE__, __LINE__);
            return 0;
        }

        // set the flags in the context export interface
        pContextExport->ConvertToRigid(TRUE);
        pContextExport->AllowBlending(TRUE);

        // get the vertex export interface
        IPhyVertexExport *pVertexExport;
        pVertexExport = (IPhyVertexExport *)pContextExport->GetVertexInterface(vertexId);
        if(pVertexExport == 0)
        {
            pPhysiqueExport->ReleaseContextInterface(pContextExport);
            m_pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);
            delete pVertexCandidate;
            theExporter.SetLastError("Vertex export interface not found.", __FILE__, __LINE__);
            return 0;
        }

        // get the vertex type
        int vertexType;
        vertexType = pVertexExport->GetVertexType();

        // handle the specific vertex type
        if(vertexType == RIGID_TYPE)
        {
            // typecast to rigid vertex
            IPhyRigidVertex *pTypeVertex;
            pTypeVertex = (IPhyRigidVertex *)pVertexExport;

                // add the influence to the vertex candidate
            // get the influencing bone
            if(!AddBoneInfluence(pSkeletonCandidate, pVertexCandidate, pTypeVertex->GetNode(), 1.0f))
            {
                pPhysiqueExport->ReleaseContextInterface(pContextExport);
                m_pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);
                delete pVertexCandidate;
                theExporter.SetLastError("Invalid bone assignment.", __FILE__, __LINE__);
                return 0;
            }
        }
        else if(vertexType == RIGID_BLENDED_TYPE)
        {
            // typecast to blended vertex
            IPhyBlendedRigidVertex *pTypeVertex;
            pTypeVertex = (IPhyBlendedRigidVertex *)pVertexExport;

            // loop through all influencing bones
            int nodeId;
            for(nodeId = 0; nodeId < pTypeVertex->GetNumberNodes(); nodeId++)
            {
                // add the influence to the vertex candidate
                if(!AddBoneInfluence(pSkeletonCandidate, pVertexCandidate, pTypeVertex->GetNode(nodeId), pTypeVertex->GetWeight(nodeId)))
                {
                    pPhysiqueExport->ReleaseContextInterface(pContextExport);
                    m_pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);
                    delete pVertexCandidate;
                    theExporter.SetLastError("Invalid bone assignment.", __FILE__, __LINE__);
                    return 0;
                }
            }
        }

        // release all interfaces
        pPhysiqueExport->ReleaseContextInterface(pContextExport);
        m_pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);
    }
#if MAX_RELEASE >= 4000
    // check for skin modifier
    else if(m_modifierType == MODIFIER_SKIN)
    {
        // create a skin interface
        ISkin *pSkin;
        pSkin = (ISkin*)m_pModifier->GetInterface(I_SKIN);
        if(pSkin == 0)
        {
            delete pVertexCandidate;
            theExporter.SetLastError("Skin modifier interface not found.", __FILE__, __LINE__);
            return 0;
        }

        // create a skin context data interface
        ISkinContextData *pSkinContextData;
        pSkinContextData = (ISkinContextData *)pSkin->GetContextInterface(m_pINode);
        if(pSkinContextData == 0)
        {
            m_pModifier->ReleaseInterface(I_SKIN, pSkin);
            delete pVertexCandidate;
            theExporter.SetLastError("Skin context data interface not found.", __FILE__, __LINE__);
            return 0;
        }

        // loop through all influencing bones
        int nodeId;
        for(nodeId = 0; nodeId < pSkinContextData->GetNumAssignedBones(vertexId); nodeId++)
        {
            // get the bone id
            int boneId;
            boneId = pSkinContextData->GetAssignedBone(vertexId, nodeId);
            if(boneId < 0) continue;

            // add the influence to the vertex candidate
            if(!AddBoneInfluence(pSkeletonCandidate, pVertexCandidate, pSkin->GetBone(boneId), pSkinContextData->GetBoneWeight(vertexId, nodeId)))
            {
                m_pModifier->ReleaseInterface(I_SKIN, pSkin);
                delete pVertexCandidate;
                theExporter.SetLastError("Invalid bone assignment.", __FILE__, __LINE__);
                return 0;
            }
        }

        // release all interfaces
        m_pModifier->ReleaseInterface(I_SKIN, pSkin);
    }
#endif
        else if( m_modifierType == MODIFIER_MORPHER || m_modifierType == MODIFIER_NONE ) {
        }
        else 
    {
          theExporter.SetLastError("No physique/skin/morpher modifier found.", __FILE__, __LINE__);
          return 0;
    }

    return pVertexCandidate;
}