//[BUGFIX]-Add-BEGIN by TCTNB.Ruili.Liu,04/08/2014,PR629105,
//Can not display Chinese SSID by GBK  normal
void parseSsid(String16& str, const char *reply)
{
    unsigned int lineBeg = 0, lineEnd = 0;
    size_t  replyLen = strlen(reply);
    char    *pos = NULL;
    char    ssid[BUF_SIZE] = {0};
    char    ssid_utf8[BUF_SIZE] = {0};
    char    ssid_txt[BUF_SIZE] ={0};
    bool    isUTF8 = false, isCh = false;
    char    buf[BUF_SIZE] = {0};
    String8 line;

    UConverterType conType = UCNV_UTF8;
    char dest[CONVERT_LINE_LEN] = {0};
    UErrorCode err = U_ZERO_ERROR;
    UConverter* pConverter = ucnv_open(CHARSET_CN, &err);
    if (U_FAILURE(err)) {
        ALOGE("ucnv_open error");
        return;
    }
    /* Parse every line of the reply to construct accessPointObjectItem list */
    for (lineBeg = 0, lineEnd = 0; lineEnd <= replyLen; ++lineEnd) {
        if (lineEnd == replyLen || ' ' == reply[lineEnd]) {
            line.setTo(reply + lineBeg, lineEnd - lineBeg + 1);
            if (DBG)
                ALOGD("%s, line=%s ", __FUNCTION__, line.string());
            if (strncmp(line.string(), "SSID=", 5) == 0) {
                sscanf(line.string() + 5, "%[^\n]", ssid);
                ssid_decode(buf,BUF_SIZE,ssid);
                isUTF8 = isUTF8String(buf,sizeof(buf));
                isCh = false;
                for (pos = buf; '\0' != *pos; pos++) {
                    if (0x80 == (*pos & 0x80)) {
                        isCh = true;
                        break;
                    }
                }
                if (DBG)
                    ALOGD("%s, ssid = %s, buf = %s,isUTF8= %d, isCh = %d",
                        __FUNCTION__, ssid, buf ,isUTF8, isCh);
                if (!isUTF8 && isCh) {
                    ucnv_toAlgorithmic(conType, pConverter, dest, CONVERT_LINE_LEN,
                                buf, strlen(buf), &err);
                    if (U_FAILURE(err)) {
                        ALOGE("ucnv_toUChars error");
                        goto EXIT;
                    }
                    ssid_encode(ssid_txt, BUF_SIZE, dest, strlen(dest));
                    if (DBG)
                        ALOGD("%s, ssid_txt = %s", __FUNCTION__,ssid_txt);
                    str += String16("SSID=");
                    str += String16(ssid_txt);
                    str += String16("\n");
                    strncpy(ssid_utf8, dest, strlen(dest));
                    memset(dest, 0, CONVERT_LINE_LEN);
                    memset(ssid_txt, 0, BUF_SIZE);
                } else {
                    memset(buf, 0, BUF_SIZE);
                    str += String16(line.string());
                }
            }
            if (strncmp(line.string(), "SSID=", 5) != 0)
                str += String16(line.string());
            lineBeg = lineEnd + 1;
        }
    }
EXIT:
    ucnv_close(pConverter);
}