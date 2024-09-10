// 发送请求/响应的文件
bool CTyHttpSvr::SendResponseFile()
{
    string strFilePathName = m_strMainPath;
    strFilePathName += "/";
    strFilePathName += m_mapRequestKeyValue["RequestUrl"];

    if (SendResponseHead(strFilePathName.c_str()))
        return TransmitFile(strFilePathName.c_str());

    return false;
}