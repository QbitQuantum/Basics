int main(const int argc, const char **argv)
{
  // output looks like:
  // PG_OperatingSystem
  ///  Namespaces: root/cimv2
  //   Provider:   PG_OperatingSystemProvider
  //   Type:       Instance
  //   Module:     OperatingSystemModule
  //   File:       libOSProvider.sl

  _c.setTimeout(PEGASUS_DEFAULT_CLIENT_TIMEOUT_MILLISECONDS);

  // everything in big try/catch to display errors
  try
  {
    _c.connectLocal();

    // Start by enumerating PG_ProviderCapabilities
    Array<CIMObjectPath> capRef =
      _c.enumerateInstanceNames(PEGASUS_NAMESPACENAME_INTEROP,
              "PG_ProviderCapabilities");
    for (int i=0; i<capRef.size(); i++)
    {
      // get the instance
      CIMInstance cap = _c.getInstance(PEGASUS_NAMESPACENAME_INTEROP,capRef[i]);

      // get referenced instance of PG_ProviderModule for later use
      String pMod;
      cap.getProperty(
              cap.findProperty("ProviderModuleName")).getValue().get(pMod);
      CIMObjectPath modRef(String("PG_ProviderModule.Name=\"") + pMod + "\"");
      CIMInstance mod = _c.getInstance(PEGASUS_NAMESPACENAME_INTEROP,modRef);

      // display name of class instrumented
      String className;
      cap.getProperty(cap.findProperty("ClassName")).getValue().get(className);
      cout << endl << className << endl;

      // display namespaces
      Array<String> nameSpaces;
      cap.getProperty(
              cap.findProperty("Namespaces")).getValue().get(nameSpaces);
      cout << "  Namespaces:";
      for (int j=0; j<nameSpaces.size(); j++) cout << " " << nameSpaces[j];
      cout << endl;
      
      // display name of provider
      String pName;
      cap.getProperty(cap.findProperty("ProviderName")).getValue().get(pName);
      cout << "  Provider:   " << pName << endl;

      // display type of provider
      Array<Uint16> pType;
      cap.getProperty(cap.findProperty("ProviderType")).getValue().get(pType);
      cout << "  Type:      ";
      for (int j=0; j<pType.size(); j++)
        cout << " " << _providerType[ pType[j] ];
      cout << endl;
      
      // display state
      Array<Uint16> state;
      mod.getProperty(
              mod.findProperty("OperationalStatus")).getValue().get(state);
      cout << "  State:     ";
      for (int j=0; j<state.size(); j++)
        cout << " " << _providerState[ state[j] ];
      cout << endl;
      
      // display module
      cout << "  Module:     " << pMod << endl;

      // display file (PG_ProviderModule.Location)
      String loc;
      mod.getProperty(mod.findProperty("Location")).getValue().get(loc);
      cout << "  File:       lib" << loc << ".sl" << endl;
    }
  }

  catch (Exception &e)
  {
    cerr << e.getMessage() << endl;
    return 1;
  }

  return 0;
}