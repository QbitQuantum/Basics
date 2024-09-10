bool CScene::load(char *aseFilename)
{
  // remove leading and trailing spaces
//  strrlc(aseFilename); // !!!does nothing because aseFilename isn't directly operated on!!!
//  strrtc(aseFilename); // !!!does nothing because aseFilename isn't directly operated on!!!
  
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

  if( !this->initialized ) init(); // inits the scene

  if( this->convert(fileAndPath) )
  {
    // Load and play the music
    
    mod = NULL; //FMUSIC_LoadSong( "audio/nova.s3m" );
    /*
    if(!mod)
    {
      //error.msg("CLIENT: CScene::Load(): %s", FMOD_ErrorString(FSOUND_GetError()));
	    error.msg( "CLIENT: CScene::Load(): couldn't load song" );
    }
    FMUSIC_PlaySong(mod);
    */
    
    SAFE_DELARY( fileAndPath );
    return true;
  }
  else
  {
    SAFE_DELARY( fileAndPath );
    return false;
  }
}