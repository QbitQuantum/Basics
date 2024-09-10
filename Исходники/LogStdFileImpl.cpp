int 
StdFileImpl::init( 
    const DOMNode* config, 
    RefCountedPtr<SysContext>& ctx )
{
    int res = -1;
    
    if ( (config != NULL) && (config->getNodeType() == DOMNode::ELEMENT_NODE) )
    {
        const DOMElement* configElem = (const DOMElement*)config;
        
        String val;
        
        // Get the log level setting [optional]
        DOMNodeList* levels = DomUtils::getNodeList( configElem, LOG_LEVEL );
        if ( levels != NULL )
        {
            for ( XMLSize_t i = 0, sz = levels->getLength(); i < sz; i++ )
            {
                if ( DomUtils::getNodeValue( (DOMElement*)levels->item( i ), &val ) )
                {
                    int level = StringUtils::toInt( val );
                    if ( level >= StdLogger::LOGC_ALL )
                    {
                        _logAll = true;
                    }
                    else
                    {
                        _levels.insert( level );
                    }
                }
            }
        }
        
        // get the log file path [required]
        DOMElement* logFileElement = NULL;
        String logFileName;
        if ( DomUtils::selectSingleNode( configElem, FILE_NAME, (DOMNode**)&logFileElement ) )
        {
            if ( DomUtils::getNodeValue( logFileElement, &val ) )
            {	
				RefCountedPtr<SysPathMgr> paths;
				REFCOUNTED_CAST(iSysComponent, SysPathMgr, ctx->getComponent(SysPathMgr::getRegistryName()), paths);
                if ( paths != NULL )
                {
                    logFileName = paths->getPath( val );
                }
                else
                {
                    logFileName = val;
                }

                DOMElement* numFilesElement = NULL;
                DOMElement* sizeFileElement = NULL;

                int numLogs = 0;
                _SizePerLog = 0;
                if ( DomUtils::selectSingleNode( configElem, NUM_FILES, (DOMNode**)&numFilesElement ) )
                {
                    if (DomUtils::getNodeValue( numFilesElement, &val ) )
                    {
                        numLogs = StringUtils::toInt(val);
                    }
                    else 
                    {
                        numLogs = 1;
                    }
                }
                if ( DomUtils::selectSingleNode( configElem, FILE_SIZE, (DOMNode**)&sizeFileElement ) )
                {
                    if (DomUtils::getNodeValue( sizeFileElement, &val ) )
                    {
                        _SizePerLog = StringUtils::toLong(val);
                    }				
                }
                
                if ( (numLogs <= 0) || (_SizePerLog <= 0) )
                {
#ifdef __GNUG__
                    _logFile.open( logFileName.c_str(), std::ios::out | std::ios::app );
#else
                    _logFile.open( logFileName.c_str(), std::ios_base::out | std::ios_base::app );
#endif
                    _logFileNames.push_back( logFileName );
                    _logIndex = 0;
                    _SizePerLog = 0;
                    res = 0;
                }
                else
                {
                    int i;
                    if ( numLogs == 1 )
                    {
                        _logFileNames.push_back( logFileName );
                    }
                    else
                    {
                        for ( i = 1; i <= numLogs; i++ )
                        {
                            _logFileNames.push_back( logFileName + StringUtils::toString(i)+ NTEXT(".txt") );
                        }
                    }

                    FileAttributes fattrs;
                    if ( !FileUtils::getAttributes( _logFileNames[0].c_str(), fattrs ) )
                    {
#ifdef __GNUG__
                        _logFile.open(_logFileNames[0].c_str(), std::ios::out | std::ios::app );
#else
                        _logFile.open(_logFileNames[0].c_str(), std::ios_base::out | std::ios_base::app );
#endif
                        _logIndex = 0;
                        res = 0;
                    }
                    else 
                    {
                        int useindex = 0;
                        struct tm filetime = fattrs.getModifyTime();
                        time_t currtime = ::time(NULL);
                        double besttime = ::difftime( currtime, mktime(&filetime) );
                        for (i = 1; i < numLogs; i++)
                        {
                            if ( FileUtils::getAttributes( _logFileNames[i].c_str(), fattrs ) )
                            {
                                filetime = fattrs.getModifyTime();
                                double thisdiff = ::difftime( currtime, ::mktime(&filetime) );
                                if ( thisdiff < besttime )
                                {
                                    besttime = thisdiff;
                                    useindex = i;
                                }
                            }
                        }

                        FileUtils::getAttributes( _logFileNames[useindex].c_str(), fattrs );
                        if ( (int) fattrs.getFileSize() < _SizePerLog )
                        {
#ifdef __GNUG__
                            _logFile.open(_logFileNames[useindex].c_str(), std::ios::out | std::ios::app );
#else
                            _logFile.open(_logFileNames[useindex].c_str(), std::ios_base::out | std::ios_base::app );
#endif
                            _logIndex = useindex;
                            res = 0;
                        }
                        else
                        {
                            if ( (useindex + 1) >= (int)_logFileNames.size() )
                            {
                                useindex = 0;
                            }
                            else
                            {
                                useindex += 1;
                            }
#ifdef __GNUG__
                            _logFile.open(_logFileNames[useindex].c_str(), std::ios::out | std::ios::trunc );
#else
                            _logFile.open(_logFileNames[useindex].c_str(), std::ios_base::out | std::ios_base::trunc );
#endif
                            _logIndex = useindex;
                            res = 0;
                            
                        }
                    }
                    
                }
            }
        }
    }
    
    return res;
}