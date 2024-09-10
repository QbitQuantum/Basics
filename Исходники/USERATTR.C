unsigned long ImageShadowProcedure(HWND Window,HMSG Message,long Param1,long Param2)
{
  switch (Message)
  {
    case WINDOWINIT:
         {
           char MidString[20];
           int AttributePosition;

           gcvt(TmpAttribute4,6,MidString);
           MessageGo(Window,SETLINEBUFFER,FP2LONG(MidString),0l);
           break;
         }
    case DIALOGBOXOK:
         {
           long MidBuffer;
           char *MidString;

           MidBuffer=MessageGo(Window,GETLINEBUFFER,0l,0l);
           MidString=LONG2FP(MidBuffer);
           TmpAttribute4=atof(MidString);
           if (TmpAttribute4<0||TmpAttribute4>=MAXCHARCOLOR)
           {
              MessageBox(GetTitleString(ERRORINFORM),
                         GetInformString(INVALIDCHARCOLOR),1,
                         WindowGetFather(Window));
              return(FALSE);
           }
           break;
         }
    default:
         return(SingleLineEditorDefaultProcedure(Window,Message,Param1,Param2));
  }
  return(TRUE);
}