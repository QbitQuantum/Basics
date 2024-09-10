int wmain(int argc, wchar_t *argv[]) {
  auto git_args = create_git_arguments(argc, argv);
  auto git_cl = L"git " + git_args;
  
  int code = _wsystem(git_cl.c_str());
  print_error(errno);
  
  return code;
}