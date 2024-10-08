int main(int argc, char **argv)
{

  Aria::init();
  ArLog::init(ArLog::StdOut, ArLog::Verbose);

  ArMap testMap;

  ArTime timer;

  ArGlobalFunctor mapChangedCB(&mapChanged);
  testMap.addMapChangedCB(&mapChangedCB);


  if (argc <= 1)
  {
    printf("mapTest: Usage %s <map> <map2:optional>\n", argv[0]);
    Aria::exit(1);
  }

  timer.setToNow();
  if (!testMap.readFile(argv[1]))
  {
    printf("mapTest: Could not read map '%s'\n", argv[1]);
    Aria::exit(2);
  }
  printf("mapTest: Took %ld ms to read file\n", timer.mSecSince());
/*
  printf("mapTest: ChangeTimes (in ms): mapObjects %ld points %ld mapInfo %ld\n",
	 testMap.getMapObjectsChanged().mSecSince(),
	 testMap.getPointsChanged().mSecSince(),
	 testMap.getMapInfoChanged().mSecSince());
*/
  timer.setToNow();
  if(!testMap.writeFile("mapTest.map"))
  {
    printf("mapTest: Error could not write new map to mapTest.map");
    Aria::exit(3);
  }
  printf("mapTest: Took %ld ms to write file mapTest.map\n", timer.mSecSince());

  std::list<ArMapObject *>::iterator objIt;
  ArMapObject *obj;
  for (objIt = testMap.getMapObjects()->begin(); 
       objIt != testMap.getMapObjects()->end(); 
       objIt++)
  {
    obj = (*objIt);
    printf("mapTest: Map object: %s named \"%s\". Pose: %0.2f,%0.2f,%0.2f. ", obj->getType(), obj->getName(), obj->getPose().getX(), obj->getPose().getY(), obj->getPose().getTh());
    if(obj->hasFromTo())
      printf("mapTest: Extents: From %0.2f,%0.2f to %0.2f,%0.2f.", obj->getFromPose().getX(), obj->getFromPose().getY(), obj->getToPose().getX(), obj->getToPose().getY());
    printf("mapTest: \n");

/*
    if (strcasecmp(obj->getType(), "Goal") == 0 ||
	strcasecmp(obj->getType(), "GoalWithHeading") == 0)
    {
      printf("mapTest: Map object: Goal %s\n", obj->getName());
    }
    else if (strcasecmp(obj->getType(), "ForbiddenLine") == 0 &&
	obj->hasFromTo())
    {
      printf("mapTest: Map object: Forbidden line from %.0f %.0f to %.0f %.0f\n",
	     obj->getFromPose().getX(), obj->getFromPose().getY(),
	     obj->getToPose().getX(), obj->getToPose().getY());
    }

*/

  }

  std::list<ArArgumentBuilder*>* objInfo = testMap.getMapInfo();
  for(std::list<ArArgumentBuilder*>::const_iterator i = objInfo->begin();
      i != objInfo->end();
      i++)
  {
    printf("mapTest: MapInfo object definition:\n----\n");
    (*i)->log();
    printf("mapTest: ----\n");
  }

  printf("mapTest: First 5 data points:\n");
  std::vector<ArPose>::iterator pIt;
  ArPose pose;
  int n = 0;
  for (pIt = testMap.getPoints()->begin(); 
       pIt != testMap.getPoints()->end(); 
       pIt++)
  {
    pose = (*pIt);
    if (n > 5)
      exit(0);
    printf("mapTest: \t%.0f %.0f\n", pose.getX(), pose.getY());
    n++;
    // the points are gone through
  }

  if (argc >= 3)
  {
    timer.setToNow();
    if (!testMap.readFile(argv[2]))
    {
      printf("mapTest: Could not read map '%s'\n", argv[2]);
    }
    printf("mapTest: Took %ld ms to read file2\n", timer.mSecSince());
/*
    ArUtil::sleep(30);
    printf("mapTest: ChangeTimes (in ms): mapObjects %ld points %ld mapInfo %ld\n",
	   testMap.getMapObjectsChanged().mSecSince(),
	   testMap.getPointsChanged().mSecSince(),
	   testMap.getMapInfoChanged().mSecSince());
*/
    timer.setToNow();
    testMap.writeFile("mapTest2.map");
    printf("mapTest: Took %ld ms to write file2\n", timer.mSecSince());
  }  

  // now test it with the config stuff
  ArArgumentBuilder builder;
  builder.setExtraString("Map");
  builder.add(argv[1]);
  printf("mapTest: Trying config with map (%s)\n", argv[1]);
  Aria::getConfig()->parseArgument(&builder);
  Aria::getConfig()->callProcessFileCallBacks(true, NULL, 0);
  printf("mapTest: Trying config again with same map (%s)\n", argv[1]);
  Aria::getConfig()->parseArgument(&builder);
  Aria::getConfig()->callProcessFileCallBacks(true, NULL, 0);
  if (argc >= 3)
  {
    ArArgumentBuilder builder2;
    builder2.setExtraString("Map");
    builder2.add(argv[2]);
    printf("mapTest: Trying config with map2 (%s)\n", argv[2]);
    Aria::getConfig()->parseArgument(&builder2);
    Aria::getConfig()->callProcessFileCallBacks(true, NULL, 0);
  }
  
}