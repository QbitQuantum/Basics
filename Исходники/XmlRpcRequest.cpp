// Constructor
XmlRpcRequest::XmlRpcRequest(Url& uri, const char* methodName)
   : mUrl(uri)
   , mpHttpRequest(new HttpMessage())
   , mpRequestBody(new XmlRpcBody())
{
   UtlString path;
   if( uri.getPath( path ) == FALSE )
   {
      path = "/RPC2";
   }
   // Start to contruct the HTTP message
   mpHttpRequest->setFirstHeaderLine(HTTP_POST_METHOD, path, HTTP_PROTOCOL_VERSION_1_1);
   mpHttpRequest->addHeaderField("Accept", "text/xml");
   mpHttpRequest->setUserAgentField(PACKAGE_NAME "_xmlrpc/" PACKAGE_VERSION);

   // Start to construct the XML-RPC body
   mpRequestBody->append(BEGIN_METHOD_CALL BEGIN_METHOD_NAME);
   mpRequestBody->append(methodName);
   mpRequestBody->append(END_METHOD_NAME BEGIN_PARAMS);
}