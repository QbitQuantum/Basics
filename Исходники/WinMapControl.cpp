/* second-phase constructor */
bool WinMapControl::construct(LPCREATESTRUCTW cParams, 
                              const char* mapServer, int portNum,
                              const char* sessionId,
                              const char* sessionKey)
{
   /* get the dimensions of the window */
   m_width = cParams->cx;
   m_height = cParams->cy;

   /* create the toolkit */
   m_toolkit = new WinTileMapToolkit(m_hwnd, cParams->hInstance);
   if(m_toolkit == NULL) return(false);

   /* create the plotter */
   m_plotter = isab::WinMapPlotter::allocate(m_width, m_height, 
                                             m_hwnd);
   if(m_plotter == NULL) return(false);
   /* set the blitting position for the plotter */
   m_plotter->setBlitPoint(cParams->x, cParams->y);

   /* create the TCP Connection handler */
   m_connHandler = WinTCPConnectionHandler::allocate(cParams->hInstance);
   if(m_connHandler == NULL) return(false);

   /* create the HTTP client connection */
   m_httpConn = new HttpClientConnection(mapServer, 
                                         portNum,
                                         NULL,
                                         m_connHandler);
   if(m_httpConn == NULL) return(false);

   /* check if session params needed */
   if( (sessionId == NULL) || (sessionKey == NULL) ||
       (sessionId == "") || (sessionKey == "") ) {
      /* create the Internet Requester without session info */
      m_httpReq = new SharedHttpDBufRequester(m_httpConn, "/TMap");
   }
   else {
      /* create the session params */
      char sessionParam[256];
      _mbscpy((unsigned char*)sessionParam, (unsigned char*)"?");
      _mbscat((unsigned char*)sessionParam, (unsigned char*)"si=");
      _mbscat((unsigned char*)sessionParam, (unsigned char*)sessionId);
      _mbscat((unsigned char*)sessionParam, (unsigned char*)"&sk=");
      _mbscat((unsigned char*)sessionParam, (unsigned char*)sessionKey);
      /* create the Internet Requester */
      m_httpReq = new SharedHttpDBufRequester(m_httpConn, "/TMap",
                                              sessionParam);
   }
   if(m_httpReq == NULL) return(false);

   /* create the caching requester */
   m_memReq = new MemoryDBufRequester(m_httpReq, 8*1024*1024);
   if(m_memReq == NULL) {
      /* delete the requester, since it wont get deleted thru 
         the TileMapHandler's destructor */
      delete m_httpReq;
      return(false);
   }

   /* create the map handler */
   m_mapHandler = new TileMapHandler(m_plotter,
                                     m_memReq,
                                     m_toolkit);
   if(m_mapHandler == NULL) return(false);

   /* initiate the first redraw */
   m_mapHandler->repaint(0);

   /* success */
   return(true);
}