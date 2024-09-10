//
//   函数： GetProcessIntegrityLevel()
//
//   用途：此函数获取当前线程的完整性级别。完整性级别只有在Windows Vista及后
//   续版本的Windows中有效。所以在Windows Vista之前的版本中执行GetProcessIntegrityLevel， 
//   它会抛出一个C++异常。
//
//   返回值：返回当前进程的完整性级别。它可能是以下某一个值。
//
//     SECURITY_MANDATORY_UNTRUSTED_RID (SID: S-1-16-0x0)
//     表示不被信任的级别。它被用于一个匿名组成员起动的进程。这时大多数
//     写入操作被禁止。
//
//     SECURITY_MANDATORY_LOW_RID (SID: S-1-16-0x1000)
//     表示低完整性级别。它被用于保护模式下的IE浏览器。这时大多数系统中对
//     象（包括文件及注册表键值）的写入操作被禁止。
//
//     SECURITY_MANDATORY_MEDIUM_RID (SID: S-1-16-0x2000)
//     表示中完整性级别。它被用于在UAC开启时启动普通应用程序。
//
//
//     SECURITY_MANDATORY_HIGH_RID (SID: S-1-16-0x3000)
//     表示高完整性级别。它被用于用户通过UAC提升权限启动一个管理员应用程序。
//     或则当UAC关闭时，管理员用户启动一个普通程序。
//
//
//     SECURITY_MANDATORY_SYSTEM_RID (SID: S-1-16-0x4000)
//     表示系统完整性级别。它被用于服务或则其他系统级别的应用程序（比如
//     Wininit, Winlogon, Smss，等等）
//
//
//   异常：如果此函数出错，它抛出一个包含Win32相关错误代码的C++ DWORD异常。
//   比如在Windows Vista之前的Windows中调用GetProcessIntegrityLevel，被抛
//   出的错误代码为ERROR_INVALID_PARAMETER。
// 
//   调用示例：
//     try 
//     {
//         DWORD dwIntegrityLevel = GetProcessIntegrityLevel();
//     }
//     catch (DWORD dwError)
//     {
//         wprintf(L"GetProcessIntegrityLevel 失败 w/err %lu\n", dwError);
//     }
//
DWORD GetProcessIntegrityLevel()
{
    DWORD dwIntegrityLevel = 0;
    DWORD dwError = ERROR_SUCCESS;
    HANDLE hToken = NULL;
    DWORD cbTokenIL = 0;
    PTOKEN_MANDATORY_LABEL pTokenIL = NULL;

    // 使用TOKEN_QUERY打开线程的主访问令牌。
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    // 查询令牌完整性级别信息的大小。注意：我们预期得到一个FALSE结果及错误
    // ERROR_INSUFFICIENT_BUFFER， 这是由于我们在GetTokenInformation输入一个
    // 空缓冲。同时，在cbTokenIL中我们会得知完整性级别信息的大小。
    if (!GetTokenInformation(hToken, TokenIntegrityLevel, NULL, 0, &cbTokenIL))
    {
        if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
        {
            // 当进程运行于Windows Vista之前的系统中，GetTokenInformation返回
            // FALSE和错误码ERROR_INVALID_PARAMETER。这是由于这些操作系统不支
            // 持TokenElevation。
            dwError = GetLastError();
            goto Cleanup;
        }
    }

    // 现在我们为完整性级别信息分配一个缓存。
    pTokenIL = (TOKEN_MANDATORY_LABEL *)LocalAlloc(LPTR, cbTokenIL);
    if (pTokenIL == NULL)
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    // 获得令牌完整性级别信息。
    if (!GetTokenInformation(hToken, TokenIntegrityLevel, pTokenIL, 
        cbTokenIL, &cbTokenIL))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    // 完整性级别SID为S-1-16-0xXXXX形式。（例如：S-1-16-0x1000表示为低完整性
    // 级别的SID）。而且有且仅有一个次级授权信息。
    dwIntegrityLevel = *GetSidSubAuthority(pTokenIL->Label.Sid, 0);

Cleanup:
    // 集中清理所有已分配的内存资源

    if (hToken)
    {
        CloseHandle(hToken);
        hToken = NULL;
    }
    if (pTokenIL)
    {
        LocalFree(pTokenIL);
        pTokenIL = NULL;
        cbTokenIL = 0;
    }

    // 一旦有任何异常发生，抛出错误。
    if (ERROR_SUCCESS != dwError)
    {
        throw dwError;
    }

    return dwIntegrityLevel;
}