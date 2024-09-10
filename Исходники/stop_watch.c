void stop_watch_main(void){
#else
void main(void){
#endif
   STATE state = START_STATE;
   initStopWatch();
   TIMER3_RUN(FALSE);
   ClearScreen();
   Print(0,5,"--STOP WATCH--",1);

   Rectangle(2 , 4 , 108 , 7);

   while(!stopApplication()){
      switch (state)
      {
                case START_STATE:
                {
                        t.h = t.m = t.s = 0;
                        overflow = 0;
                        printTime();
                        if(LanguageSel == 1)
                        {
                                Print6(2,10," OK for START    ",1);
                        }
                        else
                        {
                                Print(2,8,"按OK键开始:",1);
                        }
                        if(ScanKey() == K_OK)
                        {
                                while(ScanKey() != 0xff);
                                halWait(5);
                                TIMER3_RUN(TRUE);
                                state = RUN_STATE;
                                if(LanguageSel == 1)
                                {
                                        Print6(2,10," OK for STOP   ",1);
                                }
                                else
                                {
                                        Print(2,8,"按OK键停止:",1);
                                }

                        }
                }break;

                case RUN_STATE:
                {
                        INT_GLOBAL_ENABLE(INT_OFF);

                        if(overflow > 0 && overflow < 0x09)
                        {
                                GLED = LED_ON;
                        }
                        else if(overflow > (UINT16)1000)
                        {
                                //overflow = 0;
                                overflow -= 1000;

                                incrementTime();
                                printTime();
                        }
                        else
                        {
                                GLED = LED_OFF;
                        }
                        if(ScanKey() == K_OK)
                        {
                                while(ScanKey() != 0xff);
                                halWait(5);
                                TIMER3_RUN(FALSE);
                                state = STOP_STATE;
                                GLED = LED_OFF;
                        }

                        INT_GLOBAL_ENABLE(INT_ON);
                }break;
                case STOP_STATE:
                {
                        printTime();
                        if(LanguageSel == 1)
                        {
                                Print6(2,10," Total time is:",1);
                        }
                        else
                        {
                                Print(2,8,"总计时间为:",1);
                        }
                        if(ScanKey() == K_OK)
                        {
                                while(ScanKey() != 0xff);
                                halWait(5);
                                state = START_STATE;
                        }
                }break;
                default:
                break;
        }
   }
   while(ScanKey() != 0xff);
   halWait(5);
   INT_GLOBAL_ENABLE(INT_OFF);
   return;
}