void IntersectionNodesInAirport::GetIntersectionNodes( Stand * pStand , Taxiway * pTaxiway,std::vector<IntersectionNode>& reslts )
{
	//lead in lines
	const CPath2008& taxiPath = pTaxiway->GetPath();

	for(int i=0;i< (int)pStand->m_vLeadInLines.GetItemCount();i++)
	{
		StandLeadInLine& leadInLine = pStand->GetLeadInLineList().ItemAt(i);
		const CPath2008& instandpath = leadInLine.getPath();
		IntersectPathPath2D intersectPath;
		int intersectCountIn = intersectPath.Intersects(instandpath, taxiPath,5);

		for(int j =0 ; j< intersectCountIn;j++)
		{
			double dPos1 = instandpath.GetIndexDist(intersectPath.m_vIntersectPtIndexInPath1.at(j));
			double dPos2 = taxiPath.GetIndexDist(intersectPath.m_vIntersectPtIndexInPath2.at(j));
			CPoint2008 pos = instandpath.GetDistPoint(dPos1);
			IntersectionNode newNode;

			StandLeadInLineIntersectItem standLeadInItem;
			TaxiwayIntersectItem taxiItem;

			standLeadInItem.SetStand(pStand);
			standLeadInItem.SetLeadInLineID(leadInLine.GetID());
			standLeadInItem.SetDistInItem(dPos1);

			taxiItem.SetTaxiway(pTaxiway);
			taxiItem.SetDistInItem(dPos2);

			newNode.AddItem(&taxiItem);
			newNode.AddItem(&standLeadInItem);
			newNode.SetPosition(pos);

			reslts.push_back(newNode);
			//				
		}
	}

	for(int i=0;i<(int)pStand->m_vLeadOutLines.GetItemCount();i++)
	{
		StandLeadOutLine& leadOutLine = pStand->GetLeadOutLineList().ItemAt(i);
		const CPath2008& outstandPath = leadOutLine.getPath();

		IntersectPathPath2D intersectPath;
		int intersectCountOut = intersectPath.Intersects(outstandPath,taxiPath,5);

		for(int j =0 ; j< intersectCountOut;j++)
		{
			double dPos1 = outstandPath.GetIndexDist(intersectPath.m_vIntersectPtIndexInPath1.at(j));
			double dPos2 = taxiPath.GetIndexDist(intersectPath.m_vIntersectPtIndexInPath2.at(j));
			CPoint2008 pos = outstandPath.GetDistPoint(dPos1);
			IntersectionNode newNode;

			TaxiwayIntersectItem taxiItem;
			StandLeadOutLineIntersectItem standOutItem;

			standOutItem.SetStand(pStand);
			standOutItem.SetLeadOutLineID(leadOutLine.GetID());
			standOutItem.SetDistInItem(dPos1);

			taxiItem.SetTaxiway(pTaxiway);
			taxiItem.SetDistInItem(dPos2);

			newNode.AddItem(&taxiItem);
			newNode.AddItem(&standOutItem);			
			newNode.SetPosition(pos);

			reslts.push_back(newNode);
		}
	}	

}