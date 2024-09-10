OsStatus ForwardRules::getRouteTo(UtlString& RouteToString,
                                 bool& authRequired,
                                  TiXmlNode* nodeWithRouteToChild)
{
   
   OsStatus currentStatus = OS_FAILED;
   nodeWithRouteToChild->ToElement();
   TiXmlNode* routeToNode = NULL;
   TiXmlNode* routeToText = NULL;


   //get the user text value from it
   routeToNode = nodeWithRouteToChild->FirstChild(XML_TAG_ROUTETO);
   if(routeToNode)
   {
      if(routeToNode && routeToNode->Type() != TiXmlNode::ELEMENT)
      {
         return currentStatus;
      }

      TiXmlElement* routeToElement = routeToNode->ToElement();

      const char* authRequiredPtr = 
         routeToElement->Attribute(XML_ATT_AUTHREQUIRED);

      //set the authRequired attribute
      authRequired=getYN(authRequiredPtr, false) ; //defaults to false

      RouteToString.remove(0);
      routeToText = routeToElement->FirstChild();
      if(routeToText && routeToText->Type() == TiXmlNode::TEXT)
      {
         TiXmlText* routeTo = routeToText->ToText();
         if (routeTo)
         {
            RouteToString.append(routeTo->Value());
         }
      }
      // TinyXML compresses white space, so an all white space element becomes
      // zero length, but just in case, let's strip it ourselves.
      RouteToString.strip(UtlString::both);
      if (RouteToString.length() > 0)
      {
         // The route is not empty.  Declare success
         currentStatus = OS_SUCCESS;
      }
      else if (authRequired)
      {
         // The Route can be empty, as long as authRequired is set.
         // This means just route to the authProxy.
         currentStatus = OS_SUCCESS;
      }
      else
      {
         // Empty or missing route, and no authRequired...that's not allowed.
         currentStatus = OS_FAILED;
      }
   }
   return currentStatus;
}