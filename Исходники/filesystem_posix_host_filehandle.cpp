bool
HostFileHandle::flush()
{
   decaf_check(mHandle);
   return !!fflush(mHandle);
}