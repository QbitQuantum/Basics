bool FrUnmapFile(FrFileMapping *fmap)
{
   if (!fmap)
      return false ;
   bool success = true ;
#if defined(unix) || defined(__linux__) || defined(__GNUC__)
   success = (munmap(fmap->map_address,fmap->map_length) == 0) ;
   (void)VALGRIND_MAKE_MEM_NOACCESS(fmap->map_address,fmap->map_length) ;
#elif defined(__WINDOWS__) || defined(__NT__)
   (void)FlushViewOfFile((LPVOID)fmap->map_address,0) ;
   if (!UnmapViewOfFile((LPVOID)fmap->map_address))
      success = false ;
   CloseHandle(fmap->hMap) ;
#endif /* unix, Windows||NT */
   FramepaC_num_memmaps-- ;
   FramepaC_total_memmap_size -= fmap->map_length ;
   delete fmap ;
   return success ;
}