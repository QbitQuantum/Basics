void
Consistency::write(Variable &dataVar, std::string& entryID)
{
  // store meta data info
  std::string md;

  getMetaData(dataVar, entryID, md);

  std::string pFile =  projectTableFile.getFile();

  lockFile(pFile);

  // open the file for appending.
  std::fstream oifs;

  oifs.open(pFile.c_str(),
          std::ios::in | std::ios::out );

  if( !oifs) // does not exist
    oifs.open(pFile.c_str(),
          std::ios::out | std::ios::trunc | std::ios::in);

  if (! oifs.is_open() )
  {
    std::string key("8_1");
    if( notes->inq( key, "PT") )
    {
      std::string capt("could not create a consistency-check table") ;

      if( notes->operate(capt) )
      {
        notes->setCheckMetaStr( qa->fail );
        qa->setExit( notes->getExitValue() ) ;
      }
    }
  }
  else
  {
    // append
    oifs.seekp(0, std::ios::end);

    oifs << md << std::flush;
    oifs.close();
  }

  unlockFile(pFile);

  return;
}