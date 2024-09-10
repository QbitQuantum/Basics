static Error save_socket_id_to_file(const std::string &socket_id,
                                    const FileSpec &file_spec) {
  FileSpec temp_file_spec(file_spec.GetDirectory().AsCString(), false);
  auto error = FileSystem::MakeDirectory(temp_file_spec,
                                         eFilePermissionsDirectoryDefault);
  if (error.Fail())
    return Error("Failed to create directory %s: %s",
                 temp_file_spec.GetCString(), error.AsCString());

  llvm::SmallString<PATH_MAX> temp_file_path;
  temp_file_spec.AppendPathComponent("port-file.%%%%%%");
  auto err_code = llvm::sys::fs::createUniqueFile(temp_file_spec.GetCString(),
                                                  temp_file_path);
  if (err_code)
    return Error("Failed to create temp file: %s", err_code.message().c_str());

  llvm::FileRemover tmp_file_remover(temp_file_path.c_str());

  {
    std::ofstream temp_file(temp_file_path.c_str(), std::ios::out);
    if (!temp_file.is_open())
      return Error("Failed to open temp file %s", temp_file_path.c_str());
    temp_file << socket_id;
  }

  err_code = llvm::sys::fs::rename(temp_file_path.c_str(), file_spec.GetPath());
  if (err_code)
    return Error("Failed to rename file %s to %s: %s", temp_file_path.c_str(),
                 file_spec.GetPath().c_str(), err_code.message().c_str());

  tmp_file_remover.releaseFile();
  return Error();
}