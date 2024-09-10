int WalkabilityMap::getNearestNode(Ogre::Vector3 position)
{
	int nearestNode=-1;
	double minDistance=-1;
	double currentDistance;

	boost::graph_traits<Graph>::vertex_iterator vit,vend;
	for (tie(vit, vend) = vertices(mGraph); vit != vend; ++vit) 
	{
		currentDistance=position.distance(mGraph[*vit].mSceneNode->getPosition());
		if(minDistance==-1 || minDistance>currentDistance)
		{
			minDistance=currentDistance;
			nearestNode=*vit;
		}
	}

	return nearestNode;
}