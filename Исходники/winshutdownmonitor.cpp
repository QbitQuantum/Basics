void winshutdownmonitor::registershutdownblockreason(const qstring& strreason, const hwnd& mainwinid)
{
    typedef bool (winapi *pshutdownbrcreate)(hwnd, lpcwstr);
    pshutdownbrcreate shutdownbrcreate = (pshutdownbrcreate)getprocaddress(getmodulehandlea("user32.dll"), "shutdownblockreasoncreate");
    if (shutdownbrcreate == null) {
        qwarning() << "registershutdownblockreason: getprocaddress for shutdownblockreasoncreate failed";
        return;
    }

    if (shutdownbrcreate(mainwinid, strreason.tostdwstring().c_str()))
        qwarning() << "registershutdownblockreason: successfully registered: " + strreason;
    else
        qwarning() << "registershutdownblockreason: failed to register: " + strreason;
}