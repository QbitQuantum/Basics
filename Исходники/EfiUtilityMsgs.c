static
void
PrintMessage (
  INT8    *Type,
  INT8    *FileName,
  UINT32  LineNumber,
  UINT32  MessageCode,
  INT8    *Text,
  INT8    *MsgFmt,
  va_list List
  )
/*++

Routine Description:
  Worker routine for all the utility printing services. Prints the message in
  a format that Visual Studio will find when scanning build outputs for
  errors or warnings.

Arguments:
  Type        - "warning" or "error" string to insert into the message to be
                printed. The first character of this string (converted to uppercase)
                is used to preceed the MessageCode value in the output string.

  FileName    - name of the file where the warning was detected, or the name
                of the application that detected the warning
  
  LineNumber  - the line number where the warning was detected (parsers).
                0 should be specified if the utility is not a parser.
               
  MessageCode - an application-specific warning code that can be referenced in
                other documentation. 

  Text        - part of the message to print
  
  MsgFmt      - the format string for the message. Can contain formatting
                controls for use with varargs.
  List        - the variable list.
           
Returns:
  None.

Notes:
  If FileName == NULL then this utility will use the string passed into SetUtilityName(). 
  
  LineNumber is only used if the caller is a parser, in which case FileName refers to the
  file being parsed.

  Text and MsgFmt are both optional, though it would be of little use calling this function with
  them both NULL.

  Output will typically be of the form:
    <FileName>(<LineNumber>) : <Type> <Type[0]><MessageCode>: <Text> : <MsgFmt>

    Parser (LineNumber != 0)
      VfrCompile.cpp(330) : error E2660: AddVfrDataStructField : function does not take 2 parameters
    Generic utility (LineNumber == 0) 
      UtilityName : error E1234 : Text string : MsgFmt string and args

--*/
{
  INT8  Line[MAX_LINE_LEN];
  INT8  Line2[MAX_LINE_LEN];
  INT8  *Cptr;
  //
  // If given a filename, then add it (and the line number) to the string.
  // If there's no filename, then use the program name if provided.
  //
  if (FileName != NULL) {
    Cptr = FileName;
  } else if (mUtilityName[0] != 0) {
    Cptr = mUtilityName;
  } else {
    Cptr = "Unknown utility";
  }

  strcpy (Line, Cptr);
  if (LineNumber != 0) {
    sprintf (Line2, "(%d)", LineNumber);
    strcat (Line, Line2);
  }
  //
  // Have to print an error code or Visual Studio won't find the
  // message for you. It has to be decimal digits too.
  //
  sprintf (Line2, " : %s %c%04d", Type, toupper (Type[0]), MessageCode);
  strcat (Line, Line2);
  fprintf (stdout, "%s", Line);
  //
  // If offending text was provided, then print it
  //
  if (Text != NULL) {
    fprintf (stdout, ": %s ", Text);
  }
  //
  // Print formatted message if provided
  //
  if (MsgFmt != NULL) {
    vsprintf (Line2, MsgFmt, List);
    fprintf (stdout, ": %s", Line2);
  }

  fprintf (stdout, "\n");
}