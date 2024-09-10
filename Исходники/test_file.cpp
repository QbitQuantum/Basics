 int openHelper ()
 {
  return  tfile->openFile (fname.c_str (), File::WRITE
                           | File::READ
                           | File::NO_CACHE_STAT
                           | File::FILE_OPEN_ALWAYS);
 }