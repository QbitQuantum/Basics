bool Quake3BSP_GL::PointInTriangle(int leafIndex, Vector vPos, Vector planeNorm, float distance)
{
	BSPLeaf *pLeaf = &m_pLeafs[leafIndex];
	int numFaces = pLeaf->numOfLeafFaces;

	// We have the position of the camera which is the origin of our ray.  Get the forward
	// vector of where the camera is looking and scale that out pretty far to get the end
	// point of the ray
	Vector tempPos = tempPos.scalar(-10000.0f, Camera::GetInstance().GetCamForward());

	Vector rayEndpoint = (tempPos + vPos);

	for(int i=0; i < numFaces; ++i){
		int faceIndex = m_pLeafFaces[pLeaf->leafface + i];

		BSPFace *pFace = &m_pFaces[faceIndex];

		// Check if this is a valid face first
		if((pFace->type != FACE_POLYGON))
				continue;

		for(int j=0; j<(pFace->numOfIndices); j+=3){
			// Get the 3 points from the vertex list for this triangle to test
			BSPVertex *pVertexOne = &m_pVerts[pFace->startVertIndex+m_pIndices[pFace->startIndex+j]];
			BSPVertex *pVertexTwo = &m_pVerts[pFace->startVertIndex+m_pIndices[pFace->startIndex+j+1]];
			BSPVertex *pVertexThree = &m_pVerts[pFace->startVertIndex+m_pIndices[pFace->startIndex+j+2]];

			// Now compute the edge vectors of the triangle
			Vector tempVect1 = pVertexTwo->vPosition - pVertexOne->vPosition;
			Vector tempVect2 = pVertexThree->vPosition - pVertexTwo->vPosition;
			Vector tempVect3 = pVertexOne->vPosition - pVertexThree->vPosition;

			// Compute the normal to the plane
			Vector triangleNormal = tempVect1.Cross(tempVect2);
			triangleNormal.normalize();

			// Get the length of the ray
			Vector rayLength = rayEndpoint - vPos;
			float length = rayLength.Length();

			// Compute the D portion of the plane equation Ax + By + Cz + D = 0
			float trianglePlaneD = (triangleNormal.Dot(pVertexOne->vPosition));
			Vector tempNorm = rayEndpoint;
			tempNorm.normalize();

			// Check if the ray is parallel to the plane and would thus never intersect
			float denominator = tempNorm.Dot(triangleNormal);
			if( denominator < 0.0f){
				// Ray parallel to the plane, no chance for intersection
				continue;
			}

			// Compute the possible point of intersection
			float t = ((trianglePlaneD -(vPos.Dot(triangleNormal)))/denominator);
			
			// Test if the point lies on the ray, if so, then test if the point is within the triangle
			if(t>0.0f && t<length){
				Vector testPoint = (vPos + tempNorm.scalar(t,tempNorm));

				Vector firstInner  = testPoint - pVertexOne->vPosition;
				Vector secondInner = testPoint - pVertexTwo->vPosition;
				Vector thirdInner  = testPoint - pVertexThree->vPosition;

				float signOne = triangleNormal.Dot(tempVect1.Cross(firstInner));
				float signTwo = triangleNormal.Dot(tempVect2.Cross(secondInner));
				float signThree = triangleNormal.Dot(tempVect3.Cross(thirdInner));

				if((signOne < 0.0f && signTwo < 0.0f && signThree < 0.0f ) || ( signOne > 0.0f && signTwo > 0.0f && signThree > 0.0f )){
					// if all the signs match, either all positive or all negative, then the point is in the triangle
					// pass back the vertices to the renderer to draw.

					Renderer::GetInstance().SetTriangleVertices(pVertexOne->vPosition - triangleNormal, pVertexTwo->vPosition - triangleNormal, pVertexThree->vPosition - triangleNormal);
					return true;
				} 
			}
		}
	}

	// If we went through all the triangles in all the faces, this leaf was not intersected with, keep searching.
	return false;
}