//---------------------------------------------------------------------------
__fastcall CTA5Serial::CTA5Serial(int nPort)
{
    m_bInitOK=OpenPort(nPort);

    m_dX[0]=0.0;
    m_dX[1]=0.0;
    m_dY[0]=0.0;
    m_dY[1]=0.0;
}