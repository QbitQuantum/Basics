bool Lex::Run(const char * fileName) {
    std::ifstream fileP(fileName);
    Trastition trans = {State_start, State_start, Event_space};
    std::string buffer = "";
    char current;

    CreateTable();

    while(!fileP.eof()){
        fileP.get(current);
        buffer += current;

        trans.currentEvent = GetEventType(current);
        trans.prevState = trans.currentState;
        trans.currentState = tableTransition[trans.currentEvent][trans.currentState];

        // Ошибка
        if(trans.currentState == State_error)
        {
            console->LogError("Лексический анализатор", "Cчитан неизвестный символ");
            exit(1);
        }


        // Создание токена
        if(trans.currentState == State_createToken)
        {
            buffer.erase(buffer.length() - 1);
            AddTokenToList(buffer, GetTokenByState(trans.prevState));
            trans = {State_start, State_start, Event_space};
            buffer.clear();
        }

    }

    if(trans.currentState == State_createToken)
    {
        AddTokenToList(buffer, GetTokenByState(trans.prevState));
        trans = {State_start, State_start, Event_space};
        buffer.clear();
    }

    LogTokenList();
    fileP.close();
    return  true;
}