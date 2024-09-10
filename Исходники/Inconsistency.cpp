// experiments with 0, 10, ..., 100 differential heuristics
// 10% of them are used at each step with and without BPMX
void RunExperiments2(ScenarioLoader *sl)
{
	std::vector<graphState> aPath;
	
	Map *m = new Map(sl->GetNthExperiment(0).GetMapName());
	m->Scale(sl->GetNthExperiment(0).GetXScale(), 
			 sl->GetNthExperiment(0).GetYScale());
	Graph *g = GraphSearchConstants::GetGraph(m);
	
	GraphMapInconsistentHeuristic diffHeuristic(m, g);
	diffHeuristic.SetPlacement(kAvoidPlacement);
	diffHeuristic.SetMode(kRandom);
	
	GraphEnvironment gEnv(g, &diffHeuristic);
	gEnv.SetDirected(true);
	
	TemplateAStar<graphState, graphMove, GraphEnvironment> taNew;
	
	Timer t;
	
	for (int z = 0; z < 1; z++)
	{
		for (int x = 0; x < 10; x++)
			diffHeuristic.AddHeuristic();
		diffHeuristic.SetNumUsedHeuristics(diffHeuristic.GetNumHeuristics()/10);
		
		for (int x = 0; x < sl->GetNumExperiments(); x++)
		{
			Experiment e = sl->GetNthExperiment(x);
			//			if (e.GetBucket() != 127)
			//			{ continue; }
			
			graphState start, goal;
			start = m->GetNodeNum(e.GetStartX(), e.GetStartY());
			goal = m->GetNodeNum(e.GetGoalX(), e.GetGoalY());
			
			//			taNew.SetUseBPMX(false);
			//			Timer t;
			//			t.StartTimer();
			//			taNew.GetPath(&gEnv, start, goal, aPath);
			//			t.EndTimer();
			//			
			//			printf("%d\t%d.%d\t%d\t%f\t\t%f\n", e.GetBucket(), diffHeuristic.GetNumHeuristics(), diffHeuristic.GetNumHeuristics()/10,
			//				   taNew.GetNodesExpanded(), t.GetElapsedTime(), gEnv.GetPathLength(aPath));
			
			for (int y = 1; y < 6; y++)
			{
				if (y == 5)
					taNew.SetUseBPMX(1000);
				else
					taNew.SetUseBPMX(y);
				t.StartTimer();
				taNew.GetPath(&gEnv, start, goal, aPath);
				t.EndTimer();
				
				printf("%d\t%d.%d\t%lld\t%f\tBPMX\t%f\n", e.GetBucket(), diffHeuristic.GetNumHeuristics(), y,
					   taNew.GetNodesExpanded(), t.GetElapsedTime(), gEnv.GetPathLength(aPath));
			}
		}
	}
	exit(0);
}