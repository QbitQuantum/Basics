POTENTIAL_ROTTING_DOCUMENTATION
/*!
  This static function returns the SoType object associated with name \a name.

  Type objects for builtin types can be retreived by name both with and
  without the "So" prefix.  For dynamically loadable extension nodes, the
  name given to this function must match exactly.

  If no node type with the given name has been initialized, a dynamically
  loadable extension node with the given name is searched for.  If one is
  found, it is loaded and initialized, and the SoType object for the
  newly initialized class type returned.  If no module is found, or the
  initialization of the module fails, SoType::badType() is returned.

  Support for dynamically loadable extension nodes varies from
  platform to platform, and from compiler suite to compiler suite.

  So far code built with the following compilers are supported: GNU
  GCC v2-4, Microsoft Visual C++ v6, 2003, 2005 and 2008), SGI MIPSPro v7.

  Extensions built with compilers that are known to be binary
  compatible with the above compilers are also supported, such as
  e.g. the Intel x86 compiler compatible with MSVC++.

  To support dynamic loading for other compilers, we need to know how
  the compiler mangles the "static void classname::initClass(void)"
  symbol.  If your compiler is not supported, tell us at \c
  [email protected] which it is and send us the output of a
  symbol-dump on the shared object.  Typically you can do

  \code
  $ nm <Node>.so | grep initClass
  \endcode

  to find the relevant mangled symbol.
*/
SoType
SoType::fromName(const SbName name)
{
  static int enable_dynload = -1;
  if (enable_dynload == -1) {
    enable_dynload = TRUE; // the default setting
    const char * env = coin_getenv("COIN_NO_SOTYPE_DYNLOAD");
    if (env && atoi(env) > 0) enable_dynload = FALSE;
  }

  assert((type_dict != NULL) && "SoType static class data not yet initialized");

  // It should be possible to specify a type name with the "So" prefix
  // and get the correct type id, even though the types in some type
  // hierarchies are named internally without the prefix.
  SbString tmp(name.getString());
  if ( tmp.compareSubString("So") == 0 ) tmp = tmp.getSubString(2);
  SbName noprefixname(tmp);

  int16_t index = 0;
  if (!type_dict->get(name.getString(), index) &&
      !type_dict->get(noprefixname.getString(), index)) {
    if ( !SoDB::isInitialized() ) {
      return SoType::badType();
    }

    if (enable_dynload) {

      // find out which C++ name mangling scheme the compiler uses
      static mangleFunc * manglefunc = getManglingFunction();
      if ( manglefunc == NULL ) {
        // dynamic loading is not yet supported for this compiler suite
        static long first = 1;
        if ( first ) {
          const char * env = coin_getenv("COIN_DEBUG_DL");
          if (env && (atoi(env) > 0)) {
            SoDebugError::post("SoType::fromName",
                               "unable to figure out the C++ name mangling scheme");
          }
          first = 0;
        }
        return SoType::badType();
      }
      SbString mangled = manglefunc(name.getString());

      if ( module_dict == NULL ) {
        module_dict = new Name2HandleMap;
      }

      // FIXME: should we search the application code for the initClass()
      // symbol first?  dlopen(NULL) might not be portable enough, but it
      // could be a cool feature.  20030223 larsa

      // FIXME: We probably should use loadable modules (type MH_BUNDLE)
      // instead of shared libraries for dynamic extension nodes, on Mac
      // OS X, since (1) this is the Recommended Way for dynamically
      // loadable code and (2) it allows us to unload them when they are
      // no longer needed. Note that this would require major changes to
      // the Mac cc_dl_open() and cc_dl_sym() code. 20030318 kyrah

      static const char * modulenamepatterns[] = {
        "%s.so", "lib%s.so", "%s.dll", "lib%s.dll", "%s.dylib", "lib%s.dylib",
        NULL
      };

      SbString modulenamestring;
      cc_libhandle handle = NULL;
      int i;
      for ( i = 0; (modulenamepatterns[i] != NULL) && (handle == NULL); i++ ) {
        modulenamestring.sprintf(modulenamepatterns[i], name.getString());

        // We need to move the name string to an SbName since we use
        // the name string pointer for hash tables and need identical
        // names to produce the same pointers.
        SbName module(modulenamestring.getString());

        // Register all the module names we have tried so we don't try
        // them again.
        if (dynload_tries == NULL) dynload_tries = new NameMap;
        void * dummy;
        if (dynload_tries->get(module.getString(), dummy))
          continue; // already tried
        dynload_tries->put(module.getString(), NULL);

        cc_libhandle idx = NULL;
        if ( module_dict->get(module.getString(), idx) ) {
          // Module has been loaded, but type is not yet finished initializing.
          // SoType::badType() is here the expected return value.  See below.
          return SoType::badType();
        }

        // FIXME: should we maybe use a Coin-specific search path variable
        // instead of the LD_LIBRARY_PATH one?  20020216 larsa

        handle = cc_dl_open(module.getString());
        if ( handle != NULL ) {
          // We register the module so we don't recurse infinitely in the
          // initClass() function which calls SoType::fromName() on itself
          // which expects SoType::badType() in return.  See above.
          module_dict->put(module.getString(), handle);

          if (i > 0) {
            // We now know the file pattern used on this system, so we
            // should prioritize that pattern first.
            const char * pattern = modulenamepatterns[i];
            modulenamepatterns[i] = modulenamepatterns[0];
            modulenamepatterns[0] = pattern;
          }
        }
      }

      if ( handle == NULL ) return SoType::badType();

      // find and invoke the initClass() function.
      // FIXME: declspec stuff
      initClassFunction * initClass = (initClassFunction *) cc_dl_sym(handle, mangled.getString());
      if ( initClass == NULL ) {
        // FIXME: if a module is found and opened and initialization
        // fails, the remaining module name patterns are not tried.
        // might trigger as a problem one day...  2030224 larsa
#if COIN_DEBUG
        SoDebugError::postWarning("SoType::fromName",
                                  "Mangled symbol %s not found in module %s. "
                                  "It might be compiled with the wrong compiler / "
                                  "compiler-settings or something similar.",
                                  mangled.getString(), modulenamestring.getString());
#endif
        cc_dl_close(handle);
        return SoType::badType();
      }

      initClass();

      // We run these tests to get the index.
      if (!type_dict->get(name.getString(), index) &&
          !type_dict->get(noprefixname.getString(), index)) {
        assert(0 && "how did this happen?");
      }
    }
  }

  assert(index >= 0 && index < SoType::typedatalist->getLength());
  assert(((*SoType::typedatalist)[index]->name == name) ||
         ((*SoType::typedatalist)[index]->name == noprefixname));
  return (*SoType::typedatalist)[index]->type;
}