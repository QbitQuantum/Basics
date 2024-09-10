 EEnum GetPathType(const UString &path)
 {
   if (path.Length() <= 2)
     return kLocal;
   if (path[0] == kDirDelimiter && path[1] == kDirDelimiter)
     return kUNC;
   return kLocal;
 }