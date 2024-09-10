void CommandProcessor::parseCommandLine(const char* commandLine, int* argc, char*** argv)
{
        UtlString arg;
        int argIndex = 0;

        // Hard code length for now;
        *argv = new char*[1024];
        *argc = 0;

        if(commandLine)
        {
                //printf("creating tokenizer\n");
                UtlTokenizer tokenizer(commandLine);

                do
                {
                        arg.remove(0);
                        tokenizer.next(arg, " \t\n");

                        //printf("arg[%d]=\"%s\"\n", argIndex, arg.data());
                        if(!arg.isNull())
                        {
                                (*argv)[argIndex] = new char[strlen(arg.data()) + 1];
                                strcpy((*argv)[argIndex], arg.data());

                                argIndex++;
                        }

                }
                while(!arg.isNull());
        }
        *argc = argIndex;
}