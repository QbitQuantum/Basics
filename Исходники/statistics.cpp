STDMETHODIMP_(BOOL) CStatistic::HaveInternetConnection()
{
    DWORD dwFlag;

    //	如果函数返回FALSE,则肯定没有连接
    if( InternetGetConnectedState(&dwFlag,0) )
    {
        //	必须有下列任意一种连接，才认为是有连接
        //	因为INTERNET_CONNECTION_CONFIGURED被置位也可能是没有连接
        if( (dwFlag&INTERNET_CONNECTION_LAN) ||
            (dwFlag&INTERNET_CONNECTION_MODEM) ||
            (dwFlag&INTERNET_CONNECTION_PROXY) )
            return TRUE;
    }

    return IsNetGatewayExists();
}