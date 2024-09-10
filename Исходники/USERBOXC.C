unsigned long BoxRoundBottomDistantProcedure(HWND Window,HMSG Message,long Param1,long Param2)
{
  switch (Message)
  {
    case WINDOWINIT:
         {
           char MidString[20];

           gcvt(ConvertToSystemMeter((float)TmpTextBox.RoundDistantBottom/(float)(SCALEMETER)),
                5,MidString);
           MessageGo(Window,SETLINEBUFFER,FP2LONG(MidString),0l);
           break;
         }
    case DIALOGBOXOK:
         {
           long MidBuffer;
           char *MidString;

           MidBuffer=MessageGo(Window,GETLINEBUFFER,0l,0l);
           MidString=(char *)LONG2FP(MidBuffer);
           if (IsInvalidDigit(MidString))
           {
              MessageBox(GetTitleString(ERRORINFORM),
                         GetInformString(INVALIDBOXROUNDBOTTOMDISTANT),1,
                         WindowGetFather(Window));
              return(FALSE);
           }
           TmpTextBox.RoundDistantBottom=ConvertToUserMeter((float)SCALEMETER*atof(MidString))+0.5;
           break;
         }
    default:
         return(SingleLineEditorDefaultProcedure(Window,Message,Param1,Param2));
  }
  return(TRUE);
}