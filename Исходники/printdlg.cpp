 BOOL Close()
 {
     BOOL result = TRUE;
     if( m_hPrinter )
     {
         result = ClosePrinter( m_hPrinter );
         m_hPrinter = (HANDLE)NULL;
     }
     return result;
 }