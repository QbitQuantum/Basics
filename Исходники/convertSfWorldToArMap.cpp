int main(int argc, char **argv)
{
  Aria::init();
  char *worldName;
  char *mapName;

  if (argc != 3)
  {
    ArLog::log(ArLog::Normal, "Usage: %s <WorldFile> <MapFile>", argv[0]);
    ArLog::log(ArLog::Normal, "Example: %s columbia.wld columbia.map", argv[0]);
    exit(1);
  }

  worldName = argv[1];
  mapName = argv[2];
  
  FILE *file;
  if ((file = ArUtil::fopen(worldName, "r")) == NULL)
  {
    ArLog::log(ArLog::Normal, "Could not open world file '%s' to convert", worldName);
    exit(1);
  }
  
  char line[10000];
  
  std::vector<ArLineSegment> lines;

  bool haveHome = false;
  ArPose homePose;

  // read until the end of the file
  while (fgets(line, sizeof(line), file) != NULL)
  {
    ArArgumentBuilder builder;
    builder.add(line);

    // Four ints is a line
    if (builder.getArgc() == 4 && builder.isArgInt(0) && 
	builder.isArgInt(1) && builder.isArgInt(2) && 
	builder.isArgInt(3))
    {
      lines.push_back(
	      ArLineSegment(builder.getArgInt(0), builder.getArgInt(1),
			    builder.getArgInt(2), builder.getArgInt(3)));
    }

    // "position X Y Th" becomes a RobotHome
    if( !strcmp(builder.getArg(0), "position") &&
        builder.getArgc() == 4 && builder.isArgInt(1) && 
        builder.isArgInt(2) && builder.isArgInt(3) )
    {
      haveHome = true;
      homePose.setX(builder.getArgInt(1));
      homePose.setY(builder.getArgInt(2));
      homePose.setTh(builder.getArgInt(3));
      printf("Will make a Home point out of start position: ");
      homePose.log();
    }
  }

    
  ArMap armap;
  armap.setLines(&lines);

  ArPose nopose;
  ArMapObject home("RobotHome", homePose, NULL, "ICON", "Home", false, nopose, nopose);
  std::list<ArMapObject*> objects;
  if(haveHome)
  {
    objects.push_back(&home);
    armap.setMapObjects(&objects);
  }

  if (!armap.writeFile(mapName))
  {
    ArLog::log(ArLog::Normal, "Could not save map file '%s'", mapName);
    exit(1);
  }

  ArLog::log(ArLog::Normal, "Converted %s world file to %s map file.", worldName, mapName);
  exit(0);
}