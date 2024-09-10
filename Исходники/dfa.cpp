DFA& DFA::run(string& fIn, string& fOut) {
    char input;
    bool runnable = true;
    bool inputable = true;
    tokenCnt = 0;
    currentState = startState;
    string buffer = "";

    int inputCnt = 0;
    while(runnable) {
        if (inputable &&  inputCnt >= fIn.size() ) {
            break;
        }
        if ( inputable ) {
            input = fIn[ inputCnt++ ];
        }

        inputable = true;
        t_DFA_Trans next = trans[currentState][input];

        stringstream buf;

        if ( next.valid == _ERROR_ ) {
            runnable = false;

            buf<<"ERROR Character ["<<input+","<<(int)input<<"]"<<endl;
        } else if ( next.valid == NORMAL || next.valid == PREDICATE) {
            if ( next.valid == NORMAL ) {
                if ( !next.ignore )buffer += input;
            } else if ( next.valid == PREDICATE ) {
                inputable = false;
            }
            if ( hasFinish(next.state) ) {
                matchToken(buf, buffer, finish.find(next.state)->second);
                buffer = "";
                currentState = startState;
            } else {
                currentState = next.state;
            }
        }
        fOut += buf.str();
    }
    return *this;
}