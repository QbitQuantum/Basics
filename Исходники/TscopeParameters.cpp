   virtual string callOperation(TscopeProxy *proxy)
   {
      proxy->disconnect();  // break connection to ant server

      if (componentControlImmedCmdsGlobal.isComponentUnderControl(proxy->getName()))
      {
         // Let the component controller perform a shutdown so that
         // the component will not be restarted.
         componentControlImmedCmdsGlobal.shutdown(proxy->getName());
      }
      else
      {
         // Let the proxy handle shutdown on its own.
         proxy->shutdown();
      }

      return "";
   }