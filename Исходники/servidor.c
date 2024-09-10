int escuchaCliente(int socket, struct sockaddr_in addr)
{

    char buffer[BUFFERSIZE];
    char aux[BUFFERSIZE];
    int bytecount;
    int fin=0;
    int code=0;         /* Código de salida por defecto */
    time_t t;
    struct tm *tmp;
    socklen_t slen=sizeof(addr);
    while (!fin)
      {

    memset(buffer, 0, BUFFERSIZE);


       if((bytecount=recvfrom(socket,buffer,BUFFERSIZE,0,(struct sockaddr*)&addr,&slen))==-1)
       {
       error(5, "No puedo recibir información");
         }
printf("%s\n",buffer);
    /* Evaluamos los comandos */
    /* El sistema de gestión de comandos es muy rudimentario, pero nos vale */
    /* Comando TIME - Da la hora */
    if (strncmp(buffer, "TIME", 4)==0)
      {
        memset(buffer, 0, BUFFERSIZE);

        t = time(NULL);
        tmp = localtime(&t);
        strftime(buffer, BUFFERSIZE, "%Y-%m-%d %H:%M:%S", tmp);
      }
    
    /* Comando EXIT - Cierra la conexión actual */
    else if (strncmp(buffer, "EXIT", 4)==0)
      {
        memset(buffer, 0, BUFFERSIZE);
        sprintf(buffer, "Hasta luego. Vuelve pronto %s\n", inet_ntoa(addr.sin_addr));
        fin=1;
      }
    /* Comando CERRAR - Cierra el servidor */
    else if (strncmp(buffer, "CERRAR", 6)==0)
      {
        memset(buffer, 0, BUFFERSIZE);
        sprintf(buffer, "Adiós. Cierro el servidor\n");
        fin=1;
        code=99;        /* Salir del programa */
      }
    else
      {     
        sprintf(aux, "ECHO: %s\n", buffer);
        strcpy(buffer, aux);
      }

     if(bytecount = sendto(socket,buffer,strlen(buffer),0, (struct sockaddr*)&addr, sizeof(addr))==-1){
          error(6, "No puedo enviar información");
     }
}
 
    close(socket);
    return code;
}