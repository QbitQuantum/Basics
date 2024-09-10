bool
HostFolder::remove(const std::string &name)
{
   auto hostPath = mPath.join(name);
   auto winPath = platform::toWinApiString(hostPath.path());
   auto child = findChild(name);

   if (!child) {
      // File / Directory does not exist, nothing to do
      return true;
   }

   if (!checkPermission(Permissions::Write)) {
      return false;
   }

   auto removed = false;

   if (child->type() == NodeType::FileNode) {
      removed = !!DeleteFileW(winPath.c_str());
   } else if (child->type() == NodeType::FolderNode) {
      removed = !!RemoveDirectoryW(winPath.c_str());
   }

   if (removed) {
      mVirtual.deleteChild(child);
   }

   return removed;
}