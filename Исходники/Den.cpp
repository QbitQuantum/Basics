 FileWrapper & operator= (FileWrapper &fw)
 {
     if (&fw == this) {
         return *this;
     }
     if (fw_file) {
         fw_file->unlink();
         if (!fw_file->ref_count) {
             delete fw_file;
         }
     }
     fw_file = fw.fw_file;
     fw_file->ref_count++;
     return *this;
 }