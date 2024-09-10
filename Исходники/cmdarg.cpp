int ParseArgs(int nArgc, char *ppArgv[], CommandArgs *pArgs)
{
    char c;
    ArgsStream stream;
    BOOL bCharSkipped;

    memset(pArgs, 0, sizeof(CommandArgs));
    stream.Initialize(nArgc, ppArgv);

    if (stream.PeekChar() == 0) {
        fputs(c_pszCopyright, stdout);
        fputs(c_pszUsage, stdout);
        exit(0);
    }

    while ((c = stream.PeekChar()) != 0) {
        if (IsCommandSwitch(c)) {
            stream.GetChar(); // skip switch char: '-'

            bCharSkipped = FALSE;
            c = stream.PeekChar();
            if (IsCommandSwitch(c)) { // another '-'
                stream.GetChar(); // skip switch char: '-'
                c = stream.PeekChar();
            }
            switch (c) {
                case 'o': // output
                    stream.GetWord(); // skip char "c" or the rest of "output"
                    bCharSkipped = TRUE;
                    pArgs->pszOutputFile = stream.GetWord();
                    if (!pArgs->pszOutputFile) {
                        CmdError(CommandError_NoPathStr, c);
                        return CommandError_NoPathStr;
                    }
                    break;

                case 'i': // interface
                    pArgs->dwAttribs |= Command_r_Interface;
                    break;

                case 'c':
                    if (stream.PeekCharAt(2) == 'a') { // callback
                        pArgs->dwAttribs |= Command_r_Callback;
                    }
                    else if (stream.PeekCharAt(2) == 'o') { // const
                        pArgs->dwAttribs |= Command_r_Const;
                    }
                    else {
                        pArgs->dwAttribs |= Command_r_Class;
                    }
                    break;

                case 'b':
                    pArgs->dwAttribs |= Command_r_BaseClass;
                    break;

                case 'a':
                    if (stream.PeekCharAt(2) == 'l') { // all
                        pArgs->dwAttribs |= Command_r_All;
                    }
                    else { // aspect
                        pArgs->dwAttribs |= Command_r_Aspect;
                    }
                    break;

                case 'g': // generic
                    pArgs->dwAttribs |= Command_r_Generic;
                    break;

                case 'h':
                    if (stream.PeekCharAt(2) == 'e') { // help
                        fputs(c_pszCopyright, stdout);
                        fputs(c_pszUsage, stdout);
                        exit(0);
                    }
                    else { // callback handler
                        pArgs->dwAttribs |= Command_r_Callback;
                    }
                    break;

                case 'n':
                    pArgs->dwAttribs |= Command_r_Const;
                    break;

                case 'e': // enum
                    pArgs->dwAttribs |= Command_r_Enum;
                    break;

                case 'r': // regime
                    pArgs->dwAttribs |= Command_r_Regime;
                    break;

                case 's': // struct
                    pArgs->dwAttribs |= Command_r_Struct;
                    break;

                case 'm': // method
                    pArgs->dwAttribs |= Command_r_Method;
                    break;

                case 'f':
                    pArgs->dwAttribs |= Command_r_ForceOverride;
                    break;

                case '?':
                    fputs(c_pszCopyright, stdout);
                    fputs(c_pszUsage, stdout);
                    exit(0);

                default:
                    CmdError(CommandError_UnknownArg, c);
                    return CommandError_UnknownArg;
            }
            if (!bCharSkipped) {
                stream.GetWord(); //skip the char and the rest
            }
        }
        else {
            pArgs->pszInputFile = stream.GetWord();
        }
    }

    if (!pArgs->pszInputFile) {
        CmdError(CommandError_NoSource, c);
        return CommandError_NoSource;
    }
    return 0;
}