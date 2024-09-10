AbstractQoreNode* ExceptionSink::raiseException(const char *err, const char *fmt, ...) {
   QoreStringNode *desc = new QoreStringNode;
   
   va_list args;
   
   while (true) {
      va_start(args, fmt);
      int rc = desc->vsprintf(fmt, args);
      va_end(args);
      if (!rc)
	 break;
   }
   printd(5, "ExceptionSink::raiseException(%s, %s)\n", err, desc->getBuffer());
   priv->insert(new QoreException(err, desc));
   return 0;
}