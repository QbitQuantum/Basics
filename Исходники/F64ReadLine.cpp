void F64ReadLine::TestEnc(void)
{
    if(Args.getSourceCodepage() != NO_CODEPAGE) return;

    char* buf = new char[MEMPROTECT(32768)];
    int size = 0;
    setpointer(0);
    ReadFile(hFile, buf, 32768, (LPDWORD)&size, NULL);
    do {
        if(size > 2) { // 逆天等级的 bug 发现! 非 unsigned 情况下, 0xFF 和 '\xFF' 不同!
            if(buf[0] == '\xEF' && buf[1] == '\xBB' && buf[2] == '\xBF') {
                Args.setSourceCodepage(codepage = 65001);
                setpointer(3);
                break;
            }
        }
        if(size > 1) {
            if(buf[0] == '\xFF' && buf[1] == '\xFE') {
                Args.setSourceCodepage(codepage = 1200);
                setpointer(2);
                break;
            }
            if(buf[0] == '\xFE' && buf[1] == '\xFF') {
                Args.setSourceCodepage(codepage = 1201);
                setpointer(2);
                break;
            }
            if(TRUE == IsTextUnicode(buf, 32768, NULL)) {
                Args.setSourceCodepage(codepage = 1200);
                setpointer(2);
                break;
            }
        }
        if(isutf8(buf, 32768)) {
            Args.setSourceCodepage(codepage = 65001);
            setpointer(0);
            break;
        }
        Args.setSourceCodepage(codepage = GetACP());
        setpointer(0);
        break;
    } while(0);
    delete [] buf;
}