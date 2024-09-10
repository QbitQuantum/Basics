void main (int argc, char *argv[])
{      
   WIN32_FIND_DATAA ffd;
   HANDLE h_find;
   char file_pattern[MAX_PATH];

   if (argc != 3)
   {
      printf("patmake.exe <mol-root> <cpp-output>");
      return;
   }

   if (argv[1][strlen(argv[1]) - 1] == '\\')
      argv[1][strlen(argv[1]) - 1] = 0;

   sprintf_s(file_pattern, "%s\\*.mol", argv[1]);

   h_find = FindFirstFileA(file_pattern, &ffd);

   if (h_find == INVALID_HANDLE_VALUE) 
   {
      printf ("FindFirstFile failed (%d)\n", GetLastError());
      return;
   } 
   else 
   {
      try
      {
         FileOutput cpp_file(true, argv[2]);
         SYSTEMTIME st;

         GetSystemTime(&st);

         char buf[200];

         sprintf_s(buf, " * Added %02d/%02d/%02d %02d:%02d:%02d", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);

         cpp_file.writeStringCR("/*");
         cpp_file.writeStringCR(buf);
         cpp_file.writeStringCR(" */");

         do 
         {
            try
            {
               convertMolfile(argv[1], ffd.cFileName, cpp_file);
            }
            catch (Exception &e)
            {
               printf("Error: %s\n", e.message()); 
            }
         } while (FindNextFileA(h_find, &ffd) != 0);

         printf("Done.\n"); 
      }
      catch (Exception &e)
      {
         printf("Error: %s\n", e.message()); 
      }

      FindClose(h_find);
   }

}