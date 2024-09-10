//-----------------------------------------------------------------------------
TOKEN Token(READFILE Stream, int Operation) {

//----Can't return the current token with a NULL file
    assert(!(Stream == NULL && Operation != 0));

    switch (Operation) {
        case 2:
            FreeToken(&(Stream->Auxilliary));
            FreeToken(&(Stream->CurrentToken));
            return((TOKEN)NULL);
            break;
        case 1:
//----Read into static, return it
//DEBUG if (Stream->CurrentToken != NULL ) printf("Had %s\n",CurrentToken->NameToken);
            FreeToken(&(Stream->Auxilliary));
            FreeToken(&(Stream->CurrentToken));
            Stream->CurrentToken = GetNextToken(Stream);
//DEBUG printf("Have %s\n",Stream->CurrentToken->NameToken);
            return(Stream->CurrentToken);
            break;
        case 0:
//----Return static
            FreeToken(&(Stream->Auxilliary));
            if (Stream->CurrentToken == NULL) {
                Stream->CurrentToken = GetNextToken(Stream);
                return(Stream->CurrentToken);
            } else {
//DEBUG printf("CT ==%s==\n",Stream->CurrentToken->NameToken);
                return(Stream->CurrentToken);
            }
            break;
        case -1:
//----Return static, read next into static
            FreeToken(&(Stream->Auxilliary));
            if (Stream->CurrentToken == NULL) {
                Stream->CurrentToken = GetNextToken(Stream);
            }
            Stream->Auxilliary = Stream->CurrentToken;
            Stream->CurrentToken = GetNextToken(Stream);
//DEBUG printf("%s\n",Stream->Auxilliary->NameToken);
            return(Stream->Auxilliary);
            break;
       default:
            return((TOKEN)NULL);
            break;
    }
}