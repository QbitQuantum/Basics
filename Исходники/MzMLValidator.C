 //reimplemented in order to remove the "indexmzML" tag from the front (if present)
 String MzMLValidator::getPath_(UInt remove_from_end) const
 {
   String path;
   if (open_tags_.size() != 0 && open_tags_.front() == "indexedmzML")
   {
     path.concatenate(open_tags_.begin() + 1, open_tags_.end() - remove_from_end, "/");
   }
   else
   {
     path.concatenate(open_tags_.begin(), open_tags_.end() - remove_from_end, "/");
   }
   path = String("/") + path;
   return path;
 }