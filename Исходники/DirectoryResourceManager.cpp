DirectoryResource*
DirectoryResourceManager::findFilename(const char* fullName ///< full path to a file
                                       )
{
   OsPath fullFileName(fullName);
   UtlString dirName  = fullFileName.getDirName();
   UtlString fileName;

   fileName.append(fullName, dirName.length(), UtlString::UTLSTRING_TO_END);
   dirName.strip(UtlString::trailing, OsPath::separator[0]);

   DirectoryResource* found = NULL;
   
   Os::Logger::instance().log(FAC_SUPERVISOR, PRI_DEBUG,
                 "DirectoryResourceManager::findFilename: path '%s' file '%s'",
                 dirName.data(), fileName.data());

   {
      OsLock tableMutex(mDirectoryResourceTableLock);
      UtlSListIterator directories(mDirectoryResourceTable);
      DirectoryResource* dir;
   
      while (!found
             && (dir = dynamic_cast<DirectoryResource*>(directories.findNext(&dirName))))
      {
         if ( dir->matches(fileName) )
         {
            found = dir;
         }
      }
   }

   if (found)
   {
      UtlString matched;
      found->appendDescription(matched);
      Os::Logger::instance().log(FAC_SUPERVISOR, PRI_DEBUG,
                    "DirectoryResourceManager::findFilename: '%s' matches %s",
                    fullName, matched.data());
   }
   else
   {
      Os::Logger::instance().log(FAC_SUPERVISOR, PRI_WARNING,
                    "DirectoryResourceManager::findFilename: no match found for '%s'",
                    fullName);
   }
   
   return found;
}