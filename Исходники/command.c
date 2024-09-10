static void hangForever(void)
{
#ifdef FEATURE_AUTOREDIRECT_TO_CON
  int i;

  i = FEATURE_AUTOREDIRECT_TO_CON + 1;
#endif
    /* this might happen in certain "emergency"-level problems.
      The "cannot_exit" state must be honored, though.
      Also, it cannot be considered that the string area is
      available -- 1999/07/06 ska*/
    fcloseall();  /* prepare the external termination */
  for(;;) {
#ifdef FEATURE_AUTOREDIRECT_TO_CON
    if(--i == 0)
      cmd_ctty("CON");
#endif
    puts(   /* fcloseall() leaves the standard streams open */
     "\r\n\r\n"
     "The shell is about to be terminated, though, this is\r\n"
     "forbidden (usually by enabling the \"/P\" option).\r\n"
     "You must reboot the system or, if this shell runs in\r\n"
     "a multitasking environment, terminate this process/task manually.\r\n"
    );
    beep();
    delay(1000);  /* Keep the message on the screen for
              at least 1s, in case FreeCom has some problems
              with the keyboard */
  }
}