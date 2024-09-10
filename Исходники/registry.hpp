 static bool remove(const string& name) {
   lstring part = name.split("/");
   HKEY rootKey = root(part.take(0));
   string node = part.take();
   string path = part.merge("\\");
   if(node.empty()) return SHDeleteKeyW(rootKey, utf16_t(path)) == ERROR_SUCCESS;
   return SHDeleteValueW(rootKey, utf16_t(path), utf16_t(node)) == ERROR_SUCCESS;
 }