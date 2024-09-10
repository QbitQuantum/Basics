   void RinexMetHeader::reallyPutRecord(FFStream& ffs) const
      throw(std::exception, FFStreamError,
            gpstk::StringUtils::StringException)
   {
      RinexMetStream& strm = dynamic_cast<RinexMetStream&>(ffs);
      
         // since they want to output this header, let's store
         // it internally for use by the data
      strm.header = (*this);
      
         // i'm casting out const here to set the correct required valid bits.
         // deal with it =P
	 

      unsigned long allValid;
      if (version == 2.0)        allValid = allValid20;
      else if (version == 2.1)   allValid = allValid21;
      else
      {
         FFStreamError err("Unknown RINEX version: " + asString(version,2));
         err.addText("Make sure to set the version correctly.");
         GPSTK_THROW(err);
      }
      
      if ((valid & allValid) != allValid)
      {
         string errstr("Incomplete or invalid header: missing: ");
         errstr += bitString(allValid & ~valid);
         FFStreamError err(errstr);
         err.addText("Make sure you set all header valid bits for all of the available data.");
         GPSTK_THROW(err);
      }
      
      string line;
         // line by line, let's do this.
      if (valid & versionValid)
      {
         line  = rightJustify(asString(version,2), 9);
         line += string(11, ' ');
         line += leftJustify(fileType, 40);
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
      if (valid & markerNameValid)
      {
         line  = leftJustify(markerName, 60);
         line += markerNameString;
         strm << line << endl;
         strm.lineNumber++;
      }
      if (valid & markerNumberValid)
      {
         line  = leftJustify(markerNumber, 60);
         line += markerNumberString;
         strm << line << endl;
         strm.lineNumber++;
      }
      if (valid & obsTypeValid)
      {
         line  = rightJustify(asString(obsTypeList.size()),6);
         vector<RinexMetType>::const_iterator itr = obsTypeList.begin();
         size_t numWritten = 0;
         while (itr != obsTypeList.end())
         {
            numWritten++;
               // stupid continuation lines =P
            if ((numWritten % (maxObsPerLine+1)) == 0)
            {
               line += obsTypeString;
               strm << line << endl;
               strm.lineNumber++;
               line = string(6,' ');
            }
            line += rightJustify(convertObsType(*itr), 6);
            itr++;
         }
            // pad the line out to 60 chrs and add label
         line += string(60 - line.size(), ' ');
         line += obsTypeString;
         strm << line << endl;
         strm.lineNumber++;
      }
      if (valid & sensorTypeValid)
      {
            // only write out the sensor types that are 
            // in the obsTypeList
         vector<sensorType>::const_iterator itr = sensorTypeList.begin();
         while (itr != sensorTypeList.end())
         {
            if (std::find(obsTypeList.begin(), obsTypeList.end(),
                          (*itr).obsType) != obsTypeList.end())
            {
               line  = leftJustify((*itr).model, 20);
               line += leftJustify((*itr).type, 20);
               line += string(6, ' ');
               line += rightJustify(asString((*itr).accuracy,1),7);
               line += string(4, ' ');
               line += convertObsType((*itr).obsType);
               line += string(1, ' ');
               line += sensorTypeString;
               strm << line << endl;
               strm.lineNumber++;
            }
            itr++;
         }
      }
      if (valid & sensorPosValid)
      {
            // only write out the sensor positions that are 
            // in the obsTypeList
         vector<sensorPosType>::const_iterator itr = sensorPosList.begin();
         while (itr != sensorPosList.end())
         {
            if (std::find(obsTypeList.begin(), obsTypeList.end(),
                     (*itr).obsType) != obsTypeList.end())
            {
               line  = rightJustify(asString((*itr).position[0],4),14);
               line += rightJustify(asString((*itr).position[1],4),14);
               line += rightJustify(asString((*itr).position[2],4),14);
               line += rightJustify(asString((*itr).height,4),14);
               line += string(1, ' ');
               line += convertObsType((*itr).obsType);
               line += string(1, ' ');
               line += sensorPosString;
               strm << line << endl;
               strm.lineNumber++;
            }
            itr++;
         }
      }
      if (valid & endValid)
      {
         line  = string(60, ' ');
         line += endOfHeader;
         strm << line << endl;
         strm.lineNumber++;
      }
   }     