/*! Handle the messages routed to the display queue */
static void DisplayQueueMessageHandler(tMessage *pMsg)
{
  tMessage Msg;

  switch (pMsg->Type)
  {
  case ShowCallMsg:
    HandleCallNotification(pMsg->Options, pMsg->pBuffer, pMsg->Length);
    break;

  case WriteBufferMsg:
    WriteBufferHandler(pMsg);
    break;

  case SetWidgetListMsg:
    SetWidgetList(pMsg);
    break;
  
  case UpdateDisplayMsg:
  
    if ((!(pMsg->Options & MSG_OPT_UPD_INTERNAL) &&
        (pMsg->Options & MODE_MASK) == NOTIF_MODE) &&
        GetProperty(PROP_AUTO_BACKLIGHT))
      SendMessage(AutoBacklightMsg, MSG_OPT_NONE);

    UpdateDisplayHandler(pMsg);
    break;

  case DrawMsg:
    DrawMsgHandler(pMsg);
    break;
    
  case UpdateClockMsg:
    UpdateClock();
    break;
    
  case DrawClockWidgetMsg:
    DrawClockWidget(pMsg->Options);
    break;

  case BluetoothStateChangeMsg:
    BluetoothStateChangeHandler(pMsg);
    break;

  case IdleUpdateMsg:
    IdleUpdateHandler();
    break;

  case ButtonStateMsg:
    ButtonStateHandler();
    break;

  case StopTimerMsg:
    StopTimer((eTimerId)pMsg->Options);
    break;

  case MonitorBatteryMsg:
    MonitorBattery();
    break;

  case MusicIconMsg:
      MusicIcon(pMsg->Options);
      break;

  case MusicStateMsg:
    HandleMusicStateChange(pMsg->Options);
    break;
    
  case ChangeModeMsg:
    ChangeMode(pMsg->Options);
    break;
  
  case ControlFullScreenMsg:
    SetProperty(PROP_PHONE_DRAW_TOP, pMsg->Options || *pMsg->pBuffer ? PROP_PHONE_DRAW_TOP : 0);
    break;

  case ModifyTimeMsg:
    ModifyTimeHandler(pMsg);
    break;

  case MenuModeMsg:
    MenuModeHandler(pMsg->Options);
    break;

  case MenuButtonMsg:
    MenuButtonHandler(pMsg->Options);
    break;

  case EnableButtonMsg:
    EnableButtonMsgHandler(pMsg);
    break;

  case DevTypeMsg:

    Msg.Length = 1;
    Msg.Type = DevTypeRespMsg;
    Msg.Options = BOARD_TYPE; //default G2

    if (CreateMessage(&Msg))
    {
      Msg.pBuffer[0] = BOARD_TYPE; // backward compatible

      if (GetMsp430HardwareRevision() < 'F')
      {
        Msg.Options = DIGITAL_WATCH_TYPE_G1;
        Msg.pBuffer[0] = DIGITAL_WATCH_TYPE_G1; // backward compatible
      }

      Msg.Options |= DEV_TYPE_EN_ACK; // support ACK
      RouteMsg(&Msg);
    }

    PrintF("- DevTypeResp:%u", Msg.Options);

    // set ACK and HFP/MAP bits
//    SendMessage(ConnTypeMsg, pMsg->Options);
    break;

  case VerInfoMsg:

    Msg.Length = BUILD_LENGTH + 4 + 3;
    Msg.Type = VerInfoRespMsg;
    Msg.Options = MSG_OPT_NONE;

    if (CreateMessage(&Msg))
    {
      GetBuildNumber(Msg.pBuffer);

      *(Msg.pBuffer + BUILD_LENGTH) = VERSION[0] - ZERO;
      *(Msg.pBuffer + BUILD_LENGTH + 1) = VERSION[2] - ZERO;
      *(Msg.pBuffer + BUILD_LENGTH + 2) = VERSION[4] - ZERO;
      *(Msg.pBuffer + BUILD_LENGTH + 3) = GetMsp430HardwareRevision();
      *(Msg.pBuffer + BUILD_LENGTH + 4) = BootVersion[0] - ZERO;
      *(Msg.pBuffer + BUILD_LENGTH + 5) = BootVersion[2] - ZERO;
      *(Msg.pBuffer + BUILD_LENGTH + 6) = BootVersion[4] - ZERO;

      RouteMsg(&Msg);
    }
    PrintE("-Ver(%u):", Msg.Length); PrintQ(Msg.pBuffer, Msg.Length);
    break;

  case LogMsg:
    SendStateLog();
    break;
    
  case VibrateMsg:
    SetVibrateModeHandler(pMsg);
    break;

  case SetRtcMsg:
    if (SetRtc((Rtc_t *)pMsg->pBuffer)) UpdateClock();
    break;
    
  case CountdownMsg:
    if (pMsg->Options == CDT_ENTER)
    {
      PageType = PAGE_TYPE_INFO;
      CurrentPage[PageType] = CountdownPage;
    }
    CountdownHandler(pMsg->Options);
    break;

  case ServiceMenuMsg:
    ServiceMenuHandler();
    break;

  case FieldTestMsg:
    HandleFieldTestMode(pMsg->Options);
    break;

  case DisableButtonMsg:
    DisableButtonMsgHandler(pMsg);
    break;

  case ReadButtonConfigMsg:
    ReadButtonConfigHandler(pMsg);
    break;

  case SetBacklightMsg:
    SetBacklight(pMsg->Options);
    // testing
//    pMsg->Type = AccelMsg;
//    pMsg->Options = 1; //enable
//    HandleAccelerometer(pMsg);
    break;

  case AutoBacklightMsg:
    if (LightSenseCycle() < DARK_LEVEL) SetBacklight(LED_ON);
    break;

  case BatteryConfigMsg:
    SetBatteryLevels(pMsg->pBuffer);
    break;

  case ReadBatteryVoltageMsg:
    ReadBatteryVoltageHandler();
    break;

  case ResetMsg:
    SoftwareReset(RESET_BUTTON_PRESS, pMsg->Options);
    break;

  case NvalOperationMsg:
    NvalOperationHandler(pMsg);
    break;

  case SecInvertMsg:
    HandleSecInvert(pMsg->Options);
    break;

  case LoadTemplateMsg:
    LoadTemplateHandler(pMsg);
    break;

  case LinkAlarmMsg:
    SendMessage(VibrateMsg, VIBRA_PATTERN_LNKALM);
    break;

  case ModeTimeoutMsg:
    ModeTimeoutHandler();
    break;

  case WatchStatusMsg:
    PageType = PAGE_TYPE_INFO;
    CurrentPage[PageType] = StatusPage;
    DrawWatchStatusScreen(TRUE);
    break;

  case TermModeMsg:
    TermModeHandler();
    break;
    
  case LowBatteryWarningMsg:
    break;
    
  case LowBatteryBtOffMsg:
    UpdateClock();
    break;

#if __IAR_SYSTEMS_ICC__
  case EraseTemplateMsg:
//    EraseTemplateHandler(pMsg);
    break;
    
  case WriteToTemplateMsg:
//    WriteToTemplateHandler(pMsg);
    break;
#endif

  case AccelMsg:
    HandleAccelerometer(pMsg);
    break;

  case ReadLightSensorMsg:
    ReadLightSensorHandler();
    break;

  case WatchDrawnScreenTimeout:
    IdleUpdateHandler();
    break;

  case RateTestMsg:
    /* don't care what data is */
    Msg.Length = 10;
    Msg.Type = DiagnosticLoopback;
    Msg.Options = MSG_OPT_NONE;
    if (CreateMessage(&Msg)) RouteMsg(&Msg);
    break;
    
  default:
    PrintF("# Disp Msg:x%02X", pMsg->Type);
    break;
  }
}