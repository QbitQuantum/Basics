// Compares compareCmdLine with the output of MakeCommandLine. This is
// accomplished by converting inCmdLine to an argument list with
// CommandLineToArgvW and converting it back to a command line with
// MakeCommandLine.
static int
verifyCmdLineCreation(PRUnichar *inCmdLine,
                      PRUnichar *compareCmdLine,
                      bool passes, int testNum)
{
  int rv = 0;
  int i;
  int inArgc;
  int outArgc;
  bool isEqual;

  // When debugging with command lines containing Unicode characters greater
  // than 255 you can set the mode for stdout to Unicode so the console will
  // receive the correct characters though it won't display them properly unless
  // the console's font has been set to one that can display the characters. You
  // can also redirect the console output to a file that has been saved as Unicode
  // to view the characters.
//  _setmode(_fileno(stdout), _O_WTEXT);

  // Prepend an additional argument to the command line. CommandLineToArgvW
  // handles argv[0] differently than other arguments since argv[0] is the path
  // to the binary being executed and MakeCommandLine only handles argv[1] and
  // larger.
  PRUnichar *inCmdLineNew = (PRUnichar *) malloc((wcslen(DUMMY_ARG1) + wcslen(inCmdLine) + 1) * sizeof(PRUnichar));
  wcscpy(inCmdLineNew, DUMMY_ARG1);
  wcscat(inCmdLineNew, inCmdLine);
  LPWSTR *inArgv = CommandLineToArgvW(inCmdLineNew, &inArgc);

  PRUnichar *outCmdLine = MakeCommandLine(inArgc - 1, inArgv + 1);
  PRUnichar *outCmdLineNew = (PRUnichar *) malloc((wcslen(DUMMY_ARG1) + wcslen(outCmdLine) + 1) * sizeof(PRUnichar));
  wcscpy(outCmdLineNew, DUMMY_ARG1);
  wcscat(outCmdLineNew, outCmdLine);
  LPWSTR *outArgv = CommandLineToArgvW(outCmdLineNew, &outArgc);

  if (VERBOSE) {
    wprintf(L"\n");
    wprintf(L"Verbose Output\n");
    wprintf(L"--------------\n");
    wprintf(L"Input command line   : >%s<\n", inCmdLine);
    wprintf(L"MakeComandLine output: >%s<\n", outCmdLine);
    wprintf(L"Expected command line: >%s<\n", compareCmdLine);

    wprintf(L"input argc : %d\n", inArgc - 1);
    wprintf(L"output argc: %d\n", outArgc - 1);

    for (i = 1; i < inArgc; ++i) {
      wprintf(L"input argv[%d] : >%s<\n", i - 1, inArgv[i]);
    }

    for (i = 1; i < outArgc; ++i) {
      wprintf(L"output argv[%d]: >%s<\n", i - 1, outArgv[i]);
    }
    wprintf(L"\n");
  }

  isEqual = (inArgc == outArgc);
  if (!isEqual) {
    wprintf(L"TEST-%s-FAIL | %s | ARGC Comparison (check %2d)\n",
            passes ? L"UNEXPECTED" : L"KNOWN", TEST_NAME, testNum);
    if (passes) {
      rv = 1;
    }
    LocalFree(inArgv);
    LocalFree(outArgv);
    free(inCmdLineNew);
    free(outCmdLineNew);
    free(outCmdLine);
    return rv;
  }

  for (i = 1; i < inArgc; ++i) {
    isEqual = (wcscmp(inArgv[i], outArgv[i]) == 0);
    if (!isEqual) {
      wprintf(L"TEST-%s-FAIL | %s | ARGV Comparison (check %2d)\n",
              passes ? L"UNEXPECTED" : L"KNOWN", TEST_NAME, testNum);
      if (passes) {
        rv = 1;
      }
      LocalFree(inArgv);
      LocalFree(outArgv);
      free(inCmdLineNew);
      free(outCmdLineNew);
      free(outCmdLine);
      return rv;
    }
  }

  isEqual = (wcscmp(outCmdLine, compareCmdLine) == 0);
  if (!isEqual) {
    wprintf(L"TEST-%s-FAIL | %s | Command Line Comparison (check %2d)\n",
            passes ? L"UNEXPECTED" : L"KNOWN", TEST_NAME, testNum);
    if (passes) {
      rv = 1;
    }
    LocalFree(inArgv);
    LocalFree(outArgv);
    free(inCmdLineNew);
    free(outCmdLineNew);
    free(outCmdLine);
    return rv;
  }

  if (rv == 0) {
    if (passes) {
      wprintf(L"TEST-PASS | %s | check %2d\n", TEST_NAME, testNum);
    } else {
      wprintf(L"TEST-UNEXPECTED-PASS | %s | check %2d\n", TEST_NAME, testNum);
      rv = 1;
    }
  }

  LocalFree(inArgv);
  LocalFree(outArgv);
  free(inCmdLineNew);
  free(outCmdLineNew);
  free(outCmdLine);
  return rv;
}