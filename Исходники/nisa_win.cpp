 void VisaEmitter::EIO_Open(GenericBaton* data) {
   char temp[QUERY_STRING_SIZE];
   ViStatus status = -1;
   if (this->isConnected)
   {
     _snprintf(temp, sizeof(temp), "Already connected %s", session);
     ErrorCodeToString(temp, status, data->errorString);
     return;
   }
   status = viOpenDefaultRM(&defaultRM);
   if (status < VI_SUCCESS) {
     _snprintf(temp, sizeof(temp), "Opening RM");
     ErrorCodeToString(temp, status, data->errorString);
     return;
   }
   status = viOpen(defaultRM, data->command, VI_NULL, this->timeoutMiliSeconds, &session);
   if (status < VI_SUCCESS) {
     _snprintf(temp, sizeof(temp), "Opening session %s", data->command);
     ErrorCodeToString(temp, status, data->errorString);
     return;
   }
   status = viSetAttribute(session, VI_ATTR_TMO_VALUE, this->timeoutMiliSeconds);
   if (status < VI_SUCCESS) {
     _snprintf(temp, sizeof(temp), "Setting timeout to %d", this->timeoutMiliSeconds);
     ErrorCodeToString(temp, status, data->errorString);
     return;
   }
   
   
   this->isConnected = true;
   // status = viSetAttribute(instr, VI_ATTR_SEND_END_EN, VI_TRUE);
   // terminate reads on a carriage return  0x0a 0x0d
   // LF (Line feed, '\n', 0x0A, 10 in decimal) 
   // Carriage return, '\r', 0x0D, 13 in decimal
   
   // status = viSetAttribute(session, VI_ATTR_TERMCHAR, 0x0A);
   //status = viSetAttribute(session, VI_ATTR_TERMCHAR_EN, VI_TRUE);
   
   if (this->assertREN) {
     viGpibControlREN(session, VI_GPIB_REN_ASSERT);
   }
   
   if (this->enableSRQ)  
   {
     m_async = uv_async_t();
     m_async.data = this;    
     uv_async_init(uv_default_loop(), &m_async, reinterpret_cast<uv_async_cb>(aCallback));
     isAsyncInitialized = true;
     
     status = viInstallHandler(session, VI_EVENT_SERVICE_REQ, callback, this->uniqueSRQhandlerIdentification);
     if (status >= VI_SUCCESS) {
       status = viEnableEvent(session, VI_EVENT_SERVICE_REQ, VI_HNDLR, VI_NULL);
     }  
     if (status < VI_SUCCESS) {
       _snprintf(temp, sizeof(temp), "Post AfterOpenSuccess session %s", data->command);
       ErrorCodeToString(temp, status, data->errorString);
       return;
     }        
     this->installedSRQHanlder = true;
   }    
   _snprintf_s(data->result, _countof(data->result), _TRUNCATE, "%d", session);
 }