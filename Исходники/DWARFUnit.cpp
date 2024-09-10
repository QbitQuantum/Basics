static FileSpec resolveCompDir(const FileSpec &path) {
  bool is_symlink = SymbolFileDWARF::GetSymlinkPaths().FindFileIndex(
                        0, path, /*full*/ true) != UINT32_MAX;

  if (!is_symlink)
    return path;

  namespace fs = llvm::sys::fs;
  if (fs::get_file_type(path.GetPath(), false) != fs::file_type::symlink_file)
    return path;

  FileSpec resolved_symlink;
  const auto error = FileSystem::Instance().Readlink(path, resolved_symlink);
  if (error.Success())
    return resolved_symlink;

  return path;
}