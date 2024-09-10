static void __cdecl ac3_thread(void *p)
{
 ac3_decode *ac3=(ac3_decode *)p;

 ac3->done=CreateEvent(NULL,0,0,0);
 ac3->out_done=CreateEvent(NULL,0,0,0);
 ac3->in_done=CreateEvent(NULL,0,0,0);

 if(SetThreadPriority((HANDLE)ac3->thread,THREAD_PRIORITY_HIGHEST)==0)
 {
  debug("kxmixer: error setting thread priority [%x]\n",GetLastError());
 }
 // else debug("kxmixer: set thread priority to highest [%x]\n",ac3->thread);

 if(SetThreadExecutionState(ES_SYSTEM_REQUIRED)==NULL)
 {
  debug("kxmixer: cannot set execution thread state -- might cause problems with APM...\n");
 }

 if(ac3->done && ac3->in_done && ac3->out_done)
 {
  // debug("kxmixer: thread created and active...starting rec...\n");

  waveInStart(ac3->wave_in);

  ac3->last_out_buffer=1;
  ac3->last_in_buffer=1;
  
  while(1)
  {
   // WaitForMultipleObject including 'done' event...
   HANDLE list[3];
   list[0]=ac3->done; list[1]=ac3->out_done; list[2]=ac3->in_done;
   int ret=WaitForMultipleObjects(3,list,0,INFINITE);
   if(ret==WAIT_OBJECT_0) // done
   {
    break;
   }
   if(ret==WAIT_OBJECT_0+1) // out
   {
   }
   if(ret==WAIT_OBJECT_0+2) // in
   {
     	waveOutWrite(ac3->wave_out,&ac3->out_buffer[ac3->last_out_buffer-1],sizeof(WAVEHDR));

     	ac3->last_out_buffer++;
     	if(ac3->last_out_buffer>TOTAL_BUFFERS)
         ac3->last_out_buffer=1;
   }
  }

  waveInStop(ac3->wave_in);

  debug("kxmixer: thread exited...\n");
 } else debug("kxmixer: error creating thread events\n");
}