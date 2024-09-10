bool FileFind::FindNext(String &name)
{
#ifdef WIN32
  while ( mInternalFind->bFound )
  {
    mInternalFind->bFound = FindNextFileA(mInternalFind->hFindNext, &mInternalFind->finddata);
    if ( (mInternalFind->finddata.cFileName[0] != '.') && !(mInternalFind->finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
    {


      //gOutput->Display("DIRECTORY ENTRY: %s\n",mInternalFind->finddata.cFileName);

      name = mInternalFind->finddata.cFileName;


  		strlwr((char*)name.c_str());

      if ( mWildCard )
      {
        if ( isMatch(mWildCard,name.c_str()) ) return true;
      }
      else
        return true;
    }
  }
  FindClose(mInternalFind->hFindNext);
#endif

#ifdef LINUX_GENERIC

  if ( mInternalFind->mDir )
  {
    while ( 1 )
    {

      struct direct *di = readdir( mInternalFind->mDir );

      if ( !di )
      {
        closedir( mInternalFind->mDir );
        mInternalFind->mDir = 0;
        return false;
      }

      //gOutput->Display("DIRECTORY ENTRY: %s\n",di->d_name);

      if ( strcmp(di->d_name,".") == 0 || strcmp(di->d_name,"..") == 0 )
      {
        // skip it!
      }
      else
      {
        name = di->d_name;
    		stringutils::strlwr((char*)name.c_str());
        if ( mWildCard )
        {
          if ( mWildCard->Match(name.c_str()) ) return true;
        }
        else
          return true;
      }
    }
  }
#endif

  return false; // finished search.
}