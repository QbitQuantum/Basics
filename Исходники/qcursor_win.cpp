QCursorData::~QCursorData()
{
    delete bm;
    delete bmm;
#if !defined(Q_WS_WINCE) || defined(GWES_ICONCURS)
    if (hcurs)
        DestroyCursor(hcurs);
#endif
}