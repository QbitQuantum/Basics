Boolean Ln2SlFormHandleEvent(EventPtr e)
{
    Boolean handled = false;
    DateType dt = {0, 0};
    FormPtr frm = FrmGetFormPtr(Ln2SlForm);

    switch (e->eType) {
    case frmOpenEvent:
        if(gbVgaExists)
       		VgaFormModify(frm, vgaFormModify160To240);

        DateSecondsToDate(TimGetSeconds(), &dt);
        DateToAsciiLong(dt.month, dt.day, dt.year + 1904,
					gPrefdfmts, gAppErrStr);
        SetFieldTextFromStr(Ln2SlFormInput, gAppErrStr);

        FrmDrawForm(frm);
        handled = true;
        break;

    case ctlSelectEvent:
        switch(e->data.ctlSelect.controlID) {
        case Ln2SlFormOk:
            FrmReturnToForm(0);

            handled = true;
            break;

        case Ln2SlFormConvert:
        {
            HappyDaysFlag dummy;
            Int16 year, month, day;
            Char* input;
            int ret;
            
            input = FldGetTextPtr(GetObjectPointer(frm, Ln2SlFormInput));

            if ((ret = AnalysisHappyDays(input, &dummy,
                                         &year, &month, &day))) {
                int syear, smonth, sday;
                int leapyes
                    = CtlGetValue(GetObjectPointer(frm, Ln2SlFormInputLeap));

                ret = lunarL2S(lunarRefNum, year, month, day, leapyes, &syear, &smonth, &sday);
                if (ret == errNone) {
                    Char temp[15];
                    SysCopyStringResource(temp, DayOfWeek(smonth, sday, syear) + SunString);

                    DateToAsciiLong(smonth, sday, syear, gPrefdfmts, gAppErrStr);
                    StrNCat(gAppErrStr, " [", AppErrStrLen);
                    StrNCat(gAppErrStr, temp, AppErrStrLen);
                    StrNCat(gAppErrStr, "]", AppErrStrLen);

                    FldDrawField(SetFieldTextFromStr(Ln2SlFormResult, gAppErrStr));
                }
                else DisplayInvalidDateErrorString(Ln2SlFormResult);
            }
            else {
                DisplayInvalidDateErrorString(Ln2SlFormResult);
            }
            
            handled = true;
            break;
        }
        
        default:
            break;
                
        }
        break;

    case menuEvent:
        handled = TextMenuHandleEvent(e->data.menu.itemID, Ln2SlFormInput);
        break;

    default:
        break;
    }

    return handled;
}