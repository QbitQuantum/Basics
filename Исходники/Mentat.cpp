void Mentat::onFrame()
{

	if (analyzed)
	{
		//we will iterate through all the base locations, and draw their outlines.
		for( set<BWTA::BaseLocation*>::const_iterator i = BWTA::getBaseLocations().begin(); i != BWTA::getBaseLocations().end(); i++)
		{
			TilePosition p = (*i)->getTilePosition();
			Position base = (*i)->getPosition();

			//draw outline of center location
			Broodwar->drawBox(CoordinateType::Map,p.x() * 32, p.y() * 32, p.x() * 32 + 4 * 32, p.y() * 32 + 3 * 32, Colors::Blue, false);

			//draw a circle at each mineral patch
			for( set<BWAPI::Unit*>::const_iterator j = (*i)->getStaticMinerals().begin(); j != (*i)->getStaticMinerals().end(); j++)
			{
				Position mineral = (*j)->getInitialPosition();
				Broodwar->drawCircle(CoordinateType::Map, mineral.x(), mineral.y(), 30, Colors::Cyan, false);
			}

			//draw the outlines of vespene geysers
			for( set<BWAPI::Unit*>::const_iterator j = (*i)->getGeysers().begin(); j != (*i)->getGeysers().end(); j++)
			{
				TilePosition vespene = (*j)->getInitialTilePosition();
				Broodwar->drawBox(CoordinateType::Map,vespene.x() * 32, vespene.y() * 32, vespene.x() * 32 + 4 * 32, vespene.y() * 32 + 2 * 32, Colors::Orange, false);
			}

			//if this is an island expansion, draw a yellow circle around the base location
			if ( (*i)->isIsland() )
			{
				Broodwar->drawCircle(CoordinateType::Map, base.x(), base.y(), 80, Colors::Yellow, false);
			}
		}

		//we will iterate through all the regions and draw the polygon outline of it in green.
		for( set<BWTA::Region*>::const_iterator i = BWTA::getRegions().begin(); i != BWTA::getRegions().end(); i++)
		{
			BWTA::Polygon region = (*i)->getPolygon();
			for( int j = 0; j<(int)region.size(); j++ )
			{
				Position point1 = region[j];
				Position point2 = region[(j + 1) % region.size()];
				Broodwar->drawLine(CoordinateType::Map, point1.x(), point1.y(), point2.x(), point2.y(), Colors::Green);
			}
		}

		//we will visualize the chokepoints with red lines
		for( set<BWTA::Region*>::const_iterator i = BWTA::getRegions().begin(); i != BWTA::getRegions().end(); i++)
		{
			for( set<BWTA::Chokepoint*>::const_iterator j = (*i)->getChokepoints().begin(); j != (*i)->getChokepoints().end(); j++)
			{
				Position point1 = (*j)->getSides().first;
				Position point2 = (*j)->getSides().second;
				Broodwar->drawLine(CoordinateType::Map, point1.x(), point1.y(), point2.x(), point2.y(), Colors::Red);
			}
		}
	}
	if (analysis_just_finished)
	{
		Broodwar->printf("Finished analyzing map.");
		analysis_just_finished = false;
	}
}