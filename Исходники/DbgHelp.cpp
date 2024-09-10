DbgHelp::~DbgHelp()
{
  try
  {
    boost::mutex::scoped_lock lock(mInstanceMutex);

    // Unload all modules loades to free memory
    if (!SymEnumerateModules64(unloadModule, this))
    {
      std::cerr << "~DbgHelp(), SymEnumerateModules64 failed, GetLastError = " <<  GetLastError();

    }

    // Let dbgHelp release resources
    if(!SymCleanup())
    {
      std::cerr << "~DbgHelp(), SymCleanup failed, GetLastError = " <<  GetLastError();
    }

    // Unload dbgHelp.dll
    ::FreeLibrary(mDbgHelp);
  }
  catch(...)
  {
    // better safe than sorry...
  }
}