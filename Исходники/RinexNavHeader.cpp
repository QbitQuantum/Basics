 void RinexNavHeader::reallyPutRecord(FFStream& ffs) const 
    throw(std::exception, FFStreamError, StringException)
 {
    RinexNavStream& strm = dynamic_cast<RinexNavStream&>(ffs);
    
    strm.header = (*this);
    
    unsigned long allValid;
    if (version == 2.0)        allValid = allValid20;
    else if (version == 2.1)   allValid = allValid21;
    else if (version == 2.11)  allValid = allValid211;
    else
    {
       FFStreamError err("Unknown RINEX version: " + asString(version,3));
       err.addText("Make sure to set the version correctly.");
       GPSTK_THROW(err);
    }
    
    if ((valid & allValid) != allValid)
    {
       FFStreamError err("Incomplete or invalid header.");
       err.addText("Make sure you set all header valid bits for all of the available data.");
       GPSTK_THROW(err);
    }
    
    string line;
    
    if (valid & versionValid)
    {
       line  = rightJustify(asString(version,3), 10);
       line += string(10, ' ');
       line += string("NAVIGATION"); //leftJustify(fileType, 20);
       line += string(30, ' ');
       line += versionString;
       strm << line << endl;
       strm.lineNumber++;
    }
    if (valid & runByValid) 
    {
       line  = leftJustify(fileProgram,20);
       line += leftJustify(fileAgency,20);
       DayTime dt;
       dt.setLocalTime();
       string dat = dt.printf("%02m/%02d/%04Y %02H:%02M:%02S");
       line += leftJustify(dat, 20);
       line += runByString;
       strm << line << endl;
       strm.lineNumber++;
    }
    if (valid & commentValid)
    {
       vector<string>::const_iterator itr = commentList.begin();
       while (itr != commentList.end())
       {
          line  = leftJustify((*itr), 60);
          line += commentString;
          strm << line << endl;
          strm.lineNumber++;
          itr++;
       }
    }
    if (valid & ionAlphaValid)
    {
       line  = string(2, ' ');
       for (int i = 0; i < 4; i++)
       {
          line += rightJustify(doub2for(ionAlpha[i], 12, 2),12);  // should be 12.4
       }
       line += string(10, ' ');
       line += ionAlphaString;
       strm << line << endl;
       strm.lineNumber++;
    }
    if (valid & ionBetaValid)
    {
       line  = string(2, ' ');
       for (int i = 0; i < 4; i++)
       {
          line += rightJustify(doub2for(ionBeta[i], 12, 2),12);
       }
       line += string(10, ' ');
       line += ionBetaString;
       strm << line << endl;
       strm.lineNumber++;
    }
    if (valid & deltaUTCValid)
    {
       line  = string(3, ' ');
       //line += string(2, ' ');
       line += doub2for(A0, 19, 2);
       line += doub2for(A1, 19, 2);
       line += rightJustify(asString(UTCRefTime),9);
       line += rightJustify(asString(UTCRefWeek),9);               
       line += string(1, ' ');
       line += deltaUTCString;
       strm << line << endl;
       strm.lineNumber++;
    }
    if (valid & leapSecondsValid)
    {
       line  = rightJustify(asString(leapSeconds), 6);
       line += string(54, ' ');
       line += leapSecondsString;
       strm << line << endl;
       strm.lineNumber++;
    }
    if (valid & endValid)
    {
       line  = string(60,' ');
       line += endOfHeader;
       strm << line << endl;
       strm.lineNumber++;
    }
    
 }