/*=================================================================
* Function ID :  GetEventMask
* Input       :  void
* Output      :  DWORD& dwMask
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE/FALSE
* Description :  设置超时时间
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CComSmart::GetEventMask(DWORD& dwMask)
{
	if( !GetCommMask(m_handle, &dwMask) )
	{
		sprintf(m_szErrorText,"GetEventMask()出错[%ld]!", GetLastError());
		return false;		
	}
	return true;	
}