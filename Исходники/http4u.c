/*######################################################################
 *##
 *## NAME:  HttpGetFileEx
 *##
 *## PURPOSE:  Return headers and body of a http request 
 *##
 *####################################################################*/
int API4U HttpGetFileEx( 
                   LPCSTR szURL, 
                   LPCSTR szProxyURL, 
                   LPCSTR szLocalFile,
                   LPCSTR szHeaderFile,
                   HTTP4U_CALLBACK CbkTransmit,
                   long   lUserValue,
                   LPSTR  szResponse, int nResponseSize,
                   LPSTR  szHeaders,  int nHeadersSize
                   )
{
SOCKET  CSock = INVALID_SOCKET;
int     Rc;
int     hHeaderFile = HFILE_ERROR;
char    szService[SERVICE_LENGTH];
char    szHost[HOST_LENGTH];
char    szFichier[FILE_LENGTH];
LPSTR   szData = NULL;
LPSTR   p;
LPCSTR  szRequest;
long    RealBodySize = -1;

struct S_HttpStatus saRespStatus;
unsigned short usPort = 0;

   Tcp4uLog (LOG4U_HIPROC, "HttpGetFileEx");

#define XX_RETURN(a) {if (szData!=NULL) Free(szData);\
                     if (hHeaderFile!=HFILE_ERROR){\
                        Close(hHeaderFile);\
                        Unlink(szHeaderFile);\
                     }\
                     if (CSock != INVALID_SOCKET) TcpClose(&CSock);\
				     Tcp4uLog (LOG4U_HIEXIT, "HttpGetFileEx with return code %d", a); \
                     return a;\
                     }
#ifdef UNIX
  /* use "hidden" env variable in order to send logs to stdout       */
  if (getenv ("http4u_log")!=NULL)   DO_NOT_LOG = fileno(stdout);
#endif

  /* control URL's validity and receive URL's components. If a proxy */
  /* is used, send the connection components into usPort, szService  */
  /* and szHost.                                                     */
  if (     ! HttpIsValidURL(  szURL,
                            & usPort,
                              szService, sizeof szService ,
                              szHost, sizeof szHost ,
                              szFichier, sizeof szFichier )
       ||  (     szProxyURL!=NULL   
             &&  ! HttpIsValidURL (szProxyURL, & usPort, 
                                   szService, sizeof szService,
                                   szHost, sizeof szHost, NULL, 0))
     )
   {
      XX_RETURN (HTTP4U_BAD_URL);
   }

   /* allocate buffer */
   if ( (szData = Calloc(1,s_uHttp4uBufferSize)) == NULL) 
   {
     XX_RETURN (HTTP4U_INSMEMORY);
   } 

   /* connect to http server, or proxy server : we don't care now */
   Rc = TcpConnect(& CSock,
                      szHost,
                      usPort==0 ? szService : NULL,
                    & usPort);
  switch (Rc)
  {
     case TCP4U_SUCCESS     :  break;  /* continue */
     case TCP4U_HOSTUNKNOWN :  XX_RETURN (HTTP4U_HOST_UNKNOWN);
     default                :  XX_RETURN (HTTP4U_TCP_CONNECT);
  }

   /* send a request-line method "GET", receive reply, receive data */
   szRequest= szProxyURL==NULL? szFichier : szURL; /* if no proxy, simple ! */
   if (   (Rc=HttpSendRequest10  (CSock, "GET ", szRequest)) != HTTP4U_SUCCESS
       || (Rc=HttpRecvRespStatus (CSock, & saRespStatus, 
                                  szResponse,nResponseSize)) != HTTP4U_SUCCESS )
   {
      XX_RETURN (Rc);
    }

   /* an answer has been received, let us have a look on it */
   switch(saRespStatus.code) 
   {
       case 200: break; /* reason-phrase OK */ 
       case 204: XX_RETURN (HTTP4U_NO_CONTENT);
       case 300:
       case 301: XX_RETURN (HTTP4U_MOVED);
       case 400: XX_RETURN (HTTP4U_BAD_REQUEST);
       case 401:
       case 403: XX_RETURN (HTTP4U_FORBIDDEN);
       case 404: XX_RETURN (HTTP4U_NOT_FOUND);
       default:  XX_RETURN (HTTP4U_PROTOCOL_ERROR);
   }

   /* read headers */
   Rc = HttpRecvHeaders10(CSock, szData, s_uHttp4uBufferSize);
   /* copy headers into user buffer even if return incorrect */
   if (szHeaders != NULL) 
     Strcpyn (szHeaders, szData, min(s_uHttp4uBufferSize, (unsigned) nHeadersSize));

   if (Rc!=HTTP4U_SUCCESS)     XX_RETURN (Rc);

   /* write headers into the user local file */
  if (szHeaderFile != NULL ) 
  {
    if ((hHeaderFile = Open(szHeaderFile, WRITE_CR)) == HFILE_ERROR) 
    {
       XX_RETURN (HTTP4U_FILE_ERROR);
    }
    /* write */
    if (Write(hHeaderFile, szData, Strlen(szData)) == HFILE_ERROR) 
    {
        XX_RETURN(HTTP4U_FILE_ERROR);
    }
    Close(hHeaderFile);
    hHeaderFile = HFILE_ERROR;
  } /* szHeaderFile not NULL */

  /* if we do not need something else, just close the connection */
  /* not really nice, but HTTP servers are used to deal with it  */ 
  if (szLocalFile==NULL  &&  CbkTransmit==NULL) 
  {
     XX_RETURN (HTTP4U_SUCCESS);
  }

  /* search real length of the body */ 
  RealBodySize = -1;         /* can not compute it */
  szData[s_uHttp4uBufferSize-1] = '\0';
  p = Tcp4uStrIStr (szData, "content-length:");
  if (p!=NULL) 
  {
    p += sizeof("Content-Length:");
    while (isspace(*p)) p++;  /* skip space character */
    RealBodySize = Tcp4uAtol (p);
  }
    
  /* read Body of the respons */
  Rc=TcpRecvUntilClosedEx (& CSock,
                             szLocalFile,
                             (FARPROC) CbkTransmit,
                             s_uHttp4uTimeout,
                             s_uHttp4uBufferSize,
                             lUserValue,
                             RealBodySize);

  switch (Rc)
  {
    case TCP4U_SUCCESS:     Rc = HTTP4U_SUCCESS;    break; 
    case TCP4U_TIMEOUT:     Rc = HTTP4U_TIMEOUT;    break; 
    case TCP4U_FILE_ERROR : Rc = HTTP4U_FILE_ERROR; break; 
    case TCP4U_INSMEMORY :  Rc = HTTP4U_INSMEMORY;  break; 
    case TCP4U_CANCELLED :  Rc = HTTP4U_CANCELLED;  break; 
    default:                Rc = HTTP4U_TCP_FAILED; break; 
                                                                           
  }
XX_RETURN (Rc);
#undef XX_RETURN
} /* HttpGetFileEx */