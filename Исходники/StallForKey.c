EFI_STATUS
StallForKey (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS      Status;
  UINTN           Argc;
  CHAR16          **Argv;
  UINTN           Seconds;
  EFI_EVENT       TimerEvent;
  EFI_EVENT       WaitList[2];
  UINTN           WaitIndex;
  EFI_INPUT_KEY   Key;

  //
  // Initialize libraries
  //
  EFI_SHELL_APP_INIT (ImageHandle, SystemTable);

  //
  // Process the arguments
  //
  Argc = SI->Argc;
  Argv = SI->Argv;

  Seconds = DEFAULT_WAIT_TIME;
  if (Argc > 1) {
    Seconds = Atoi (Argv[1]);
  }

  //
  // Create timer event
  //
  Status = BS->CreateEvent (
                 EFI_EVENT_TIMER,
                 0,
                 NULL,
                 NULL,
                 &TimerEvent
                 );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Create event. %a:%d:%r\n", __FILE__, __LINE__, Status));
    return Status;
  }

  //
  // Set up the timer
  //
  Status = BS->SetTimer (
                 TimerEvent,
                 TimerPeriodic,
                 10000000                   // 1 second
                 );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Set timer. %a:%d:%r\n", __FILE__, __LINE__, Status));
    BS->CloseEvent (TimerEvent);
    return Status;
  }

  //
  // Set up waiting list
  //
  WaitList[0] = ST->ConIn->WaitForKey;
  WaitList[1] = TimerEvent;

  //
  // Do it until timeout
  //
  while (Seconds != 0) {
    //
    // Print the prompt information (The last blank char is used to clean up
    // the last string. Don't remove it.)
    //
    Print (L"Press any key within %d seconds \r", Seconds);

    //
    // Wait for timeout or key input
    //
    Status = BS->WaitForEvent (
                   2,
                   WaitList,
                   &WaitIndex
                   );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Wait for event. %a:%d:%r\n", __FILE__, __LINE__, Status));
      break;
    }

    //
    // Check the triggered event
    //
    if (WaitIndex == 0) {
      //
      // Key input event is triggered
      //
      Key.ScanCode = SCAN_NULL;
      Status = ST->ConIn->ReadKeyStroke (ST->ConIn, &Key);
      if (!EFI_ERROR (Status)) {
        break;
      }

      DEBUG ((EFI_D_ERROR, "Read key stroke. %a:%d:%r\n", __FILE__, __LINE__, Status));
    } else {
      //
      // Timer event is triggered
      //
      Seconds --;
    }
  }

  //
  // Close the timer event
  //
  BS->CloseEvent (TimerEvent);

  //
  // Done
  //
  if (Seconds == 0) {
    return EFI_TIMEOUT;
  } else {
    return EFI_SUCCESS;
  }
}