/* 编译从这开始 */
int main (int argc, char **argv)
{
    int i;

	//share_fs ();

    CurrentHeap = &ProgramHeap;
    argc--; argv++;

#if defined(_LF)
    init_file_layout ();
    init_memory_layout ();
#endif
    CreateLogFile ();

#if 1
    i = ParseCommandLine (argc, argv);
    
    /* 初始化词法分析器 */
    SetupLexer ();
    /* 按照配置文件设置基本类型和默认函数的属性 */
    SetupTypeSystem ();

    for ( ; i < argc; i++ ) {
    
        Compile (argv[i]);
    }
#endif
    CloseLogFile ();
    return (ErrorCount != 0 ? -1 : 0);
}