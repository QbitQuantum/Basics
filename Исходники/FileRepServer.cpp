/*
    FUNCTION: main()

    PURPOSE: main() calls StartServiceCtrlDispatcher to register the
        main service thread.    When this call returns,
        the service has stopped.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:
*/
VOID _cdecl main(int argc, char **argv){
    RPC_STATUS status;

    int nNumArgs;
    LPWSTR *szArgList = CommandLineToArgvW(GetCommandLine(), &nNumArgs);

    if (NULL == szArgList) {
        _tprintf(TEXT("FileRep main: CommandLineToArgW failed"));
        exit(EXIT_FAILURE);
    }

    // Allow the user to override settings with command line switches.
    for (int i = 1; i < nNumArgs; i++) {
        // Well-formed argument switches start with '/' or '-' and are
        // two characters long.
        if (((*szArgList[i] == TEXT('-')) || (*szArgList[i] == TEXT('/'))) && _tcsclen(szArgList[i]) == 2) {

            switch (_totlower(*(szArgList[i]+1))) {

                case TEXT('f'):
		  bNoFileIO = true;
		  break;
                    
                case TEXT('h'):
                case TEXT('?'):
                default:
                    exit(EXIT_SUCCESS);
            }
        }
        else {
	  _tprintf(TEXT("Bad arguments.\n\n"));
	  exit(EXIT_FAILURE);
        }
    }

    // Service initialization
    if (!StartFileRepServer()) {
      return;
    } else {
      bServerListening = TRUE;

      // RpcMgmtWaitServerListen() will block until the server has
      // stopped listening.
      status = RpcMgmtWaitServerListen();
      if (status != RPC_S_OK){
        AddToMessageLogProcFailureEEInfo(TEXT("ServiceStart: RpcMgmtWaitServerListen"), status);
        return;
      }
    }
    
    return;
}