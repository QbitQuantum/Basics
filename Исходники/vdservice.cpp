int main(void)
{
   int argc;
   TCHAR** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
   return _tmain(argc, argv);
}