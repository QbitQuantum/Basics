 /**
     \fn ADM_copyFile
 */
 uint8_t ADM_renameFile(const char *source, const char *target)
 {

     int sourceFileNameLength = utf8StringToWideChar(source, -1, NULL);
     int targetFileNameLength = utf8StringToWideChar(target, -1, NULL);
     wchar_t *wcFileSource=(wchar_t*)_alloca(sourceFileNameLength*sizeof(wchar_t));
     wchar_t *wcFileTarget= (wchar_t*)_alloca(targetFileNameLength * sizeof(wchar_t));

     utf8StringToWideChar(source, -1, wcFileSource);
     utf8StringToWideChar(target, -1, wcFileTarget);

     if(!_wrename(wcFileSource,wcFileTarget)) return true;
     ADM_error("Failed to rename %s to %s\n",source,target);
     return false;
 }