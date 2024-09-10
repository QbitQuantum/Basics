void EditWorkspace(System *sys)
{
    VMVALUE lineNumber;
    char *token;

    BufInit();
    
    VM_printf("ebasic 0.001\n");

    for (;; ) {
        
        VM_getline(sys->lineBuf, sizeof(sys->lineBuf));

        sys->linePtr = sys->lineBuf;

        if ((token = NextToken(sys)) != NULL) {
            if (ParseNumber(token, &lineNumber)) {
                if (IsBlank(sys->linePtr)) {
                    if (!BufDeleteLineN(lineNumber))
                        VM_printf("no line %d\n", lineNumber);
                }
                else if (!BufAddLineN(lineNumber, sys->linePtr))
                    VM_printf("out of edit buffer space\n");
            }

            else {
                int i;
                for (i = 0; cmds[i].name != NULL; ++i)
                    if (strcasecmp(token, cmds[i].name) == 0)
                        break;
                    if (cmds[i].handler) {
                        (*cmds[i].handler)(sys);
                        VM_printf("OK\n");
                    }
                else
                    VM_printf("unknown command: %s\n", token);
            }
        }
    }
}