error_t icecastClientConnect(IcecastClientContext *context)
{
   error_t error;
   size_t length;
   IpAddr serverIpAddr;

   //Icecast request template
   const char_t requestTemplate[] =
      "GET /%s HTTP/1.1\r\n"
      "Host: %s\r\n"
      "User-agent: UserAgent\r\n"
      "Icy-MetaData: 1\r\n"
      "Connection: close\r\n"
      "\r\n";

   //The specified Icecast server can be either an IP or a host name
   error = getHostByName(context->settings.interface,
      context->settings.serverName, &serverIpAddr, 1, NULL, 0);
   //Unable to resolve server name?
   if(error) return error;

   //Open a TCP socket
   context->socket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_PROTOCOL_TCP);
   //Failed to open socket?
   if(!context->socket) return ERROR_OUT_OF_RESOURCES;

   //Start of exception handling block
   do
   {
      //Adjust receive timeout
      error = socketSetTimeout(context->socket, ICECAST_CLIENT_TIMEOUT);
      //Any error to report?
      if(error) return error;

      //Connect to the specified Icecast server
      error = socketConnect(context->socket, &serverIpAddr, context->settings.serverPort);
      //Connection with server failed?
      if(error) return error;

      //Format Icecast request
      length = sprintf(context->buffer, requestTemplate,
         context->settings.resource, context->settings.serverName);

      //Debug message
      TRACE_DEBUG(context->buffer);

      //Send Icecast request
      error = socketSend(context->socket, context->buffer,
         length, NULL, SOCKET_FLAG_WAIT_ACK);

      //Failed to send the request?
      if(error) return error;

      //Parse response header
      while(1)
      {
         char_t *separator;
         char_t *property;
         char_t *value;

         //Read a line from the response header
         error = socketReceive(context->socket, context->buffer,
            ICECAST_CLIENT_METADATA_MAX_SIZE, &length, SOCKET_FLAG_BREAK_CRLF);
         //Failed to read data?
         if(error)
            break;

         //Properly terminate the string with a NULL character
         context->buffer[length] = '\0';

         //The end of the header has been reached?
         if(!strcmp(context->buffer, "\r\n"))
            break;

         //Check whether a separator is present
         separator = strchr(context->buffer, ':');

         //Separator found?
         if(separator)
         {
            //Split the line
            *separator = '\0';

            //Get property name and value
            property = strTrimWhitespace(context->buffer);
            value = strTrimWhitespace(separator + 1);

            //Debug message
            TRACE_INFO("<%s>=<%s>\r\n", property, value);

            //Icy-Metaint property found?
            if(!strcasecmp(property, "Icy-Metaint"))
               context->blockSize = atoi(value);
         }
      }

      //End of exception handling block
   } while(0);

   //Check whether an error occurred
   if(error)
   {
      //Clean up side effects
      socketClose(context->socket);
   }

   //Return status code
   return error;
}