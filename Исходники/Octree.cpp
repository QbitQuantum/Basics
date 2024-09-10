void COctree::DrawOctree(COctree *pNode)
{
	// We should already have the octree created before we call this function.
	// This only goes through the nodes that are in our frustum, then renders those
	// vertices stored in their end nodes.  Before we draw a node we check to
	// make sure it is a subdivided node (from m_bSubdivided).  If it is, then
	// we haven't reaches the end and we need to keep recursing through the tree.
	// Once we get to a node that isn't subdivided we draw it's vertices.

	// Make sure a valid node was passed in, otherwise go back to the last node
	if(!pNode) return;


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// Before we do any checks with the current node, let's make sure we even need too.
	// We want to check if this node's cube is even in our frustum first.
	// To do that we pass in our center point of the node and 1/2 it's width to our 
	// CubeInFrustum() function.  This will return "true" if it is inside the frustum 
	// (camera's view), otherwise return false.  
	else if(g_Frustum.CubeInFrustum(pNode->m_vCenter.x, pNode->m_vCenter.y, 
									pNode->m_vCenter.z, pNode->m_Width / 2))

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


	// Check if this node is subdivided. If so, then we need to recurse and draw it's nodes
	if(pNode->IsSubDivided())
	{
		// Recurse to the bottom of these nodes and draw the end node's vertices
		// Like creating the octree, we need to recurse through each of the 8 nodes.
		DrawOctree(pNode->m_pOctreeNodes[TOP_LEFT_FRONT]);
		DrawOctree(pNode->m_pOctreeNodes[TOP_LEFT_BACK]);
		DrawOctree(pNode->m_pOctreeNodes[TOP_RIGHT_BACK]);
		DrawOctree(pNode->m_pOctreeNodes[TOP_RIGHT_FRONT]);
		DrawOctree(pNode->m_pOctreeNodes[BOTTOM_LEFT_FRONT]);
		DrawOctree(pNode->m_pOctreeNodes[BOTTOM_LEFT_BACK]);
		DrawOctree(pNode->m_pOctreeNodes[BOTTOM_RIGHT_BACK]);
		DrawOctree(pNode->m_pOctreeNodes[BOTTOM_RIGHT_FRONT]);
	}
	else
	{
		// Increase the amount of nodes in our viewing frustum (camera's view)
		g_TotalNodesDrawn++;

		// Make sure we have valid vertices assigned to this node
		if(!pNode->m_pVertices) return;

		// Render the world data with triangles
		glBegin(GL_TRIANGLES);

		// Turn the polygons green
		glColor3ub(0, 255, 0);

		// Store the vertices in a local pointer to keep code more clean
		CVector3 *pVertices = pNode->m_pVertices;

		// Go through all of the vertices (the number of triangles * 3)
		for(int i = 0; i < pNode->GetTriangleCount() * 3; i += 3)
		{
			// Before we render the vertices we want to calculate the face normal
			// of the current polygon.  That way when lighting is turned on we can
			// see the definition of the terrain more clearly.  In reality you wouldn't do this.
			
			// Here we get a vector from each side of the triangle
			CVector3 vVector1 = pVertices[i + 1] - pVertices[i];
			CVector3 vVector2 = pVertices[i + 2] - pVertices[i];

			// Then we need to get the cross product of those 2 vectors (The normal's direction)
			CVector3 vNormal = Cross(vVector1, vVector2);

			// Now we normalize the normal so it is a unit vector (length of 1)
			vNormal = Normalize(vNormal);

			// Pass in the normal for this triangle so we can see better depth in the scene
			glNormal3f(vNormal.x, vNormal.y, vNormal.z);

			// Render the first point in the triangle
			glVertex3f(pVertices[i].x, pVertices[i].y, pVertices[i].z);

			// Render the next point in the triangle
			glVertex3f(pVertices[i + 1].x, pVertices[i + 1].y, pVertices[i + 1].z);

			// Render the last point in the triangle to form the current triangle
			glVertex3f(pVertices[i + 2].x, pVertices[i + 2].y, pVertices[i + 2].z);
		}

		// Quit Drawing
		glEnd();
	}
}