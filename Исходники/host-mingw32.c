static int
mingw32_gt_pch_use_address (void *addr, size_t size, int fd,
			    size_t offset)
{
  void * mmap_addr;
  HANDLE mmap_handle;

  /* Apparently, MS Vista puts unnamed file mapping objects into Global
     namespace when running an application in a Terminal Server
     session.  This causes failure since, by default, applications 
     don't get SeCreateGlobalPrivilege. We don't need global
     memory sharing so explicitly put object into Local namespace.

     If multiple concurrent GCC processes are using PCH functionality,
     MapViewOfFileEx returns "Access Denied" error.  So we ensure the
     session-wide mapping name is unique by appending process ID.  */

#define OBJECT_NAME_FMT "Local\\MinGWGCCPCH-"

  char* object_name = NULL;
  /* However, the documentation for CreateFileMapping says that on NT4
     and earlier, backslashes are invalid in object name.  So, we need
     to check if we are on Windows2000 or higher.  */
  OSVERSIONINFO version_info;
  version_info.dwOSVersionInfoSize = sizeof (version_info);

  if (size == 0)
    return 0; 

  /* Offset must be also be a multiple of allocation granularity for
     this to work.  We can't change the offset. */ 
  if ((offset & (va_granularity - 1)) != 0 || size > pch_VA_max_size)
    return -1;


  /* Determine the version of Windows we are running on and use a
     uniquely-named local object if running > 4.  */
  GetVersionEx (&version_info);
  if (version_info.dwMajorVersion > 4)
    {
      char local_object_name [sizeof (OBJECT_NAME_FMT)
			      + sizeof (DWORD) * 2];
      snprintf (local_object_name, sizeof (local_object_name),
		OBJECT_NAME_FMT "%lx", GetCurrentProcessId());
      object_name = local_object_name;
    }
     
  mmap_handle = CreateFileMappingA ((HANDLE) _get_osfhandle (fd), NULL,
				    PAGE_WRITECOPY | SEC_COMMIT, 0, 0,
				    object_name);

  if (mmap_handle == NULL)
    {
      w32_error (__FUNCTION__,  __FILE__, __LINE__, "CreateFileMapping");
      return -1; 
    }
  mmap_addr = MapViewOfFileEx (mmap_handle, FILE_MAP_COPY, 0, offset,
			       size, addr);
  if (mmap_addr != addr)
    {
      w32_error (__FUNCTION__, __FILE__, __LINE__, "MapViewOfFileEx");
      CloseHandle(mmap_handle);
      return  -1;
    }

  return 1;
}