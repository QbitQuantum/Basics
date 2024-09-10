boolean Plugin_017(byte function, struct NodoEventStruct *event, char *string)
  {
  boolean success=false;
  
  int x;
  
  switch(function)
    {    
    case PLUGIN_INIT:
      {
      for(x=0;x<WIRED_PORTS;x++)
        pinMode(PIN_WIRED_OUT_1+x,INPUT); // definieer Arduino pin's voor Wired-Out
      }

    case PLUGIN_EVENT_IN:
      {
      if(event->Type     == NODO_TYPE_EVENT && 
         event->Command  == EVENT_USEREVENT &&
         event->Par1     == 255 &&
         event->Par2     == 255)
        {
        switch(event->Port)
          {
          case VALUE_SOURCE_IR:
            bitWrite(HW_Config,HW_IR_TX,true);
            break;
          case VALUE_SOURCE_RF:
            bitWrite(HW_Config,HW_RF_TX,true);
            break;
          }
        }          
      }

    case PLUGIN_ONCE_A_SECOND:
      {
      if(Active)
        {
        switch(HWSecCounter++)
          {
          case 1:
            HWSendTestEvent(VALUE_SOURCE_RF);
            break;

          case 5:
            HWSendTestEvent(VALUE_SOURCE_IR);
            break;

          case 7:
            HWSendTestEvent(VALUE_SOURCE_I2C);
            break;

          case 8:
            {            
            CheckWiredLines();          
            ShowTestResults();
            if(HW_ConfigCheck)
              {
              if(HW_Config==HW_ConfigCheck)
                {
                for(x=0;x<=4;x++)
                  {
                  Beep(2500,25);
                  delay(100);
                  }
                Serial.println(F("NodoTest: HWConfig is correct!"));
                }
              else
                {
                Beep(500,1000);
                Serial.println(F("NodoTest: HWConfig is NOT correct!"));
                }
              }
            Active=false;
            }
          }
        }
      break;
      }
      
    case PLUGIN_COMMAND:
      {
      Beep(1000,250);
      Settings.TransmitIR=VALUE_ON;
      Settings.TransmitRF=VALUE_ON;
      Settings.RawSignalReceive=VALUE_OFF;
    
      HWSecCounter=0;

      for(x=0;x<WIRED_PORTS;x++)
        {
        Settings.WiredInputPullUp[x]=VALUE_ON;
        pinMode(A0+PIN_WIRED_IN_1+x,INPUT_PULLUP);
        }

      HW_ConfigCheck=event->Par2;
      Active=true;
      Serial.println(F("NodoTest: Running...(please wait a few seconds)\n"));
      Beep(1000,50);

      success=true;
      break;
      }      
    
    #if NODO_MEGA // alleen relevant voor een Nodo Mega want de Small heeft geen MMI!
    case PLUGIN_MMI_IN:
      {
      char *TempStr=(char*)malloc(INPUT_COMMAND_SIZE);

      if(GetArgv(string,TempStr,1))
        {
        if(strcasecmp(TempStr,PLUGIN_NAME)==0)
          {
          event->Type    = NODO_TYPE_PLUGIN_COMMAND;
          event->Command = PLUGIN_ID; // nummer van dit plugin
          if(GetArgv(string,TempStr,2))
            event->Par2    = str2int(TempStr);
          success=true;
          }
        }
      free(TempStr);
      break;
      }

    case PLUGIN_MMI_OUT:
      {
      strcpy(string,PLUGIN_NAME);               // Commando 
      strcat(string," ");
      strcat(string,int2str(event->Par2));

      break;
      }
    #endif //MMI
    }
    
  return success;
  }