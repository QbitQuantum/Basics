/**
 * @brief 运行进程函数
 * 创建经编译的代码的可执行文件进程
 *
 * @param exe 可执行文件文件名
 * @param input 进程输入文件名
 * @param output 进程输出文件名
 * @param cs 用于接收代码状态的引用
 * @param hInput 用于接收输入文件句柄
 * @param hOutput 用于接收输出文件句柄
 * @return 若进程创建成功则返回进程句柄，否则返回NULL
 */
HANDLE CNBUTOJCore::RunCode(const char *exe, const char *input, const char *output, CodeState &cs, HANDLE &hInput, HANDLE &hOutput, PROCESS_INFORMATION &inProcInfo)
{
    SECURITY_ATTRIBUTES sa;
    sa.bInheritHandle = true;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;

    /** 打开得到输入输出文件句柄 */
    hInput = hOutput = NULL;
    hInput = CreateFile(input, GENERIC_READ, NULL, &sa, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    hOutput = CreateFile(output, GENERIC_WRITE | GENERIC_READ, NULL,
        &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    //HANDLE hError = CreateFile(".err", GENERIC_WRITE | GENERIC_READ, NULL,
    //    &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(NULL == hInput || NULL == hOutput)
    {
        cs.state = SYSTEM_ERROR;
        strcpy(cs.err_code, "File error.");

        return NULL;
    }

    PROCESS_INFORMATION ProcInfo;
    STARTUPINFO StartInfo = { sizeof(StartInfo) };
    StartInfo.cb = sizeof(StartInfo);
    StartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    StartInfo.hStdInput = hInput;
    StartInfo.hStdOutput = hOutput;
    StartInfo.wShowWindow = SW_HIDE;
    //StartInfo.hStdError = hError;

    /** 运行程序 */
    bool flag = CreateProcessA(exe, NULL, NULL,
        NULL, true, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &StartInfo, &ProcInfo);

    /** 若运行不成功 */
    if(!flag)
    {
        cs.state = SYSTEM_ERROR;
        strcpy(cs.err_code, "Can't create process.");

        return NULL;
    }

    cs.state = RUNNING;
    inProcInfo = ProcInfo;

    return ProcInfo.hProcess;
}