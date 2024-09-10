//
// инициализация COM порта
//
BOOL CComPort::Initialize(const _TSTRING& i_sComPort,DWORD baud,BYTE parity,BYTE stopbit,char Dtr,char Rts)
{			
 m_sComPort = i_sComPort;
 return Initialize(baud,parity,stopbit,Dtr,Rts);
} 