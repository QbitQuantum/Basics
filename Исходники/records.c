bool    AddSysRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return true;

  uint i = OpenRecord(SYS_RECORD, cdwSysRecord);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwSysRecord++; SaveCache(&chSysRecord);
  reCurr.ev = ev;

  switch (ev)
  {
//    case EVE_CONTACTS3_START:
//    case EVE_CONTACTS3_COUNTER: memcpy(&reCurr.mpbBuff+0, &cbContact, sizeof(uchar));
//                                memcpy(&reCurr.mpbBuff+1, &cbContactMax, sizeof(uchar)); break;
//
//    case EVE_VALUE3_DOWN:     memcpy(&reCurr.mpbBuff+0, &reContactDown, sizeof(float)); break;
//    case EVE_VALUE3_UP:       memcpy(&reCurr.mpbBuff+0, &reContactUp, sizeof(float)); break;
//    case EVE_VALUE3_COUNTER:  memcpy(&reCurr.mpbBuff+0, &cbContactMax, sizeof(uchar)); break;
//
//    case EVE_CONTACTS3_0_ON:  memcpy(&reCurr.mpbBuff+0, &reContactRec, sizeof(float));
//                              memcpy(&reCurr.mpbBuff+4, &reContactUp, sizeof(float)); break;
//
//    case EVE_CONTACTS3_0_OFF: memcpy(&reCurr.mpbBuff+0, &reContactRec, sizeof(float));
//                              memcpy(&reCurr.mpbBuff+4, &reContactDown, sizeof(float)); break;
//
//    case EVE_CONTACTSMODE:
//    case EVE_CONTACTS1:
//    case EVE_CONTACTS2: memcpy(&reCurr.mpbBuff+0, &bContactRec, sizeof(uchar)); break;

    case EVE_PREVNEXTTIME2:   Put(0, (uchar *) &tiCurr, sizeof(time)); break;

    case EVE_EDIT_DIGITAL1:
    case EVE_EDIT_DIGITAL2:   PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpdiDigital[ibRecordCan], sizeof(digital)); break;

    case EVE_EDIT_KEY10:
    case EVE_EDIT_KEY20:      PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpphKeys[ibRecordCan].szLine+0, 7); break;

    case EVE_EDIT_KEY11:
    case EVE_EDIT_KEY21:      Put(0, (uchar *) &mpphKeys[ibRecordCan].szLine+7, 6); break;

    case EVE_EDIT_ADDRESS10:
    case EVE_EDIT_ADDRESS11:  PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpdwAddress1[ibRecordCan], sizeof(ulong)); break;

    case EVE_EDIT_ADDRESS20:
    case EVE_EDIT_ADDRESS21:  PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpdwAddress2[ibRecordCan], sizeof(ulong)); break;
  }

  CloseRecord(SYS_RECORD, i);

  return CloseOut();
}