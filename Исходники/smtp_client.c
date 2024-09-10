error_t smtpSendMail(const SmtpAuthInfo *authInfo, const SmtpMail *mail)
{
   error_t error;
   uint_t i;
   uint_t replyCode;
   IpAddr serverIpAddr;
   SmtpClientContext *context;

   //Check parameters
   if(!authInfo || !mail)
      return ERROR_INVALID_PARAMETER;
   //Make sure the server name is valid
   if(!authInfo->serverName)
      return ERROR_INVALID_PARAMETER;

   //Debug message
   TRACE_INFO("Sending a mail to %s port %" PRIu16 "...\r\n",
      authInfo->serverName, authInfo->serverPort);

   //The specified SMTP server can be either an IP or a host name
   error = getHostByName(authInfo->interface,
      authInfo->serverName, &serverIpAddr, 0);
   //Unable to resolve server name?
   if(error)
      return ERROR_NAME_RESOLUTION_FAILED;

   //Allocate a memory buffer to hold the SMTP client context
   context = osAllocMem(sizeof(SmtpClientContext));
   //Failed to allocate memory?
   if(!context)
      return ERROR_OUT_OF_MEMORY;

   //Open a TCP socket
   context->socket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);
   //Failed to open socket?
   if(!context->socket)
   {
      //Free previously allocated resources
      osFreeMem(context);
      //Report an error
      return ERROR_OPEN_FAILED;
   }

#if (SMTP_TLS_SUPPORT == ENABLED)
   //Do not use SSL/TLS for the moment
   context->tlsContext = NULL;
