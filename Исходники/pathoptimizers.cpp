 ShortcutLinearPlanner(EnvironmentBasePtr penv, std::istream& sinput) : PlannerBase(penv)
 {
     __description = ":Interface Author: Rosen Diankov\n\npath optimizer using linear shortcuts.";
     _linearretimer = RaveCreatePlanner(GetEnv(), "LinearTrajectoryRetimer");
 }