 String getSystemProperty (const String& name)
 {
     return juceString (LocalRef<jstring> ((jstring) getEnv()->CallStaticObjectMethod (SystemClass,
                                                                                       SystemClass.getProperty,
                                                                                       javaString (name).get())));
 }