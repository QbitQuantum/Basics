void TquantTablesPageBase::create(HWND parent)
{
    createDialog(dialogId,parent);
    SetParent(m_hwnd,parent);
    setPos(0,0);
    show(true);
    matrixflnm[0]='\0';
    _makepath_s(matrixdir,MAX_PATH,NULL,config->pth,_l("custom matrices"),NULL);
    firstdir=true;
}