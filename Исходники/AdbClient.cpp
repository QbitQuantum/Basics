Error AdbClient::ShellToFile(const char *command, uint32_t timeout_ms,
                             const FileSpec &output_file_spec) {
  std::vector<char> output_buffer;
  auto error = internalShell(command, timeout_ms, output_buffer);
  if (error.Fail())
    return error;

  const auto output_filename = output_file_spec.GetPath();
  std::ofstream dst(output_filename, std::ios::out | std::ios::binary);
  if (!dst.is_open())
    return Error("Unable to open local file %s", output_filename.c_str());

  dst.write(&output_buffer[0], output_buffer.size());
  dst.close();
  if (!dst)
    return Error("Failed to write file %s", output_filename.c_str());
  return Error();
}