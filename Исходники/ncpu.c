int
cpu_count()
{
  SYSTEM_INFO si;

  GetNativeSystemInfo( &si );
  return (int)si.dwNumberOfProcessors;
}