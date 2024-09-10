MM::DeviceDetectionStatus VariLC::DetectDevice(void)
{
   // all conditions must be satisfied...
   MM::DeviceDetectionStatus result = MM::Misconfigured;

   try
   {	   
	   long baud;
	   GetProperty(g_BaudRate_key, baud);

      std::string transformed = port_;
      for( std::string::iterator its = transformed.begin(); its != transformed.end(); ++its)
      {
         *its = (char)tolower(*its);
      }	  	     

      if( 0< transformed.length() &&  0 != transformed.compare("undefined")  && 0 != transformed.compare("unknown") )
      {
		int ret = 0;	  
		MM::Device* pS;

		
			 // the port property seems correct, so give it a try
			 result = MM::CanNotCommunicate;
			 // device specific default communication parameters
			 GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_AnswerTimeout, "2000.0");			 
			 GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_BaudRate, baud_.c_str() );
			 GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_DelayBetweenCharsMs, "0.0");
			 GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_Handshaking, "Off");
			 GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_Parity, "None");
			 GetCoreCallback()->SetDeviceProperty(port_.c_str(), MM::g_Keyword_StopBits, "1");
			 GetCoreCallback()->SetDeviceProperty(port_.c_str(), "Verbose", "1");
			 pS = GetCoreCallback()->GetDevice(this, port_.c_str());
			 pS->Initialize();
	         
			 ClearPort(*this, *GetCoreCallback(), port_);
			 ret = SendSerialCommand(port_.c_str(), "V?", "\r");     
			 GetSerialAnswer (port_.c_str(), "\r", serialnum_);
			 GetSerialAnswer (port_.c_str(), "\r", serialnum_);
				 if (ret!=DEVICE_OK || serialnum_.length() < 5)
				 {
					LogMessageCode(ret,true);
					LogMessage(std::string("VariLC not found on ")+port_.c_str(), true);
					LogMessage(std::string("VariLC serial no:")+serialnum_, true);
					ret = 1;
					serialnum_ = "0";
					pS->Shutdown();	
				 } else
				 {
					// to succeed must reach here....
					LogMessage(std::string("VariLC found on ")+port_.c_str(), true);
					LogMessage(std::string("VariLC serial no:")+serialnum_, true);
					result = MM::CanCommunicate;	
					GetCoreCallback()->SetSerialProperties(port_.c_str(),
											  "600.0",
											  baud_.c_str(),
											  "0.0",
											  "Off",
											  "None",
											  "1");
					serialnum_ = "0";
					pS->Initialize();
					ret = SendSerialCommand(port_.c_str(), "R 1", "\r");
					ret = SendSerialCommand(port_.c_str(), "C 0", "\r");
					pS->Shutdown();					
				}
      }
   }
   catch(...)
   {
      LogMessage("Exception in DetectDevice!",false);
   }
   return result;
}