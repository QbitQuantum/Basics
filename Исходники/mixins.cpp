    void Loggable::Static::info(const char* msg, ...)
    {
      char text[BUF_SZ];
      char* text_contents = text + 1;

      text[0] = HERMES_EC_INFO;
      text[1] = ' ';
      text_contents++;

      //print the message
      va_list arglist;
      va_start(arglist, msg);
      vsprintf(text_contents, msg, arglist);
      va_end(arglist);

      //Windows platform
#ifdef _WINDOWS
      HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

      //generate console settings
      WORD console_attr_red = FOREGROUND_RED, console_attr_green = FOREGROUND_GREEN, console_attr_blue = FOREGROUND_BLUE;

      WORD console_attrs = 0;
      console_attrs |= console_attr_green;

      //set new console settings
      SetConsoleTextAttribute(h_console, console_attrs);

      //write text
      DWORD num_written;
      BOOL write_success = WriteConsoleA(h_console, text_contents, strlen(text_contents), &num_written, nullptr);
      std::cout << std::endl;

      //Linux platform
#else
# define FOREGROUND_RED 1
# define FOREGROUND_GREEN 2
# define FOREGROUND_BLUE 4
      //console color code
      int console_attrs = 0;
      bool console_bold = true;

      printf("\033[%dm", console_attrs + 30);

      //emphasize and console bold
      if(console_bold)
        printf("\033[1m");

      //print text and reset settings
      printf("%s\033[0m\n", text_contents);

#endif
    }