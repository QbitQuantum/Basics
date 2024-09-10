int main()
{
  char* pgmptr = nullptr;
  auto errcode = _get_pgmptr(&pgmptr); // pgmptr is now empty string, errcode 0
  std::cout << "pgmptr: \"" << pgmptr << "\" (error code: " << errcode << ")\n";

  char modulename[MAX_PATH];
  GetModuleFileNameA(nullptr, modulename, MAX_PATH); // modulename is correct
  std::cout << "GetModuleFileName: \"" << modulename << "\"\n";

  std::system("pause");

  return 0;
}