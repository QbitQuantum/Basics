void statement(int varCount)
{
    int changeSpot = 0;
    int sym;
    symbol localSymbolHolder;
    int localVarCount = varCount;
    if(token.sym == identsym)
    {
        //printf("\n\nThe token word is : %s\n\n", token.word);
        //printf("The symbol word is : %s\n", symbol_table[1].name);
        if(isSymbol(token.word))
            localSymbolHolder = symbol_table[getSymbol(token.word)];
        else
            getError(11);
        getToken();
    if(token.sym != becomessym)
        getError(5);
    getToken();
    expression();
    enter(var,localSymbolHolder.name,0,0,getTop());
    emit(4, 0, localSymbolHolder.addr);
   // printf("\n\nThe TOS IS %d\n\n", getTop());
    }
    else if(token.sym == callsym)
    {
        getToken();
        if(token.sym != identsym)
            getError(2);
        getToken();
    }
    else if(token.sym == beginsym)
    {
        emit(6, 0, 4 + localVarCount);
        getToken();
        statement(localVarCount);
        while(token.sym == semicolonsym)
        {
            getToken();
            statement(localVarCount);
        }
        if(token.sym != endsym)
             getError(6);
        getToken();
    }
    else if(token.sym == ifsym)
    {
        getToken();
        changeSpot = condition();
        if(token.sym != thensym)
            getError(6);
        getToken();
        statement(localVarCount);
    }
    else if(token.sym == whilesym)
    {
        getToken();
        condition();
        if(token.sym != dosym)
            getError(7);
        getToken();
        statement(localVarCount);
    }
   // printf("\n\nThe change spot and codespot  is: %d, %d\n\n", changeSpot, codeSpot);
    if(changeSpot != 0)
        code3[(changeSpot * 3) + 2] =codeSpot;
}