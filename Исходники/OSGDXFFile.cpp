/* load interface
 * @todo Evaluate options, see ScanParseSkel...
 * This interface will change due to AMZ modifications
 * @todo Option to trigger cleanup/free of allocated memory? May be faster
 * sometimes when you load many files not to clean up after every file but only
 * after loading all!
 */
NodeTransitPtr DXFFile::load(std::istream &is)
{
	Time startTime = getSystemTime();

	if ( ! _the->_entityTypeHierarchy.empty() )
	{
		FWARNING(("DXFFile::load(): BUG! "
				  "DXF entity structure not completely resolved! "
				  "Unknown entity types will be ignored!\n"));
		for(StringToStringMMap::iterator itr = 
				_the->_entityTypeHierarchy.begin();
			itr != _the->_entityTypeHierarchy.end();
			++ itr)
		{
			FWARNING(("     unresolved: %s <-- %s\n",
					  itr->first.c_str(), itr->second.c_str()
					 ));
		}	
	}

    if(is)
    {
        if(DXFRecord::setStream(is))
        {	
            _the->read( NULL );
        }	
    }
    
#if 0 //TODO: raus!
    if(szFilename != NULL)
    {
        std::string tmpName;

        _pathHandler.setBaseFile(szFilename);

        tmpName = _pathHandler.findFile(szFilename);

        if(tmpName.size() != 0)
        {
			if(DXFRecord::openStream(tmpName.c_str()))
			{	
				_the->read( NULL );
				DXFRecord::closeStream();
			}			
        }
    }
#endif
    
    fprintf(stderr, "Full Time : %lf\n", 
            getSystemTime() - startTime);
	
    NodeTransitPtr returnValue(_rootNodeP);

    _the->cleanup();

	return returnValue;
}