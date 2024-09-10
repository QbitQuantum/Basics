MM::DeviceDetectionStatus Hub::DetectDevice(void)
{
   // all conditions must be satisfied...
   MM::DeviceDetectionStatus result = MM::Misconfigured;
   char answerTO[MM::MaxStrLength];

   try
   {
      std::string portLowerCase = port_;
      for( std::string::iterator its = portLowerCase.begin(); its != portLowerCase.end(); ++its)
      {
         *its = (char)tolower(*its);
      }
      if( 0< portLowerCase.length() &&  0 != portLowerCase.compare("undefined")  && 0 != portLowerCase.compare("unknown") )
      {
         result = MM::CanNotCommunicate;

         // record the default answer time out
         GetCoreCallback()->GetDeviceProperty(port_.c_str(), "AnswerTimeout", answerTO);

         // device specific default communication parameters
         // for ASI FW
         GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_Handshaking, "Off");
         GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_StopBits, "1");
         GetCoreCallback()->SetDeviceProperty(port_.c_str(), "AnswerTimeout", "500.0");
         GetCoreCallback()->SetDeviceProperty(port_.c_str(), "DelayBetweenCharsMs", "0");
         MM::Device* pS = GetCoreCallback()->GetDevice(this, port_.c_str());

         std::vector< std::string> possibleBauds;
         possibleBauds.push_back("115200");
         possibleBauds.push_back("28800");         
         possibleBauds.push_back("19200");
         possibleBauds.push_back("9600");


         for( std::vector< std::string>::iterator bit = possibleBauds.begin(); bit!= possibleBauds.end(); ++bit )
         {
            GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_BaudRate, (*bit).c_str() );
            pS->Initialize();
            PurgeComPort(port_.c_str());
            // Version
            char version[256];
            int ret = g_hub.GetVersion(*this, *GetCoreCallback(), version);
            if( DEVICE_OK != ret )
            {
               LogMessageCode(ret,true);
            }
            else
            {
               // to succeed must reach here....
               result = MM::CanCommunicate;
            }
            pS->Shutdown();
            CDeviceUtils::SleepMs(300);
            if( MM::CanCommunicate == result)
               break;
         }
         // always restore the AnswerTimeout to the default
         GetCoreCallback()->SetDeviceProperty(port_.c_str(), "AnswerTimeout", answerTO);

      }
   }
   catch(...)
   {
      LogMessage("Exception in DetectDevice!",false);
   }
   return result;
}