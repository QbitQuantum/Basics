void dumpAllImports()
{
  EnumerateLoadedModulesEx(GetCurrentProcess(), menum, NULL);
  dbg("dumpAllImports: done");
}