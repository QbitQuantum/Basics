int primitive_drop_breakpoint (HANDLE process, DWORD address, BYTE *holder)
{
  BYTE    breakpoint_instance = 0xCC;
  DWORD   bytes_read;
  BOOL    read_status, write_status;

  // Read out the byte that we're going to eclipse with the breakpoint.
  // Some other function will have to store this somewhere.

  //printf ("--- NUB: Writing breakpoint at 0x%x\n", address);

  read_status =
    ReadProcessMemory 
      (process, (LPVOID) address, holder, sizeof(BYTE),
       &bytes_read);

  dylan_debugger_message("dropped breakpoint byte %= %=",
                         *holder, read_status);

  // If it doesn't work, don't try to continue.

  if (!read_status)
    return (0);

  // Write in the breakpoint instruction.

  write_status =
    ValidatedWriteProcessMemory 
      (process, (LPVOID) address, &breakpoint_instance,
       sizeof(BYTE), &bytes_read);

  dylan_debugger_message("Dropping breakpoint at %= %=", address, write_status);

  // Again, break if something goes wrong. (We have to assume here that the
  // breakpoint wasn't written if the function call failed).

  if (!write_status)
    return (0);

  // Make sure the breakpoint will be "seen" when encountered...

  FlushInstructionCache (process, (LPCVOID) address, sizeof(BYTE));
  return(1);
}