#endif

   //Start of exception handling block
   do
   {
      //Bind the socket to a particular network interface?
      if(authInfo->interface)
      {
         //Associate the socket with the relevant interface
         error = socketBindToInterface(context->socket, authInfo->interface);
         //Any error to report?
         if(error) break;
      }

      //Set timeout for blocking operations
      error = socketSetTimeout(context->socket, SMTP_DEFAULT_TIMEOUT);
      //Any error to report?
      if(error) break;

      //Connect to the SMTP server
      error = socketConnect(context->socket, &serverIpAddr, authInfo->serverPort);
      //Connection to server failed?
      if(error) break;

#if (SMTP_TLS_SUPPORT == ENABLED)
      //Open a secure SSL/TLS session?
      if(authInfo->useTls)
      {
         //Initialize TLS context
         context->tlsContext = tlsInit();
         //Initialization failed?
         if(!context->tlsContext)
         {
            //Unable to allocate memory
            error = ERROR_OUT_OF_MEMORY;
            //Stop immediately
            break;
         }

         //Bind TLS to the relevant socket
         error = tlsSetSocket(context->tlsContext, context->socket);
         //Any error to report?
         if(error) break;

         //Select client operation mode
         error = tlsSetConnectionEnd(context->tlsContext, TLS_CONNECTION_END_CLIENT);
         //Any error to report?
         if(error) break;

         //Set the PRNG algorithm to be used
         error = tlsSetPrng(context->tlsContext, authInfo->prngAlgo, authInfo->prngContext);
         //Any error to report?
         if(error) break;

         //Perform TLS handshake
         error = tlsConnect(context->tlsContext);
         //Failed to established a TLS session?
         if(error) break;
      }
#endif

      //Wait for the connection greeting reply
      error = smtpSendCommand(context, NULL, &replyCode, NULL);
      //Any communication error to report?
      if(error) break;

      //Check whether the greeting message was properly received
      if(!SMTP_REPLY_CODE_2YZ(replyCode))
      {
         //An unexpected response was received...
         error = ERROR_UNEXPECTED_RESPONSE;
         //Stop immediately
         break;
      }

      //Clear security features
      context->authLoginSupported = FALSE;
      context->authPlainSupported = FALSE;
      context->authCramMd5Supported = FALSE;
      context->startTlsSupported = FALSE;

      //Send EHLO command and parse server response
      error = smtpSendCommand(context, "EHLO [127.0.0.1]\r\n",
         &replyCode, smtpEhloReplyCallback);
      //Any communication error to report?
      if(error) break;

      //Check SMTP response code
      if(!SMTP_REPLY_CODE_2YZ(replyCode))
      {
         //An unexpected response was received...
         error = ERROR_UNEXPECTED_RESPONSE;
         //Stop immediately
         break;
      }

#if (SMTP_TLS_SUPPORT == ENABLED)
      //Check whether the STARTTLS command is supported
      if(context->startTlsSupported && !context->tlsContext)
      {
         //Send STARTTLS command
         error = smtpSendCommand(context, "STARTTLS\r\n", &replyCode, NULL);
         //Any communication error to report?
         if(error) break;

         //Check SMTP response code
         if(!SMTP_REPLY_CODE_2YZ(replyCode))
         {
            //An unexpected response was received...
            error = ERROR_UNEXPECTED_RESPONSE;
            //Stop immediately
            break;
         }

         //Initialize TLS context
         context->tlsContext = tlsInit();
         //Initialization failed?
         if(!context->tlsContext)
         {
            //Unable to allocate memory
            error = ERROR_OUT_OF_MEMORY;
            //Stop immediately
            break;
         }

         //Bind TLS to the relevant socket
         error = tlsSetSocket(context->tlsContext, context->socket);
         //Any error to report?
         if(error) break;

         //Select client operation mode
         error = tlsSetConnectionEnd(context->tlsContext, TLS_CONNECTION_END_CLIENT);
         //Any error to report?
         if(error) break;

         //Set the PRNG algorithm to be used
         error = tlsSetPrng(context->tlsContext, authInfo->prngAlgo, authInfo->prngContext);
         //Any error to report?
         if(error) break;

         //Perform TLS handshake
         error = tlsConnect(context->tlsContext);
         //Failed to established a TLS session?
         if(error) break;

         //Clear security features
         context->authLoginSupported = FALSE;
         context->authPlainSupported = FALSE;
         context->authCramMd5Supported = FALSE;

         //Send EHLO command and parse server response
         error = smtpSendCommand(context, "EHLO [127.0.0.1]\r\n",
            &replyCode, smtpEhloReplyCallback);
         //Any communication error to report?
         if(error) break;

         //Check SMTP response code
         if(!SMTP_REPLY_CODE_2YZ(replyCode))
         {
            //An unexpected response was received...
            error = ERROR_UNEXPECTED_RESPONSE;
            //Stop immediately
            break;
         }
      }
#endif

      //Authentication requires a valid user name and password
      if(authInfo->userName && authInfo->password)
      {
#if (SMTP_LOGIN_AUTH_SUPPORT == ENABLED)
         //LOGIN authentication mechanism supported?
         if(context->authLoginSupported)
         {
            //Perform LOGIN authentication
            error = smtpSendAuthLogin(context, authInfo);
            //Authentication failed?
            if(error) break;
         }
         else
#endif
#if (SMTP_PLAIN_AUTH_SUPPORT == ENABLED)
         //PLAIN authentication mechanism supported?
         if(context->authPlainSupported)
         {
            //Perform PLAIN authentication
            error = smtpSendAuthPlain(context, authInfo);
            //Authentication failed?
            if(error) break;
         }
         else
#endif
#if (SMTP_CRAM_MD5_AUTH_SUPPORT == ENABLED)
         //CRAM-MD5 authentication mechanism supported?
         if(context->authCramMd5Supported)
         {
            //Perform CRAM-MD5 authentication
            error = smtpSendAuthCramMd5(context, authInfo);
            //Authentication failed?
            if(error) break;
         }
         else
#endif
         //No authentication mechanism supported?
         {
            //Skip authentication step
         }
      }

      //Format the MAIL FROM command (a null return path must be accepted)
      if(mail->from.addr)
         sprintf(context->buffer, "MAIL FROM:<%s>\r\n", mail->from.addr);
      else
         strcpy(context->buffer, "MAIL FROM:<>\r\n");

      //Send the command to the server
      error = smtpSendCommand(context, context->buffer, &replyCode, NULL);
      //Any communication error to report?
      if(error) break;

      //Check SMTP response code
      if(!SMTP_REPLY_CODE_2YZ(replyCode))
      {
         //An unexpected response was received...
         error = ERROR_UNEXPECTED_RESPONSE;
         //Stop immediately
         break;
      }

      //Format the RCPT TO command
      for(i = 0; i < mail->recipientCount; i++)
      {
         //Skip recipient addresses that are not valid
         if(!mail->recipients[i].addr)
            continue;

         //Format the RCPT TO command
         sprintf(context->buffer, "RCPT TO:<%s>\r\n", mail->recipients[i].addr);
         //Send the command to the server
         error = smtpSendCommand(context, context->buffer, &replyCode, NULL);
         //Any communication error to report?
         if(error) break;

         //Check SMTP response code
         if(!SMTP_REPLY_CODE_2YZ(replyCode))
         {
            //An unexpected response was received...
            error = ERROR_UNEXPECTED_RESPONSE;
            //Stop immediately
            break;
         }
      }

      //Propagate exception if necessary
      if(error) break;

      //Send message body
      error = smtpSendData(context, mail);
      //Any error to report?
      if(error) break;

      //End of exception handling block
   } while(0);

   //Check status code
   if(error == NO_ERROR ||
      error == ERROR_UNEXPECTED_RESPONSE ||
      error == ERROR_AUTHENTICATION_FAILED)
   {
      //Properly disconnect from the SMTP server
      smtpSendCommand(context, "QUIT\r\n", &replyCode, NULL);
   }

#if (SMTP_TLS_SUPPORT == ENABLED)
   //Gracefully close SSL/TLS session
   if(context->tlsContext != NULL)
      tlsFree(context->tlsContext);
#endif

   //Close socket
   socketClose(context->socket);
   //Clean up previously allocated resources
   osFreeMem(context);

   //Return status code
   return error;
}