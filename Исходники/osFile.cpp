int64_t File::getSize()
{
   int64_t retSize = 0;
   getFileSize( _name, retSize );
   return retSize;
}