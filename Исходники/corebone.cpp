void CalCoreBone::calculateBoundingBox(CalCoreModel * pCoreModel)
{
   int boneId =  m_pCoreSkeleton->getCoreBoneId(m_strName);
   bool bBoundsComputed=false;
   int planeId;
   
   CalQuaternion rot;
   rot=m_rotationBoneSpace;   
  
   rot.invert();
   
   CalVector dir = CalVector(1.0f,0.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[0].setNormal(dir);

   dir = CalVector(-1.0f,0.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[1].setNormal(dir);

   dir = CalVector(0.0f,1.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[2].setNormal(dir);

   dir = CalVector(0.0f,-1.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[3].setNormal(dir);

   dir = CalVector(0.0f,0.0f,1.0f);
   dir*=rot;
   m_boundingBox.plane[4].setNormal(dir);

   dir = CalVector(0.0f,0.0f,-1.0f);
   dir*=rot;
   m_boundingBox.plane[5].setNormal(dir);
   
   int meshId;
   for(meshId=0; meshId < pCoreModel->getCoreMeshCount(); ++meshId)
   {
       CalCoreMesh * pCoreMesh = pCoreModel->getCoreMesh(meshId);
	   
       int submeshId;
       for(submeshId=0;submeshId<pCoreMesh->getCoreSubmeshCount();submeshId++)
       {
		   CalCoreSubmesh *pCoreSubmesh = pCoreMesh->getCoreSubmesh(submeshId);
		   
		   if(pCoreSubmesh->getSpringCount()==0)
		   {
			   
			   std::vector<CalCoreSubmesh::Vertex>& vectorVertex =  pCoreSubmesh->getVectorVertex();
			   for(size_t vertexId=0;vertexId <vectorVertex.size(); ++vertexId)
			   {
				   for(size_t influenceId=0;influenceId<vectorVertex[vertexId].vectorInfluence.size();++influenceId)
				   {
					   if(vectorVertex[vertexId].vectorInfluence[influenceId].boneId == boneId && vectorVertex[vertexId].vectorInfluence[influenceId].weight > 0.5f)
					   {						   
						   for(planeId = 0; planeId < 6; ++planeId)
						   {
							   if(m_boundingBox.plane[planeId].eval(vectorVertex[vertexId].position) < 0.0f)
							   {
								   m_boundingBox.plane[planeId].setPosition(vectorVertex[vertexId].position);
								   m_boundingPosition[planeId]=vectorVertex[vertexId].position;
								   bBoundsComputed=true;
							   }
						   }
					   }
				   }
			   }	
		   }
	   }
   }

   // To handle bones with no vertices assigned 
   if(!bBoundsComputed) 
   { 
	   for(planeId = 0; planeId < 6; ++planeId) 
	   { 
		   m_boundingBox.plane[planeId].setPosition(m_translation); 
		   m_boundingPosition[planeId] = m_translation; 
	   } 
   } 
   
   m_boundingBoxPrecomputed = true;
}