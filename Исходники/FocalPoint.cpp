MM::DeviceDetectionStatus FocalPointCheckSerialPort(MM::Device& device, MM::Core& core, std::string portToCheck, double answerTimeoutMs)
{
   // all conditions must be satisfied...
   MM::DeviceDetectionStatus result = MM::Misconfigured;
   char answerTO[MM::MaxStrLength];

   try
   {
      std::string portLowerCase = portToCheck;
      for( std::string::iterator its = portLowerCase.begin(); its != portLowerCase.end(); ++its)
      {
         *its = (char)tolower(*its);
      }
      if( 0< portLowerCase.length() &&  0 != portLowerCase.compare("undefined")  && 0 != portLowerCase.compare("unknown") )
      {
         result = MM::CanNotCommunicate;
         core.GetDeviceProperty(portToCheck.c_str(), "AnswerTimeout", answerTO);
         // device specific default communication parameters
         // for ASI Stage
         core.SetDeviceProperty(portToCheck.c_str(), MM::g_Keyword_Handshaking, "Off");
         core.SetDeviceProperty(portToCheck.c_str(), MM::g_Keyword_StopBits, "1");
         std::ostringstream too;
         too << answerTimeoutMs;
         core.SetDeviceProperty(portToCheck.c_str(), "AnswerTimeout", too.str().c_str());
         core.SetDeviceProperty(portToCheck.c_str(), "DelayBetweenCharsMs", "0");
         MM::Device* pS = core.GetDevice(&device, portToCheck.c_str());
         std::vector< std::string> possibleBauds;
         possibleBauds.push_back("9600");
         for( std::vector< std::string>::iterator bit = possibleBauds.begin(); bit!= possibleBauds.end(); ++bit )
         {
            core.SetDeviceProperty(portToCheck.c_str(), MM::g_Keyword_BaudRate, (*bit).c_str() );
            pS->Initialize();
            core.PurgeSerial(&device, portToCheck.c_str());
            // check status
            const char* command = "/";
            int ret = core.SetSerialCommand( &device, portToCheck.c_str(), command, "\r");
            if( DEVICE_OK == ret)
            {
               char answer[MM::MaxStrLength];

               ret = core.GetSerialAnswer(&device, portToCheck.c_str(), MM::MaxStrLength, answer, "\r\n");
               if( DEVICE_OK != ret )
               {
                  char text[MM::MaxStrLength];
                  device.GetErrorText(ret, text);
                  core.LogMessage(&device, text, true);
               }
               else
               {
                  // to succeed must reach here....
                  result = MM::CanCommunicate;
               }
            }
            else
            {
               char text[MM::MaxStrLength];
               device.GetErrorText(ret, text);
               core.LogMessage(&device, text, true);
            }
            pS->Shutdown();
            if( MM::CanCommunicate == result)
               break;
            else
               // try to yield to GUI
               CDeviceUtils::SleepMs(10);
         }
         // always restore the AnswerTimeout to the default
         core.SetDeviceProperty(portToCheck.c_str(), "AnswerTimeout", answerTO);
      }
   }
   catch(...)
   {
      core.LogMessage(&device, "Exception in DetectDevice!",false);
   }
   return result;
}