//---------------------------------------------------------------------------
// Func: CShip::load(char *aseFilename)
// Rtrn: 0 if failed, 1 if succeeded
// Note: The ship MUST be attached to the scene. This is done by setting
//       the CShip::scene pointer to the current scene. For example:
//
//         CScene scene;
//         CPlayer player;
//         player.ship.attachToScene(&scene); // must be done first!!!!
//         if(!player.load("ships/ship01tc.ase")) { error } else { success }
//
//---------------------------------------------------------------------------
bool CShip::load(char *aseFilename)
{ 

//-------------------
// No Scene?
//   Don't Pass Go,
//   Don't collect $200
//-------------------

  if( scene == NULL )
  {
    error.msg("ERROR: Ship not associated with a scene! (CShip::load())");
    return false;
  }

//-------------------
// Perpare Raw Str
//-------------------

  // remove leading and trailing spaces
  strrlc(aseFilename); // !!!does nothing because aseFilename isn't directly operated on!!!
  strrtc(aseFilename); // !!!does nothing because aseFilename isn't directly operated on!!!

  char *allocFileName = new char[ strlen(aseFilename)+1 ];
  strcpy( allocFileName, aseFilename );

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
    //console->print( 0, "Invalid Filename!" );
    return false;
  }

//-------------------
// Append new path
//  & extension
//-------------------

  char *fileAndPath = NULL;

  int pathSize = strlen("ships/") + strlen(allocFileName) + strlen(".ase") + 1;
  fileAndPath = new char[ pathSize ];
  memset(fileAndPath, NULL, pathSize);
  
  strcpy(fileAndPath, "ships/");
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

  if( this->openFile(fileAndPath) )
    this->closeFile();
  else
  {
    //console->print( 0, "Couldn't open %s", fileAndPath );
    error.msg( "Couldn't open %s", fileAndPath );
    SAFE_DELARY( fileAndPath );
    return false;
  }

//-------------------
// Do the loading
//-------------------

  if( !this->initialized )
    init(); // inits the scene

  if( !this->convert(fileAndPath) )
  {
    SAFE_DELARY( fileAndPath );
    return false;
  }
  else
  {
    SAFE_DELARY( fileAndPath );
  }

  return true;
}