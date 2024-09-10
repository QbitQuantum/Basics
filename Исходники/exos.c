       short EXos(
       char    oscmd[],
       DBshort mode)

/*      Proceduren OS i WIN32-version.
 *
 *      In: oscmd => Kommandosträng.
 *          mode  => 0 = Asynkront (Batch) med wait
 *                   1 = Interaktivt
 *                   2 = Asynkront utan wait
 *
 *      Ut: Inget.
 *
 *      Felkoder: EX2092 = Fel från os, cmd=%s
 *
 *      (C)microform ab 1996-02-21 J. Kjellander
 *
 *      1997-02-03 _flushall(), J.Kjellander
 *      1997-05-20 COMMAND.COM bort,mode 1, J.Kjellander
 *      1998-03-27 WaitForSingleObject(), J.Kjellander
 *
 ******************************************************!*/

  {
   DWORD               create,errnum;
   char                errbuf[80];
   STARTUPINFO         si;
   PROCESS_INFORMATION pi;

/*
DWORD excode används ej fn.;
*/
/*
***Initiera startupinfo och processinfo.
*/
   memset(&si,0,sizeof(si));
   si.cb = sizeof(si);
/*
***Töm alla filbuffrar.
*/
   _flushall();
/*
***Om mode = 1 skall DOS-fönster skapas.
*/
   if ( mode == 1 ) create = CREATE_NEW_CONSOLE;
   else             create = DETACHED_PROCESS;
/*
***Starta processen.
*/
   if ( !CreateProcess(NULL,
                       oscmd,
                       NULL,
                       NULL,
                       FALSE,
                       create,
                       NULL,
                       NULL,
                      &si,
                      &pi) )
      {
      errnum = GetLastError();
      sprintf(errbuf,"%d%%%s",errnum,oscmd);
      return(erpush("EX2092",errbuf));
      }
/*
***Enligt dok. bör man stänga handtagen primära
***tråden så fort som möjligt om det inte behövs.
*/
    CloseHandle(pi.hThread);
/*
***Om mode = 0 eller 1 skall vi vänta tills subprocessen är
***klar. Detta verkar funka olika i NT och 95. C:s wait funkar
***inte ! Ej heller cwait(). Bytt till WaitForSingleObject()
***1998-03-27, JK.
*/
    if ( mode != 2 ) WaitForSingleObject(pi.hProcess,INFINITE);
/*
***Nu kan vi stänga även handtaget till själva processen.
*/
    CloseHandle(pi.hProcess);
/*
***Det ska gå att få reda på Exit-status men det test
***jag gjorde mot TakCAD funkade inte. VisualBasic inblandat !
*
loop:
    if ( GetExitCodeProcess(pi.hProcess,&excode) )
      {
      if ( excode == STILL_ACTIVE )
        {
        goto loop;
        }
      }
    else
      {
      errnum = GetLastError();
      sprintf(errbuf,"%d%%%s",errnum,oscmd);
      return(erpush("EX2092",errbuf));
      }
*/

 
    return(0);
  }