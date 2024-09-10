size_t VMemoryManager_CRT::AlignedMemSize(void* ptr, int iAlignment)
{
  // Not all memory size functions cope with NULL pointer
  if(ptr == NULL)
    return 0;

#if defined(WIN32)  || defined (_VISION_XENON) 
#if defined(VBASE_USE_CRT_DEBUG)
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
  return _aligned_msize_dbg(ptr, iAlignment, 0);
#else
  return _msize_dbg(ptr, _NORMAL_BLOCK);//@@@@ VStudio < 2005 and code might be wrong
#endif
#else
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
  return _aligned_msize(ptr, iAlignment, 0);
#else
  return _msize(ptr);//@@@@ VStudio < 2005 and code might be wrong
#endif
#endif


#elif defined (_VISION_PS3)
  return malloc_usable_size(ptr);



#elif defined (_VISION_POSIX)
  return 0; // TODO: IOS

#elif defined (_VISION_PSP2)
  return malloc_usable_size(ptr);

#elif defined (_VISION_WIIU)
  return 0; // XXCK

#else
#error Undefined platform!
#endif
}