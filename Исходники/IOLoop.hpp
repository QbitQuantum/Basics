 void Set(FileDescriptor fd, unsigned mask, FileEventHandler &handler) {
   if (mask != 0)
     Add(fd, mask, handler);
   else
     Remove(fd);
 }