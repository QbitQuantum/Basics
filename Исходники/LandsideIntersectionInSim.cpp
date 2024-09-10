LandsideVehicleInSim* LandsideIntersectLaneLinkInSim::CheckPathConflict( LandsideVehicleInSim* pVeh, const CPath2008& path,DistanceUnit& minDist )
{
	LandsideVehicleInSim* pConflict = NULL;

	LandsideIntersectionInSim* pIntersection = getIntersection();
	if(pIntersection)
	{
		for(int i=0;i<pIntersection->GetLinkageCount();i++)
		{
			LandsideIntersectLaneLinkInSim* pOtherLink = pIntersection->GetLinkage(i);
			if(pOtherLink==this)
				continue;

			for(int iV = 0; iV < pOtherLink->GetInResVehicleCount();iV++)
			{
				LandsideVehicleInSim* pOtherV = pOtherLink->GetInResVehicle(iV);
				if(pOtherV == pVeh )
					continue;

				if( !pVeh->bCanWaitFor(pOtherV) )
					continue;

				IntersectPathPath2D intersect;
				double dWidth = (pVeh->GetWidth()+pOtherV->GetWidth())*0.5;
				if(intersect.Intersects(path, pOtherV->getSpanPath(),dWidth)>0)
				{
					double dIntserctIndex = intersect.m_vIntersectPtIndexInPath1.front();
					double dOtherInterIndex = intersect.m_vIntersectPtIndexInPath2.front();

					double dist = path.GetIndexDist(dIntserctIndex);
					double dOtherDist = path.GetIndexDist(dOtherInterIndex);
					if(dist < dOtherDist)
						continue;

					if(!pConflict)
					{
						minDist = dist;
						pConflict = pOtherV;
					}
					else if(minDist > dist)
					{
						minDist = dist;
						pConflict = pOtherV;						
					}					
				}
			}
		}
	}		
	return pConflict;
}