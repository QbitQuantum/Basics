void
BaseCamAdapter::
showParameters(String8 const& param) const
{
    static char bufParam[4096];

    const int count = 768;
    char *pbuf = bufParam;
    char ch;
    uint32_t len;
    uint32_t i, loop;

    pbuf[0] = 0;
    len = param.length();
    if ( len > 4096) {
        len = 4096;
    }

    ::strcpy(pbuf, param.string());
    loop = (len + count - 1) / count;

    CAM_LOGD("[showParameters]: %d, %d \n", loop, len);
    for (i = 0; i < loop; i++) {
        ch = pbuf[count];
        pbuf[count] = 0;
        CAM_LOGD("(%s) \n", pbuf);
        pbuf[count] = ch;
        pbuf += count;
    }
}