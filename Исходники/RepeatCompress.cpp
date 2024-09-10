    void ScanParamString(char *paramstr,int len)
    // Parses a parameter string
    {
        char  *endptr=paramstr+len,*endstringptr;

        // Skip all white spaces
        while(paramstr<endptr)
        {
            if((*paramstr!=' ')&&(*paramstr!=',')&&(*paramstr!='\t')&&
                    (*paramstr!='\r')&&(*paramstr!='\n'))
                break;
            paramstr++;
        }

        // Parse the delimiter string
        endstringptr=::ParseString(paramstr,endptr);
        if(endstringptr==NULL)
        {
            Error("First parameter in rep(");
            ErrorCont(paramstr,len);
            ErrorCont(") should be a string!");
            Exit();
        }

        // Store the delimiter string
        delimiter=paramstr+1;
        delimiterlen=endstringptr-delimiter;

        // Skip white spaces
        endstringptr++;

        while(endstringptr<endptr)
        {
            if((*endstringptr!=' ')&&(*endstringptr!=',')&&(*endstringptr!='\t')&&
                    (*endstringptr!='\r')&&(*endstringptr!='\n'))
                break;
            endstringptr++;
        }

        // Next, there must be the compressor as a parameter

        subcompressor2=NULL;
        subcompressor=compressman.CreateCompressorInstance(endstringptr,endptr);

        if(subcompressor->IsRejecting())
        {
            Error("Compressor '");
            ErrorCont(endstringptr,endptr-endstringptr);
            ErrorCont("' must always accept the string!\n");
            Exit();
        }

        subuncompressor2=NULL;
        subuncompressor=compressman.CreateUncompressorInstance(endstringptr,endptr);

        // Skip white spaces
        while(endstringptr<endptr)
        {
            if((*endstringptr!=' ')&&(*endstringptr!=',')&&(*endstringptr!='\t')&&
                    (*endstringptr!='\r')&&(*endstringptr!='\n'))
                break;
            endstringptr++;
        }

        // No additional tail compressor?
        if(*endstringptr==')')
            return;

        // Otherwise find the tail compressor

        subcompressor2=compressman.CreateCompressorInstance(endstringptr,endptr);

        subuncompressor2=compressman.CreateUncompressorInstance(endstringptr,endptr);


        // Skip white spaces
        while(endstringptr<endptr)
        {
            if((*endstringptr!=' ')&&(*endstringptr!=',')&&(*endstringptr!='\t')&&
                    (*endstringptr!='\r')&&(*endstringptr!='\n'))
                break;
            endstringptr++;
        }

        // Last character must be ')'
        if(*endstringptr!=')')
        {
            Error("Missing closed parenthesis in '");
            ErrorCont(paramstr,len);
            Exit();
        }
    }