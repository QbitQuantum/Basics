OctreeSDF::Node* OctreeSDF::subtract(Node* node, const SolidGeometry& implicitSDF, const Area& area)
{
	bool needsSubdivision = implicitSDF.cubeNeedsSubdivision(area);
	if (node->getNodeType() == Node::INNER && needsSubdivision)
	{
		InnerNode* innerNode = (InnerNode*)node;
		Area subAreas[8];
		area.getSubAreas(subAreas);
		for (int i = 0; i < 8; i++)
			innerNode->m_Children[i] = subtract(innerNode->m_Children[i], implicitSDF, subAreas[i]);
		return node;
	}
	if (!needsSubdivision)
	{
		if (implicitSDF.getSample(area.getCornerVecs(0).second).signedDistance < 0)
			return node;
		delete node;
		Node* newNode = createNode(area, implicitSDF);
		newNode->invert();
		return newNode;
	}
	if (node->getNodeType() == Node::EMPTY)
	{
		EmptyNode* emptyNode = (EmptyNode*)node;
		if (emptyNode->m_CornerSamples[0].signedDistance < 0)
			return node;
		delete node;
		Node* newNode = createNode(area, implicitSDF);
		newNode->invert();
		return newNode;

	}

	GridNode* gridNode = (GridNode*)node;
	GridNode otherGridNode(area, implicitSDF);
	for (int i = 0; i < LEAF_SIZE_3D; i++)
	{
		if (-otherGridNode.m_Samples[i].signedDistance < gridNode->m_Samples[i].signedDistance)
		{
			gridNode->m_Samples[i] = otherGridNode.m_Samples[i];
			gridNode->m_Samples[i].signedDistance *= -1.0f;
		}
	}
	return node;
}