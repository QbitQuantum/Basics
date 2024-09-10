int _tmain(int argc, _TCHAR* argv[])
{
    if (argc > 1 && argv[1])
    {
        char path[1000] {};
        WideCharToMultiByte(CP_UTF8, 0, argv[1], -1, path, 1000, 0, 0);
        std::string out(path);
        out.append(".temp");
        if (MoveFileA(path, out.c_str()) == TRUE)
        {
            Parse(out, path);
            DeleteFileA(out.c_str());
        }
    }
    return 0;
}