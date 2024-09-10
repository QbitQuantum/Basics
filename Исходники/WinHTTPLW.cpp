////////////////////////////////////////////////////////////
///
/// @brief 为应用程序创建一个会话对象、获取用户IE代理设置
///
/// @note 在应用程序开始时调用
///
/// @param void
///
/// @return HRESULT
///
/// @retval S_OK 正常返回
/// @retval 通过GetLastError()返回
///
////////////////////////////////////////////////////////////
HRESULT WinHTTPLW::Initialize()
{
    if (m_hSession == NULL)
    {
        m_hSession = ::WinHttpOpen(
            L"LeWei WinHTTP/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0
            );
    }

    if (m_hSession == NULL)
    {
        return HRESULT_FROM_WIN32(::GetLastError());
    }

    // 获取当前用户IE的代理设置
    if (!::WinHttpGetIEProxyConfigForCurrentUser(&m_ieProxyConfig))         
    {
        Uninitialize();

        return HRESULT_FROM_WIN32(::GetLastError());
    }

    WINHTTP_AUTOPROXY_OPTIONS autoProxyOptions = { 0 };

    // lpszAutoConfigUrl不为空表示钩选"使用自动配置脚本"，Internet Explorer将下载代理自动配置(PAC)文件来确定特定连接的代理服务器
    if (m_ieProxyConfig.lpszAutoConfigUrl != NULL)                                 
    {
        // fAutoDetect为true表示钩选"自动检测设置"，意味着Internet Explorer使用Web代理自动发现(WPAD)协议来查找代理设置。
        if (m_ieProxyConfig.fAutoDetect)
        {
            autoProxyOptions.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
            autoProxyOptions.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DHCP | 
                                                 WINHTTP_AUTO_DETECT_TYPE_DNS_A;
        }
        else
        {
            autoProxyOptions.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
            autoProxyOptions.lpszAutoConfigUrl = m_ieProxyConfig.lpszAutoConfigUrl;
        }

        // 获取当前的IE代理服务器信息
        if (!::WinHttpGetProxyForUrl(
            m_hSession,
            NULL,
            &autoProxyOptions,
            &m_proxyInfo))
        {
            Uninitialize();

            return HRESULT_FROM_WIN32(::GetLastError());
        }

        // 设置代理方式默认为IE代理
        if (!::WinHttpSetOption(
            m_hSession,
            WINHTTP_OPTION_PROXY,
            &m_proxyInfo,
            sizeof(m_proxyInfo)
            ))
        {
            Uninitialize();

            return HRESULT_FROM_WIN32(::GetLastError());
        }

    }
    else if (m_ieProxyConfig.lpszProxy != NULL)           
    {
        // 获取当前的IE代理服务器信息
        m_proxyInfo.dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
        m_proxyInfo.lpszProxy = m_ieProxyConfig.lpszProxy;
        m_proxyInfo.lpszProxyBypass = m_ieProxyConfig.lpszProxyBypass;

        // 设置代理方式默认为IE代理
        if (!::WinHttpSetOption(
            m_hSession,
            WINHTTP_OPTION_PROXY,
            &m_proxyInfo,
            sizeof(m_proxyInfo)
            ))
        {
            Uninitialize();
            
            return HRESULT_FROM_WIN32(::GetLastError());
        }
    }

    return S_OK;
}