void * server_reciever_thread(void* arg)
{
 int len;  // recieved string lenght
 char buffer[200]; // buffer for recieved message

 // prevzeti vstupnich argumentu id clienta
 int new_fd =(int)arg;

 // tahani data z socketu a rozesilani vsem
 while ((len = recv(new_fd, buffer, sizeof(buffer)-1, 0)) > 0) 
 {
  buffer[len-2] = 0; /* mark end of string */

  long noveOtacky;
  char* p;
  noveOtacky = strtol(buffer, &p, 0);

  // prevod str na cislo
  if ((p == buffer) || *p)
  {
    //vypise na serveru ze to klient zadal blbe
    printf("Klient zadal nesmyslny pozadavek:%s\n",buffer);
    fflush(stdout);
    // odesli zpravu klientovi ze to zadal blbe
    const char msg[] = "Zadal jste nesmysl \n";
    send(new_fd, msg, strlen(msg), 0);
  }
  
  // kdyz to tedy cislo je
  else
  {
   // kontrola zda je to v mezich od -10000 do +10000
   if(noveOtacky<-10000  || noveOtacky>10000)
   {
    // oznameni na severu ze klient zadal cislo mimo rozsah
    printf("Klient zadal cislo mimo rozsah otacek: %d \n",(int)noveOtacky);
    fflush(stdout);
    // oznameni klintovi ze zadal moc velke cislo 
    const char msg[] = "Prilis vysoke otacky \n";
    send(new_fd, msg, strlen(msg), 0);
   }

   // kdyz je vse v poradku, tak se prepisy otacky
   else
   {
    pthread_mutex_lock(&mutex_demandRotates); 
      demandRotates = noveOtacky;
    pthread_mutex_unlock(&mutex_demandRotates); 
    printf("Klient zadal pozadavek na otacky: %d ot/min \n",(int)noveOtacky);
    fflush(stdout);
    // oznameni klientovi ze vse probehlo dobre a otacky se nastavily
    char msg[400]; 
    sprintf(msg,"Pozadovane otacky zmeneny na %d ot/min\n",(int)noveOtacky);
    send(new_fd, msg, strlen(msg), 0);
   }
  }

 }// konec cteci smycky, bude z ni vyskoceno kdyz neprijde zadny znak
 // coz je kdyz se klient odpoji

// oznameni se se muze ukoncit toto vlakno
pthread_mutex_lock(&mutex_isClientConnected); 
     printf("Klient se odpojil \n");
     fflush(stdout);
     isClientConnected = FALSE;
pthread_mutex_unlock(&mutex_isClientConnected); 

return NULL;
}