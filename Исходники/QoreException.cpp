// static function
QoreHashNode *QoreException::getStackHash(int type, const char *class_name, const char *code, const QoreProgramLocation& loc) {
   QoreHashNode *h = new QoreHashNode;

   QoreStringNode *str = new QoreStringNode;
   if (class_name)
      str->sprintf("%s::", class_name);
   str->concat(code);

   //printd(5, "QoreException::getStackHash() %s at %s:%d-%d src: %s+%d\n", str->getBuffer(), loc.file ? loc.file : "n/a", loc.start_line, loc.end_line, loc.source ? loc.source : "n/a", loc.offset);
   
   h->setKeyValue("function", str, 0);
   h->setKeyValue("line",     new QoreBigIntNode(loc.start_line), 0);
   h->setKeyValue("endline",  new QoreBigIntNode(loc.end_line), 0);
   h->setKeyValue("file",     loc.file ? new QoreStringNode(loc.file) : 0, 0);
   h->setKeyValue("source",   loc.source ? new QoreStringNode(loc.source) : 0, 0);
   h->setKeyValue("offset",   new QoreBigIntNode(loc.offset), 0);
   h->setKeyValue("typecode", new QoreBigIntNode(type), 0);
   const char *tstr = 0;
   switch (type) {
      case CT_USER:
	 tstr = "user";
         break;
      case CT_BUILTIN:
	 tstr = "builtin";
         break;
      case CT_RETHROW:
	 tstr = "rethrow";
         break;
/*
      case CT_NEWTHREAD:
	 tstr = "new-thread";
         break;
*/
      default:
	 assert(false);
   }
   h->setKeyValue("type",  new QoreStringNode(tstr), 0);
   return h;
}