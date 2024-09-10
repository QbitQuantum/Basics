bool BinaryDataMMAP::createMMAP(string filename)
{
   size_ = getFilesize(filename);
   if( size_==FILE_DOES_NOT_EXIST )
      return false;

   fileDescriptor_ = open(filename.c_str(), O_RDONLY);
   if(fileDescriptor_ == -1)
   {
      cout << "***ERROR: file to be mmap'd exists, but could not be read" << endl;
      return false;
   }

   ptr_ = (uint8_t*)mmap(NULL, size_, PROT_READ, MAP_SHARED, fileDescriptor_, 0);
   if(ptr_ == MAP_FAILED)
   {
      close(fileDescriptor_);
      cout << "***ERROR: mmap'ing file failed, despite exist w/ read access." << endl;
      return false;
   }
   
   // Usually we will be scanning the whole file, sequentially, after mmapping
   setAdvice(MADV_SEQUENTIAL);
   return true; 
}