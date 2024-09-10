//请求返回后，调用回调函数
void BaseHTTPRequestHandler::invokeResponseCallback(char *buf,size_t len) {

    CALLBACK_DATA callback_data;
    if(buf == NULL || len == 0)
        return;

    if(IsBadReadPtr(buf,len))
        return;

    memset(&callback_data, 0, sizeof(CALLBACK_DATA));
    callback_data.buf=(char*)malloc(len);
    memset(callback_data.buf,0,len);
    memcpy_s(callback_data.buf,len,buf,len);

    m_pHttpService_Params->response_callback(&callback_data);

    //处理完之后，清理掉内存
    if (callback_data.buf != NULL) {
        free(callback_data.buf);
        callback_data.buf = NULL;
    }
}