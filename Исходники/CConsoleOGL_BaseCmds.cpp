bool CConsoleOGL::CmdTrack(char *szCmdParam)
{
  bool goodToGo = true;
  char *allocFileName = new char[ strlen(szCmdParam)+1 ];
  strcpy( allocFileName, szCmdParam );

//-------------------
// Tokenize Path
//-------------------
   
  _strrev( allocFileName );                  // reverse the string

  char *token = strtok(allocFileName, " /\"\0\\"); // search for the first slash or quote

  if(token != NULL)
  {
    _strrev(token);                     // flip the filename around again
                                        //  to get the correct name      
    strcpy(allocFileName, token);         // copy back into the cmdParam, just to make sure
    allocFileName[strlen(allocFileName) + 1] = NULL; // terminate it! to be really sure
  }
  else
  {
    print( 0, "Invalid Filename!" );
    SAFE_DELARY( allocFileName );
    goodToGo = false;
    return false;
  }

//-------------------
// Append new path
//  & extension
//-------------------

  char *fileAndPath = NULL;

  int pathSize = strlen("tracks/") + strlen(allocFileName) + strlen(".ase") + 1;
  fileAndPath = new char[ pathSize ];
  memset(fileAndPath, NULL, pathSize);

  strcpy(fileAndPath, "tracks/");
  strcat(fileAndPath, allocFileName);
  
  // case-insensitive scan for .ASE ending
  if( strncmp(_strrev(_strlwr(fileAndPath)), "esa.", 4) ) // if the extension isn't there
    strcat(_strrev(fileAndPath), ".ase");  // reverse it back and append extension
  else
    _strrev(fileAndPath); // reverse it back anyway
  
 // SAFE_DELARY(allocFileName); // this stopped working all of a sudden!

//-------------------
// Test to see if the
//  file exists
//-------------------

  if( this->client->scene.openFile(fileAndPath) )
      this->client->scene.closeFile();
  else
  {
    print( 0,  "Couldn't open %s", fileAndPath );
    error.msg( "Couldn't open %s", fileAndPath );
    SAFE_DELARY( fileAndPath );
    goodToGo = false;
    return false;
  }
  
  if( goodToGo == true )
  {
    error.msg( "--------------------------------" );
    error.msg( "CLIENT: Attempting to load track %s", szCmdParam, "..." );
    print( 0,  "--------------------------------" );
    print( 0,  "Loading track...");

    // We make sure the new track exists before unloading the old track
    // I think the string parsing and verification should be in here, not in
    // scene.load(filename). That makes everything easier, since the way everything
    // is set up right now we have to essentially run through scene.load twice.
    // Same goes for the ship

    console->splash( 1 ); // turn on the splash screen

    this->client->scene.unload();
    //this->client->player.ship.unload();

    // Load the new
    if( this->client->scene.load(szCmdParam) )
    {
      this->client->player.ship.attachToScene(&this->client->scene); // I think we only have to do this once, in client.init()
      this->client->ai.attachToScene(&this->client->scene);          // same for this
    
      this->client->ai.unload();
      this->client->ai.loadShips();
      this->client->player.ship.reset();

      //this->client->player.ship.load("ships/ship01tc.ase"); // do error checking if loaded ok
      error.msg( "Track loaded successfully" );
      print( 0,  "Track loaded successfully");
    }
    else
    {
      error.msg( "CLIENT: Couldn't load track" );
      print( 0,  "CLIENT: Couldn't load track" );
      return false;
    }
    
    console->splash( 0 ); // turn off the splash screen
  }

  return true;
}