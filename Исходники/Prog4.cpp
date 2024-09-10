/*--------------- E x e c u t e ( ) ---------------

PURPOSE
Execute a command stream, either from cin of
from a command file

INPUT PARAMETERS
cmdStream --  the stream from which commands are to be read
pwlFcn     -- the pwlFcn list.
*/
void Execute(istream &cmdStream, DblLinkedList &pwlFcn)
{
  string cmdLine; // The current command line

  // Repeatedly get a command from the keyboard and
  // execute it.
  do
    {
    cmdLine = GetCmd(cmdStream, pwlFcn);

    if (cmdLine.length() != 0)
      {
      switch (toupper(cmdLine[0]))
        {
        // Execute a command file.
        case ExecuteCmd:
          DoExecute(cmdLine, pwlFcn);
          break;
        // Determine which command to execute.
        case InsertCmd:        // Insert a new point.
          InsertPoint(cmdLine, pwlFcn);
          break;
        case ClearCmd:      // Clear the pwlFcn.
          pwlFcn.~DblLinkedList(); // Explicit destructor function call
          break;
        case DeleteCmd:     // Delete the current point.
          if (!pwlFcn.AtEnd())
            pwlFcn.DeleteItem();
          if (pwlFcn.Empty())
            cout << "The pwlFcn is empty." << endl;
          break;
        case PrintCmd:       // Display the pwlFcn.
          DisplayPwlFcn(pwlFcn);
          break;
        case OpenCmd:       // Read in a pwlFcn file.
          ReadPwlFcnFile(cmdLine, pwlFcn);
          break;
        case SaveAsCmd:      // Write out a pwlFcn file.
          WritePwlFcnFile(cmdLine, pwlFcn);
          break;
        case ForwardCmd:       // Advance to the next point.
          if (!pwlFcn.AtEnd())
            pwlFcn.Forward();
          if (pwlFcn.AtEnd())
            cout << "The pwlFcn is at the end." << endl;
          break;
        case BackwardCmd:       // Go back to the previous point.
          pwlFcn.Backward();
          break;
        case RewindCmd:         // Rewind to the first point in the pwlFcn.
          pwlFcn.Rewind();
          break;
        case GenerateCmd:     // Generate waveform.
          {
          DblLinkedList pwlFcnCopy(pwlFcn); // Invokes copy constructor

          Generate(cmdLine, pwlFcnCopy);
          }
          break;
        case NumPtsCmd:
          {
          DblLinkedList pwlFcnCopy; // A copy of the pwlFcn
          
          pwlFcnCopy = pwlFcn;    // Invokes overloaded assignment
         
          CountPoints(pwlFcnCopy);  // Pass by value invokes the copy constructor.
          }
          break;
        case QuitCmd:       // Terminate execution.
          break;
        default:            // Bad command
          cout << "*** Error: Unknown Command" << endl;
          break;
        }
      }
    }
  while (cmdLine.length() > 0 && toupper(cmdLine[0]) != QuitCmd);
}