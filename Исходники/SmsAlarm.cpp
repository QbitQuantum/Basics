/*****************************************************************************
 * Function - SendAlarmSms
 * DESCRIPTION: Create an send an alarm sms
 *
 *****************************************************************************/
void SmsAlarm::SendAlarmSms(AlarmEvent* pAlarmEvent, SMS_REQUEST_TYPE reqType)
{
  #ifdef STR_MAX
    #error"AlarmSms"
  #else
    #define STR_MAX 900
  #endif
  char s1[STR_MAX]; //En sms må ikke være mere end 210tegn(tegn=1-4bytes), udfør evt tjek i nedenstående der sikrer mod overindeksering
  int str_id;
  int max_len;
  TimeFormatDataPoint* pDpTimePreference = TimeFormatDataPoint::GetInstance();
  mpc::display::ActualAlarmString alarm_String;

  SmsOut* my_sms = new SmsOut();  //Create a sms object, SmsCtrl will take care of deleting the object

  /* Create the message */
  s1[0]=0;
  if(pAlarmEvent->GetAlarmType() == ALARM_STATE_WARNING)
    strncat(s1, Languages::GetInstance()->GetString( SID_WARNING ),STR_MAX);  //Warning
  else if (pAlarmEvent->GetAlarmType() == ALARM_STATE_ALARM)
    strncat(s1, Languages::GetInstance()->GetString( SID_FS_ALARM ),STR_MAX); //Alarm
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, "\n", max_len);                                          // CR LF
  max_len = STR_MAX - strlen(s1);
  str_id = GetUnitString(pAlarmEvent->GetErroneousUnit(), pAlarmEvent->GetErroneousUnitNumber());//Alarm source
  if( max_len>0 )
    strncat(s1, Languages::GetInstance()->GetString( str_id ), max_len); //Unit type and number
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, "\n", max_len);                                          // CR LF
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, AlarmText::GetInstance()->GetString(pAlarmEvent->GetAlarmId(), pAlarmEvent->GetErroneousUnitNumber()), max_len); //Alarm text
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, "\n", max_len);                                          // CR LF
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, Languages::GetInstance()->GetString( SID_ARRIVAL_TIME ), max_len);  //Occurred at
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, "\n", max_len);                                          // CR LF
  max_len = STR_MAX - strlen(s1);
  mpTimeText->SetTime(*pAlarmEvent->GetArrivalTime());
  if( max_len>0 )
    strncat(s1, mpTimeText->GetText(), max_len);                         //Time
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, "\n", max_len);                                           // CR LF
  max_len = STR_MAX - strlen(s1);
  if( max_len>0 )
    strncat(s1, Languages::GetInstance()->GetString( SID_DEPARTURE_TIME ), max_len);//Disappeared at
  strcat(s1, "\n");                                                     // CR LF
  max_len = STR_MAX - strlen(s1);
  mpTimeText->SetTime(*pAlarmEvent->GetDepartureTime());
  if( max_len>0 )
    strncat(s1, mpTimeText->GetText(), max_len);                                    //Time

  /* Copy messge to sms object */
  my_sms->SetSmsMessage( s1 );

  switch (reqType)
  {
  case SMS_PRI_SEC:
    my_sms->SetSendTo(mpSmsRecipient->GetValue());          //Primary, or both primary and secondary number
    SmsCtrl::GetInstance()->SendSms( my_sms );              //Send sms to SmsCtrl
    break;
  case SMS_DIRECT:
    SmsCtrl::GetInstance()->SendDirectAlarmSms(my_sms);
    break;
  }
}