/* ------------------------------------------------------------------ */
int Skt4uCleanup (void)
{
int Ark;

   if (bInitDone)
     {
       /* blocking call ? */
       if (WSAIsBlocking())  
        {
           WSACancelBlockingCall (); 
           return TCP4U_ERROR; 
         }
       else 
        {
          /* TcpClose (&s) force s a -1 -> pas besoin de UnrcdSkt */
          for (Ark=0 ; Ark<SizeOfTab(HistoSocket) ; Ark++)
             if (    HistoSocket[Ark].hTask == GetCurrentTask () 
                  && HistoSocket[Ark].skt   != INVALID_SOCKET )
                  TcpClose (& HistoSocket[Ark].skt);  
          WSACleanup ();
        }  /* requete non bloquante */ 
     } /* bInitDone */
return TCP4U_SUCCESS;
} /* Skt4wCleanup */