int patch_connect()
{
  char str[2048];
  
  HMODULE m = GetModuleHandle( "ws2_32.dll" );
  if( !m )
  {
    MessageBox( 0, "No Module handle for ws2_32.dll", "error", MB_OK );
    return 0;
  }
  
  volatile FARPROC cptr = GetProcAddress( m, "connect" );
  volatile unsigned char *data = (volatile unsigned char *)cptr;
  
  if( !cptr )
  {
    MessageBox( 0, "no address for connect", "error", MB_OK  );
    return 0;
  }
  sprintf( str, "address of connect is 0x%08lx", (DWORD)data );
  MessageBox( 0, str, "info", MB_OK );
  
  DWORD oldProtect;
  if( !VirtualProtect( (void*)cptr, 4096, PAGE_EXECUTE_WRITECOPY, &oldProtect ) )
  {		
    if( !VirtualProtect( (void*)cptr, 4096, PAGE_EXECUTE_READWRITE, &oldProtect ) )
    {
      MessageBox( 0, "VirtualProtect failed", "error", MB_OK );					
      return 0;
    }		
  }
  
  hook_connect_reentry = ((DWORD)(data))+8;
  sprintf( str,"reentry=%08lx", hook_connect_reentry );
  MessageBox(0,str,"INFO",MB_OK );
  
  sprintf( str, "original: %02x %02x %02x %02x %02x %02x %02x %02x",
           data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7] 
    );
  MessageBox( 0, str, "info", MB_OK );
  
  data[0] = 0xff; /* long jump, indirect */
  data[1] = 0x25;
  DWORD *jmpaddr = (DWORD *)(data+2);
  *jmpaddr = (DWORD)&hook_connect_entry;
  
  sprintf( str, "new: %02x %02x %02x %02x %02x %02x %02x %02x",
           data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7] 
    );
  MessageBox( 0, str, "info", MB_OK );
  
  
  /*
    DWORD other;
    if( !VirtualProtect( cptr, 4096, oldProtect, &other ) )
    {
    MessageBox( 0, "SecondVirtualProtect failed", "error", MB_OK );
    return 0;
    }
  */
  
  return 1;	
}