void STATEMENT()
{
    //initialization
    if(TOKEN == identsym)
    {
        //stores the name of the identifier that will be initialized
        char name[12];
        strcpy(name, IDENTIFIER);

        //if identifier is not a variable, produce error
        if(getSymbol(IDENTIFIER).kind != 2)
        {
            ERROR("Error number 12, assignment to constant or procedure not allowed.");
        }

        GETTOKEN();
        if(TOKEN != becomessym)
        {
            ERROR("Error number 13, assignment operator expected.");
        }
        GETTOKEN();
        EXPRESSION();

        symbol current = getSymbol(name);
        //STO L M
        printToFile(4,lexiLevel-current.level,current.addr);
        lines++;
    }
    else if(TOKEN == callsym)
    {
        GETTOKEN();
        if(TOKEN != identsym)
        {
            ERROR("Error number 14, call must be followed by an identifier.");
        }

        //if the identifier is not a procedure, produce an error
        if(getSymbol(IDENTIFIER).kind != 3)
        {
            ERROR("Error number 15, call of a constant or variable is meaningless.");
        }

        symbol current = getSymbol(IDENTIFIER);
        //CAL L M
        printToFile(5, lexiLevel-current.level, current.addr);
        lines++;

        GETTOKEN();
    }
    //a group of statements
    else if(TOKEN == beginsym)
    {
        GETTOKEN();
        STATEMENT();
        while(TOKEN == semicolonsym)
        {
            GETTOKEN();
            STATEMENT();
        }
        if(TOKEN != endsym)
        {
            printf("Line: %d %s\n", lines, IDENTIFIER);
            ERROR("Error number 26, end is expected.");
        }
        GETTOKEN();
    }
    else if(TOKEN == ifsym)
    {
        GETTOKEN();
        CONDITION();
//top of the stack has whether it is true or false
        if(TOKEN != thensym)
        {
            ERROR("Error number 16, then expected.");
        }

        //after the condition, count how many instructions are written
        int currentLines = lines;
        inConditional++;
        fpos_t filePos;
        fgetpos(ifp, &filePos);

        //loop ensures this is done twice
        int i;
        for(i = 0; i < 2; i++)
        {
            if(i == 1)
            {
                inConditional--;

                //JPC 0 M = lines
                printToFile(8,0,lines);

                //returns the file to the previous position
                fsetpos(ifp, &filePos);
                lines = currentLines;
            }
            lines++;

            GETTOKEN();
            STATEMENT();

            fpos_t filePos2;
            fgetpos(ifp, &filePos2);
            if(TOKEN == semicolonsym)
            {
                GETTOKEN();
            }

            //we need another line for the jump
            if(i == 0 && TOKEN == elsesym)
            {
                lines++;
            }
            else if(TOKEN != elsesym)
            {
                TOKEN = semicolonsym;
                fsetpos(ifp, &filePos2);
            }
        }

        if(TOKEN == elsesym)
        {
            //gets the position of the else
            currentLines = lines;
            inConditional++;
            fgetpos(ifp, &filePos);
            for(i = 0; i < 2; i++)
            {
                if(i == 1)
                {
                    inConditional--;

                    //jmp end of loop
                    printToFile(7,0,lines);

                    //returns the file to the previous position
                    fsetpos(ifp, &filePos);
                    lines = currentLines;
                }
                lines++;

                GETTOKEN();
                STATEMENT();
            }
        }
    }
    else if(TOKEN == whilesym)
    {
        int jumpBackLine = lines;
        GETTOKEN();
        CONDITION();
//top of the stack has whether it is true or false
        if(TOKEN != dosym)
        {
            ERROR("Error number 18, do expected.");
        }

        //after the condition, count how many instructions are written
        int currentLines = lines;
        inConditional++;
        fpos_t filePos;
        fgetpos(ifp, &filePos);

        //loop ensures this is done twice
        int i;
        for(i = 0; i < 2; i++)
        {
            if(i == 1)
            {
                inConditional--;
//make branch here (lines + 1 contains the line that you jump to if the condition is not met)
//printToFile()
                //JPC 0 M = l
                printToFile(8,0,lines + 1);

                //returns the file to the previous position
                fsetpos(ifp, &filePos);
                lines = currentLines;
                //Lines increment for the printToFile used in for loop
                //lines++;
            }
            //the line for the branch is added
            lines++;

            GETTOKEN();
            STATEMENT();
        }
        //JMP 0 M = jumpBackLines
        printToFile(7,0,jumpBackLine);
        lines++;
    }
    else if(TOKEN == readsym)
    {
        GETTOKEN();
        if(TOKEN != identsym)
        {
            ERROR("Error number 28, identifier expected after read.");
        }

        symbol current = getSymbol(IDENTIFIER);

        if(current.kind != 2)
        {
            ERROR("Error number 29, writing to a constant or procedure is not allowed.");
        }

        //SIO 0 1
        //STO 0 M
        printToFile(9, 0, 1);
        printToFile(4,lexiLevel-current.level,current.addr);
        lines += 2;

        GETTOKEN();
    }
    else if(TOKEN == writesym)
    {
        GETTOKEN();
        if(TOKEN != identsym)
        {
            ERROR("Error number 30, identifier expected after write.");
        }

        symbol current = getSymbol(IDENTIFIER);

        if(current.kind == 3)
        {
            ERROR("Error number 31, cannot write a procedure.");
        }

        if(current.kind == 2)
        {
            //LOD L M
            printToFile(3, lexiLevel-current.level, current.addr);
        }
        if(current.kind == 1)
        {
            //LIT 0 val
            printToFile(1, 0, current.val);
        }
        //SIO 0 0
        printToFile(9, 0, 0);
        lines +=2;

        GETTOKEN();
    }
}