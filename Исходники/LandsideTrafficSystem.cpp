//-----------------------------------------------------------------------
//Summary:
//		find shortest path from entry point to exit point
//Parameters:
//		entryPos[in]: start point
//		pStartResource[in]: start landside traffic object
//		exitPos[in]: end point
//		pEndResource[in]: end landside traffic object
//		_shortestPath[out]: shortest path from start to end
//Return:
//		true: find the path
//		false: failed
//-----------------------------------------------------------------------
bool CLandsideGraph::getShortestPath( const CPoint2008& entryPos,LandsideResourceInSim* pStartLandsideResource,CLandsideWalkTrafficObjectInSim* pStartResource,const CPoint2008& exitPos,LandsideResourceInSim* pEndLandsideResource,CLandsideWalkTrafficObjectInSim* pEndResource,LandsideTrafficGraphVertexList& _shortestPath )
{
	CPoint2008 startPos;
	CPoint2008 endPos;
	if (pStartResource->GetShortestProjectPoint(pStartLandsideResource,entryPos,startPos) && pEndResource->GetShortestProjectPoint(pEndLandsideResource,exitPos,endPos))
	{
		LandsideTrafficGraphVertex startVertex, endVertex;

		pStartResource->GetWalkwayVertex(startVertex,startPos);
		pEndResource->GetWalkwayVertex(endVertex,endPos);

		LandsideTrafficGraphVertex entryVertex1, entryVertex2, exitVertex1, exitVertex2;
		pStartResource->GetNearestVertex(startPos, entryVertex1, entryVertex2);
		pEndResource->GetNearestVertex(endPos, exitVertex1, exitVertex2);

		LandsideTrafficGraphVertexList path[4];
		findShortestPath(entryVertex1, exitVertex1, path[0]);
		findShortestPath(entryVertex1, exitVertex2, path[1]);
		findShortestPath(entryVertex2, exitVertex1, path[2]);
		findShortestPath(entryVertex2, exitVertex2, path[3]);

		double exDistance[4];
		exDistance[0] = startPos.distance(entryVertex1.GetPointDist()) + endPos.distance(exitVertex1.GetPointDist());
		exDistance[1] = startPos.distance(entryVertex1.GetPointDist()) + endPos.distance(exitVertex2.GetPointDist());
		exDistance[2] = startPos.distance(entryVertex2.GetPointDist()) + endPos.distance(exitVertex1.GetPointDist());
		exDistance[3] = startPos.distance(entryVertex2.GetPointDist()) + endPos.distance(exitVertex2.GetPointDist());

		int shortestIndex = 0;
		for (int i = 1; i < 4; i++)
		{
			if (GetLength(path[i]) + exDistance[i] < GetLength(path[shortestIndex]) + exDistance[shortestIndex])
			{
				shortestIndex = i;
			}
		}

		_shortestPath = path[shortestIndex];
	
		_shortestPath.insert(_shortestPath.begin(), startVertex);
		_shortestPath.push_back(endVertex);
	}
	// add the source point and dest point
	LandsideTrafficGraphVertex sourceVertex;
	sourceVertex.SetPoint(entryPos);

	LandsideTrafficGraphVertex destVertex;
	destVertex.SetPoint(exitPos);

	_shortestPath.push_back(destVertex);
	_shortestPath.insert(_shortestPath.begin(), sourceVertex);
	return true;
}