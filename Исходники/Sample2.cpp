void MyRandomUnitKeyHandler(unsigned long windowID, tKeyboardModifier mod, char)
{
//	if (mod == kShiftDown)
//	{
//		RunWorkMeasureTest();
//		return;
//	}
	Map *m = unitSims[windowID]->GetEnvironment()->GetMap();
	unitSims[windowID]->ClearAllUnits();
	m->SetTileSet(kFast);
//	recording = true;
//	startRecording();

	int x1, y1, x2, y2;
	if (mod == kShiftDown)
	{
		x1 = 0; y1 = 0;
		x2 = m->GetMapWidth()-1;
//		x2 = 0;//m->GetMapWidth()-1;
		y2 = m->GetMapHeight()-1;
	}
	else {
		do {
			x2 = random()%m->GetMapWidth();
			y2 = random()%m->GetMapHeight();
			x1 = random()%m->GetMapWidth();
			y1 = random()%m->GetMapHeight();
		} while ((m->GetTerrainType(x1, y1) != kGround) || (m->GetTerrainType(x2, y2) != kGround));

		do {
			x2 = random()%m->GetMapWidth();
			y2 = random()%m->GetMapHeight();
			x1 = random()%m->GetMapWidth();
			y1 = random()%m->GetMapHeight();
		} while ((m->GetTerrainType(x1, y1) != kGround) || (m->GetTerrainType(x2, y2) != kGround));
	}
	//x1 = 6; y1 = 3; x2 = 15; y2 = 72;
	xySpeedHeading a(x1, y1), b(x2, y2);
	//xySpeedHeading a(0, 0), b(mazeSize-1, mazeSize-1);
	//	xySpeedHeading a(0, 0), b(mazeSize-1, 0);
	a1.GetPath(unitSims[windowID]->GetEnvironment(), a, b, path);
	std::cout << "Found path -- " << a1.GetNodesExpanded() << " nodes expanded; length: " << unitSims[windowID]->GetEnvironment()->GetPathLength(path) << std::endl;
	std::cout << "Solving " << a << " to " << b << std::endl;
	stepsPerFrame = 1.0/120.0;
//	GLdouble a1, b1, c1, r1;
	
//	m->GetOpenGLCoord((x1+x2)/2, (y1+y2)/2, a1, b1, c1, r1);
//	cameraMoveTo(a1, b1, c1-600*r1, 1.0);
//	cameraLookAt(a1, b1, c1, 1.0);

//	measure.MeasureDifficultly(unitSims[windowID]->GetEnvironment(), a, b);
//	measure.ShowHistogram();
	
//	LocalSensing::RIBS<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *u1 = new LocalSensing::RIBS<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(a, b);
//	u1->SetWeight(1.0);
//	u1->SetSpeed(0.02);
//	unitSims[windowID]->AddUnit(u1);

//	LSSLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *u2 = new LSSLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(a, b, new LSSLRTAStar<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(1));
//	u2->SetSpeed(0.02);
//	unitSims[windowID]->AddUnit(u2);

	LSSLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *u2 = new LSSLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(a, b, new LSSLRTAStar<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(10));
	u2->SetSpeed(0.02);
	unitSims[windowID]->AddUnit(u2);
	
//	LSSLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *u3 = new LSSLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(a, b, new LSSLRTAStar<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(10));
//	u3->SetSpeed(0.02);
//	unitSims[windowID]->AddUnit(u3);

//	FLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *u4 = new FLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(a, b, new FLRTA::FLRTAStar<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(10, 1.5));
//	u4->SetSpeed(0.02);
//	unitSims[windowID]->AddUnit(u4);
//
//	FLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *u5 = new FLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(a, b, new FLRTA::FLRTAStar<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(10, 5.5));
//	u5->SetSpeed(0.02);
//	unitSims[windowID]->AddUnit(u5);
//
	FLRTA::FLRTAStar<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *f;
	FLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment> *u6 = new FLRTAStarUnit<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(a, b, f = new FLRTA::FLRTAStar<xySpeedHeading, deltaSpeedHeading, Directional2DEnvironment>(10, 1.5));
	f->SetOrderRedundant(false);
	f->SetUseLocalGCost(true);
	u6->SetSpeed(0.02);
	unitSims[windowID]->AddUnit(u6);
	
	unitSims[windowID]->GetStats()->AddFilter("trialDistanceMoved");
	unitSims[windowID]->GetStats()->AddFilter("TotalLearning");
	unitSims[windowID]->GetStats()->AddFilter("nodesExpanded");
	unitSims[windowID]->GetStats()->EnablePrintOutput(true);
	unitSims[windowID]->SetTrialLimit(50000);

	SetNumPorts(windowID, 1+(unitSims[windowID]->GetNumUnits()-1)%MAXPORTS);
}