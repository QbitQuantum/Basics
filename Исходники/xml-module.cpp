QoreStringNode *xml_module_init() {
   QoreString err;

   // set our generic error handler to catch initialization errors
   xmlSetGenericErrorFunc((void*)&err,  (xmlGenericErrorFunc)qoreXmlGenericErrorFunc);

   // initialize libxml2 library
   LIBXML_TEST_VERSION

   if (err.strlen())
      return new QoreStringNode(err);

   // reset the generic error handler back to the default
   initGenericErrorDefaultFunc(0);

   XNS.addSystemClass(initXmlNodeClass(XNS));
   XNS.addSystemClass(initXmlDocClass(XNS));
   XNS.addSystemClass(initXmlReaderClass(XNS));
   XNS.addSystemClass(initSaxIteratorClass(XNS));
   XNS.addSystemClass(initFileSaxIteratorClass(XNS));

   XNS.addSystemClass(initXmlRpcClientClass(XNS));

   init_xml_constants(XNS);

   // set up Option namespace for XML options
   QoreNamespace *option = new QoreNamespace("Option");

   init_option_constants(*option);

   XNS.addInitialNamespace(option);

   init_xml_functions(XNS);

   return 0;
}