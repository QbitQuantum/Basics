static String buildFileName(const String& prefix,const Path& path)
{
   // Need to join the path (minus the root) with our
   // internal path name.
   String file = prefix;
   file = Path::Join(file,'/',path.getPath());
   file = Path::Join(file,'/',path.getFileName());
   file = Path::Join(file,'.',path.getExtension());
   return file;
}