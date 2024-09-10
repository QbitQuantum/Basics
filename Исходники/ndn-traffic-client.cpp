 bool
 processConfigurationDetail( std::string detail, Logger& logger, int lineNumber )
 {
   std::string parameter, value;
   if (extractParameterValue(detail, parameter, value))
     {
       if (parameter == "TrafficPercentage")
         trafficPercentage = toInteger(value);
       else if (parameter == "Name")
         name = value;
       else if (parameter == "NameAppendBytes")
         nameAppendBytes = toInteger(value);
       else if (parameter == "NameAppendSequenceNumber")
         nameAppendSequenceNumber = toInteger(value);
       else if (parameter == "MinSuffixComponents")
         minSuffixComponents = toInteger(value);
       else if (parameter == "MaxSuffixComponents")
         maxSuffixComponents = toInteger(value);
       else if (parameter == "ExcludeBefore")
         excludeBefore = value;
       else if (parameter == "ExcludeAfter")
         excludeAfter = value;
       else if (parameter == "ExcludeBeforeBytes")
         excludeBeforeBytes = toInteger(value);
       else if (parameter == "ExcludeAfterBytes")
         excludeAfterBytes = toInteger(value);
       else if (parameter == "ChildSelector")
         childSelector = toInteger(value);
       else if (parameter == "MustBeFresh")
         mustBeFresh = toInteger(value);
       else if (parameter == "NonceDuplicationPercentage")
         nonceDuplicationPercentage = toInteger(value);
       else if (parameter == "Scope")
         scope = toInteger(value);
       else if (parameter == "InterestLifetime")
         interestLifetime = toInteger(value);
       else if (parameter == "ExpectedContent")
         expectedContent = value;
       else
         logger.log("Line "+toString(lineNumber)+" \t- Invalid Parameter='"+parameter+"'", false, true);
     }
   else
     {
       logger.log("Line "+toString(lineNumber)+" \t- Improper Traffic Configuration Line- "+detail, false, true);
       return false;
     }
   return true;
 }