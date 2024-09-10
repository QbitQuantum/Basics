void ConfigData::ReadFunctionLogConfigData(ConfigParser &parser)
{
  // Get if logging the OpenGL function calls
  const ConfigToken *functionLogToken = parser.GetToken("FunctionLog");
  if(!functionLogToken)
  {
    return;
  }

  //Get if the log is enabled
  const ConfigToken *testToken = functionLogToken->GetChildToken("LogEnabled");
  if(testToken)
  {
    testToken->Get(logEnabled);
  }

  //Get if the log is flushed
  testToken = functionLogToken->GetChildToken("LogFlush");
  if(testToken)
  {
    testToken->Get(logFlush);
  }

  //Get list of additional render calls
  testToken = functionLogToken->GetChildToken("AdditionalRenderCalls");
  if(testToken)
  {
    //Loop for all values
    for(uint i=0; i < testToken->GetNumValues(); i++)
    {
      //Get each function name and add to the array
      string newValue;
      testToken->Get(newValue,i);
      frameAdditionalRenderCalls.push_back(newValue);
    }
  }

  //Get if a maximum number of logging frames has been specified
  testToken = functionLogToken->GetChildToken("LogMaxNumFrames");
  if(testToken)
  {
    logMaxFrameLoggingEnabled = true;
    testToken->Get(logMaxNumLogFrames);
  }

  //Get the log path
  testToken = functionLogToken->GetChildToken("LogPath");
  if(testToken)
  {
    testToken->Get(logPath);

    if(logPath.size() == 0)
    {
      //Assign the dll path as the log path
      logPath = dllPath;
    }
    //If no trailing slash is provided, add one
    //  (Perhaps check that it is a valid path?)
    else if(logPath[logPath.size()-1] != '\\' &&
            logPath[logPath.size()-1] != '/')
    {
      logPath = logPath + FileUtils::dirSeparator;
    }
  }
  else
  {
    //Assign the dll path as the log path
    logPath = dllPath;
  }

  //Get the log file name
  testToken = functionLogToken->GetChildToken("LogFileName");
  if(testToken)
  { 
    testToken->Get(logName);
  }

  //Get if the format is XML or not
  testToken = functionLogToken->GetChildToken("LogFormat");
  if(testToken)
  { 
    //Get an test the string for XML format
    string value;
    if(testToken->Get(value))
    {
      if(value == "XML" || value == "xml")
      {
        logXMLFormat = true;
      }
    }
  }

  //Get the XML format data
  const ConfigToken *xmlFormatToken = functionLogToken->GetChildToken("XMLFormat");
  if(xmlFormatToken)
  {
    //Get the XSL file
    testToken = xmlFormatToken->GetChildToken("XSLFile");
    if(testToken)
    { 
      testToken->Get(logXSLFile);
    }

    //Get the base directory
    testToken = xmlFormatToken->GetChildToken("BaseDir");
    if(testToken)
    { 
      testToken->Get(logXSLBaseDir);

      //Add a trailing seperator
      if(logXSLBaseDir.size() > 0 &&
         logXSLBaseDir[logXSLBaseDir.size()-1] != '\\' &&
         logXSLBaseDir[logXSLBaseDir.size()-1] != '/')
      {
        logXSLBaseDir = logXSLBaseDir + FileUtils::dirSeparator;
      }
    }
  }

}