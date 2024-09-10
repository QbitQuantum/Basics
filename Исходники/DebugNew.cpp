void printStackTrace(MemoryAllocationRecord* rec)
{
    const unsigned int bufferSize = 512;

    // Resolve the program counter to the corresponding function names.
    unsigned int pc;
    for (int i = 0; i < MAX_STACK_FRAMES; i++)
    {
        // Check to see if we are at the end of the stack trace.
        pc = rec->pc[i];
        if (pc == 0)
            break;

        // Get the function name.
        unsigned char buffer[sizeof(IMAGEHLP_SYMBOL64) + bufferSize];
        IMAGEHLP_SYMBOL64* symbol = (IMAGEHLP_SYMBOL64*)buffer;
        DWORD64 displacement;
        memset(symbol, 0, sizeof(IMAGEHLP_SYMBOL64) + bufferSize);
        symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
        symbol->MaxNameLength = bufferSize;
        if (!SymGetSymFromAddr64(GetCurrentProcess(), pc, &displacement, symbol))
        {
            gameplay::print("[memory] STACK TRACE: <unknown location>\n");
        }
        else
        {
            symbol->Name[bufferSize - 1] = '\0';

            // Check if we need to go further up the stack.
            if (strncmp(symbol->Name, "operator new", 12) == 0)
            {
                // In operator new or new[], keep going...
            }
            else
            {
                // Get the file and line number.
                if (pc != 0)
                {
                    IMAGEHLP_LINE64 line;
                    DWORD displacement;
                    memset(&line, 0, sizeof(line));
                    line.SizeOfStruct = sizeof(line);
                    if (!SymGetLineFromAddr64(GetCurrentProcess(), pc, &displacement, &line))
                    {
                        gameplay::print("[memory] STACK TRACE: %s - <unknown file>:<unknown line number>\n", symbol->Name);
                    }
                    else
                    {
                        const char* file = strrchr(line.FileName, '\\');
                        if(!file) 
                            file = line.FileName;
                        else
                            file++;
                        
                        gameplay::print("[memory] STACK TRACE: %s - %s:%d\n", symbol->Name, file, line.LineNumber);
                    }
                }
            }
        }
    }
}