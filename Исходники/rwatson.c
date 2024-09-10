int main(int argc, char **argv)
{
   HWND hMain;
   HWINSTA hwinsta;

   hwinsta = OpenWindowStation("WinSta0", FALSE, WINSTA_READSCREEN);
   if (hwinsta == NULL || SetProcessWindowStation(hwinsta) == FALSE)
      printf("Failed to set window station!\n");

   if (argc > 1)
      sscanf(argv[1], "%d", &hMain);
   else hMain = FindMainWindow(dialog_class_name, main_window_caption);

   printf("%d\n", hMain);

   if (hMain == NULL)
   {
      printf("Couldn't find window with caption %s\n", main_window_caption);
      exit(1);
   }

   if (!SendWindowEvents(hMain))
      return 1;

   return 0;
}