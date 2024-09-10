int64 FileDescriptorDataIO :: GetPosition() const
{
   int fd = _fd.GetFileDescriptor();
   if (fd >= 0)
   {
#ifdef MUSCLE_USE_LLSEEK
      loff_t spot;
      return (_llseek(fd, 0, 0, &spot, SEEK_CUR) == 0) ? spot : -1; 
#else
      return lseek(fd, 0, SEEK_CUR);
#endif
   }
   return -1;
}