byte ESP8266_Simple::startHttpServer(unsigned port, unsigned long (* requestHandler)(char *buffer, int bufferLength), unsigned int maxBufferSize)
{
  char cmdBuffer[64];
  byte responseCode;
  
  this->httpServerRequestHandler = requestHandler;
  this->httpServerMaxBufferSize = maxBufferSize;
  
  // Enter MUX mode
  responseCode = this->sendCommand(F("AT+CIPMUX=1"));
  if(responseCode != ESP8266_OK) return responseCode;
  
  // Set Server Timeout
  memset(cmdBuffer,0,sizeof(cmdBuffer));
  strcpy_P(cmdBuffer, PSTR("AT+CIPSTO=,"));
  ultoa(this->generalCommandTimeoutMicroseconds/1000/1000, cmdBuffer+strlen(cmdBuffer), 10);    
  this->sendCommand(cmdBuffer);
  
  // Start Server
  memset(cmdBuffer,0,sizeof(cmdBuffer));
  strcpy_P(cmdBuffer, PSTR("AT+CIPSERVER=1,"));
  itoa(port, cmdBuffer+strlen(cmdBuffer), 10);    
  responseCode = this->sendCommand(cmdBuffer);
  if(responseCode != ESP8266_OK) return responseCode;
    
  return ESP8266_OK;
}