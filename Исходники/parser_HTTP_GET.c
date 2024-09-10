int main(void){
    
    int server_Socket, accept_Socket;
    unsigned int length, count;
    struct sockaddr_in server_Struct, client_Struct;
    char got_charachter[1000];
    char web_Site[]="HTTP/1.1 200 OK\r\n\r\n";
    unsigned short int port_No=5000;
    char *position_of_GET,*position_of_HTTP;
    char nameof_File[100];
    
    server_Socket=socket(AF_INET,SOCK_STREAM,0);
    
    
    server_Struct.sin_family=AF_INET;
    server_Struct.sin_addr.s_addr=htonl(INADDR_ANY);
    server_Struct.sin_port=htons(port_No);
    length=sizeof(server_Struct);
   
    
    printf("\n Server is now binding....");
    bind(server_Socket,(struct sockaddr *)&server_Struct,length);
   
    printf("\n Server listen....");
    //printf("\n Server mit IP %s on port %d ",ip_Adress,port_No);
    listen(server_Socket,5);
    
    while(1){
        
        printf("\n Server accept.....");
        fflush(stdout);
        accept_Socket=accept(server_Socket,(struct sockaddr *)&client_Struct, &length);
      
        printf(" connected to %s",inet_ntoa(client_Struct.sin_addr));
        
        count=read(accept_Socket,got_charachter,sizeof(got_charachter));
        got_charachter[count]=0;
        printf("server got the charachters %s",got_charachter);
        
        
       if(position_of_GET=strstr(got_charachter,"GET"))
       {
         printf("\n GET command start at char %ld\n\n",(position_of_GET-got_charachter)+1);
              if(position_of_HTTP=strstr(got_charachter,"HTTP"))
              {
                printf("\n GET command start at char %ld\n\n",(position_of_HTTP-got_charachter)+1);
                length=position_of_HTTP-position_of_GET-6;
                strncpy(nameof_File,position_of_GET+4,length+1);
                nameof_File[length+1]=0;
                printf("\n The name of File you asked for %s is not available at this moment",nameof_File);
              }
                else
              {
                      printf("\n HTTP has no HTTP \n\n");
              }
       }
       else
       {
           printf("\n HTTP has no GET \n\n");
       }
       
       printf("\n\n\n");
        write(accept_Socket,web_Site,sizeof(web_Site));
        printf("\n\n server close()....");
        close(accept_Socket);
    
        
        
        
    }

    
    
    
    
    return (0);
}