void runsyslinuximage(const char*cmd, long ipappend)
{
  unsigned int numfun = 0;
  char *ptr,*cmdline;

  getversion(NULL,&numfun);
  // Function 16h not supported Fall back to runcommand
  if (numfun < 0x16) runsyslinuxcmd(cmd);
  // Try the Run Kernel Image function
  // Split command line into
  strcpy(__com32.cs_bounce,cmd);
  ptr = __com32.cs_bounce;
  // serach for first space or end of string
  while ( (*ptr) && (*ptr != ' ')) ptr++;
  if (!*ptr) cmdline = ptr; // no command line
  else {
     *ptr++='\0'; // terminate kernal name
     cmdline = ptr+1;
     while (*cmdline != ' ') cmdline++; // find first non-space
  }
  // Now call the interrupt
  REG_BX(inreg) = OFFS(cmdline);
  REG_ES(inreg) = SEG(cmdline);
  REG_SI(inreg) = OFFS(__com32.cs_bounce);
  REG_DS(inreg) = SEG(__com32.cs_bounce);
  REG_EDX(inreg) = 0;

  __intcall(0x22,&inreg,&outreg); // If successful does not return
}