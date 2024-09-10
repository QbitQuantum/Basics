int Algoritms::SaveStates(char *name,char *AlgTaskName[maxcrits],
			  char *AlgProcName[3],task far* tasklistptr)
   {
   int handle,retvalue;
   UINT MaxLgTakt,MaxLgProc,MaxLgTask;
   UCHAR NumbTask=0,NumbProc=0;
   char *CopyRight=
" ╔════════════════════════════════════════════════════════════════════════════╗\n"
" ║                      PARALLEL    PROCESSOR   SCHEDULER                     ║\n"
" ║                                 Version 1.1                                ║\n"
" ║                                (C)  Feedback                               ║\n"
" ╚════════════════════════════════════════════════════════════════════════════╝\n\n";
   char *value=
      "                                                                      \n";
   char *AlgTaskMsg=
      " Алгоритм выбора задач:                                               \n";
   char *AlgProcMsg=
      "    - по минимуму индекса                                             \n"
      " Алгоритм выбора процессоров:                                         \n"
      "    -                                                                 \n"
      "    - по минимуму индекса                                             \n";
   char *TitleMessage=
      " Число Задач:        Число процессоров:        Критический путь:      \n"
      " ┌─────────────┬────────────┬───────────────────┬─────────────────┐   \n"
      " │    Номер    │   Номер    │ Время постановки  │ Время окончания │   \n"
      " │    задачи   │ процессора │   на выполнение   │     решения     │   \n"
      " ├─────────────┼────────────┼───────────────────┼─────────────────┤   \n";
   char *Mesg=
      " │             │            │                   │                 │   \n";
   char *TitleDone=
      " └─────────────┴────────────┴───────────────────┴─────────────────┘   \n"
      " Время решения =>                                                     \n"
      " Коэффициенты загруженности процессоров :                             \n";
   char *Charge=
      "    Процессор    :    Время работы =>       Загруженность => 0.       \n";
   char *Str=
      "\n────────────────────────────────────────────────────────────────────────────────\n\n";
   tasks=tasklistptr;
   itoa(time,value,10);
   MaxLgTakt=strlen(value);
   itoa(cntprocs,value,10);
   MaxLgProc=strlen(value);
   itoa(cnttasks,value,10);
   MaxLgTask=strlen(value);
   if ((handle=
      open(name,O_APPEND|O_TEXT|O_RDWR,S_IREAD|S_IWRITE))==-1)
      {
      if ((handle=
	 open(name,O_CREAT|O_APPEND|O_TEXT|O_RDWR,S_IREAD|S_IWRITE))==-1)
	 return io_error;
      if (write(handle,CopyRight,80*5+1)!=80*5+1)
	 {
	 close(handle);
	 return io_error;
	 }
      }
   if (write(handle,AlgTaskMsg,71)!=71)
      {
      close(handle);
      return io_error;
      }
   for (int i=1; i<=cntcrits; i++)
      {
      strcpy(value,"    - ");
      strcpy(&value[6],AlgTaskName[critslist[i]-1]);
      if (write(handle,value,71)!=71)
	 {
	 close(handle);
	 return io_error;
	 }
      }
   strcpy(&AlgProcMsg[71*2+6],AlgProcName[charge]);
   if (write(handle,AlgProcMsg,71*4)!=71*4)
      {
      close(handle);
      return io_error;
      }
   strcpy(value,AlgTaskName[critslist[i]-1]);
   itoa(cnttasks,value,10);
   strcpy(&TitleMessage[15],value);
   itoa(cntprocs,value,10);
   strcpy(&TitleMessage[41],value);
   itoa(critway,value,10);
   strcpy(&TitleMessage[66],value);
   if (write(handle,TitleMessage,71*5)!=71*5)
      {
      close(handle);
      return io_error;
      }
   while (++NumbTask<=cnttasks)
      {
      itoa(NumbTask,value,10);
      strcpy(&Mesg[7+MaxLgTask-strlen(value)],value);
      itoa(taskstate[NumbTask].procnumber,value,10);
      strcpy(&Mesg[21+MaxLgProc-strlen(value)],value);
      itoa(taskstate[NumbTask].begtime,value,10);
      strcpy(&Mesg[37+MaxLgTakt-strlen(value)],value);
      itoa(taskstate[NumbTask].begtime+tasks[NumbTask].weight-1,value,10);
      strcpy(&Mesg[56+MaxLgTakt-strlen(value)],value);
      if (write(handle,Mesg,71)!=71)
	 {
	 close(handle);
	 return io_error;
	 }
      strcpy(&Mesg[7],"     ");
      strcpy(&Mesg[21],"     ");
      strcpy(&Mesg[37],"     ");
      strcpy(&Mesg[56],"     ");
      }
   itoa(time-1,value,10);
   strcpy(&TitleDone[89],value);
   if (write(handle,TitleDone,71*3)!=71*3)
      {
      close(handle);
      return io_error;
      }
   while (++NumbProc<=cntprocs)
      {
      int dec,sign;
      double kfc;
      itoa(NumbProc,value,10);
      strcpy(&Charge[14+MaxLgProc-strlen(value)],value);
      itoa(procs[NumbProc].chargetime,value,10);
      strcpy(&Charge[38+MaxLgTakt-strlen(value)],value);
      kfc=((float)procs[NumbProc].chargetime)/((float)(time-1));
      value=fcvt(kfc,5,&dec,&sign);
      if (procs[NumbProc].chargetime!=time-1) strcpy(&Charge[63],value);
	 else
	    strcpy(&Charge[61],"1.00000");
      if (write(handle,Charge,71)!=71)
	 {
	 close(handle);
	 return io_error;
	 }
      strcpy(&Charge[14],"   :");
      if (procs[NumbProc].chargetime!=time-1) strcpy(&Charge[63],"     ");
	 else
	    strcpy(&Charge[61],"0.    ");
      }
   write(handle,Str,82);
   close(handle);
   return io_ok;
   }