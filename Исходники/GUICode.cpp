void SetupMapOverlay()
{
	std::cout << "Doing map overlay from " << start << " to " << goal << "\n";
	counts.resize(0);
	counts.resize(10);
	delete mo;
	mo = new MapOverlay(map);
	me->SetDiagonalCost(1.5);
	forward.SetStopAfterGoal(false);
	backward.SetStopAfterGoal(false);
	std::vector<xyLoc> path;
	forward.GetPath(me, start, goal, path);
	backward.GetPath(me, goal, start, path);
	
	double optimal;
	forward.GetClosedListGCost(goal, optimal);
	for (int x = 0; x < map->GetMapWidth(); x++)
	{
		for (int y = 0; y < map->GetMapHeight(); y++)
		{
			if (map->GetTerrainType(x, y) == kGround)
			{
				xyLoc l(x, y);
				double startDist, goalDist;
				forward.GetClosedListGCost(l, startDist);
				backward.GetClosedListGCost(l, goalDist);
				if (startDist <= optimal/2 && goalDist <= optimal/2)
				{
					counts[NN]++;
					mo->SetOverlayValue(x, y, NN);
				}
				else if (startDist <= optimal/2 && goalDist <= optimal)
				{
					counts[NF]++;
					mo->SetOverlayValue(x, y, NF);
				}
				else if (startDist <= optimal/2)
				{
					counts[NR]++;
					mo->SetOverlayValue(x, y, NR);
				}
				else if (startDist <= optimal && goalDist <= optimal/2)
				{
					counts[FN]++;
					mo->SetOverlayValue(x, y, FN);
				}
				else if (startDist <= optimal && goalDist <= optimal)
				{
					counts[FF]++;
					mo->SetOverlayValue(x, y, FF);
				}
				else if (startDist <= optimal)
				{
					counts[FR]++;
					mo->SetOverlayValue(x, y, FR);
				}
				else if (goalDist <= optimal/2)
				{
					counts[RN]++;
					mo->SetOverlayValue(x, y, RN);
				}
				else if (goalDist <= optimal)
				{
					counts[RF]++;
					mo->SetOverlayValue(x, y, RF);
				}
				else {
					counts[RR]++;
					mo->SetOverlayValue(x, y, RR);
				}
			}
		}
	}
	mo->SetOverlayValue(start.x, start.y, 0);
	mo->SetOverlayValue(start.x, start.y, 10);
	mo->SetOverlayValue(goal.x, goal.y, 10);
	for (int x = 0; x < counts.size(); x++)
	{
		switch (x)
		{
			case 1: printf("NN: %d\n", counts[x]); break;
			case 2: printf("NF: %d\n", counts[x]); break;
			case 3: printf("NR: %d\n", counts[x]); break;
			case 4: printf("FN: %d\n", counts[x]); break;
			case 5: printf("FF: %d\n", counts[x]); break;
			case 6: printf("FR: %d\n", counts[x]); break;
			case 7: printf("RN: %d\n", counts[x]); break;
			case 8: printf("RF: %d\n", counts[x]); break;
			case 9: printf("RR: %d\n", counts[x]); break;
			default: break;
		}
	}
}