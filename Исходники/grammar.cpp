/// parse the alternative, such as alternative : items (| items)*
void Grammar::parseAlternative(string &ruleName, NFA **start, NFA **end) 
{
	assert(start != NULL);
	assert(end != NULL);
    // parse items
    parseItems(ruleName, start, end);
   
    if (isMatch(TT_OP, "|")) {
        // make a closing state 
        NFA *closingStartState = new NFA();
        NFA *closingEndState = new NFA;
        closingStartState->arc(*start);
        (*end)->arc(closingEndState);

        while (isMatch(TT_OP, "|")) {
            advanceToken();
            NFA *startState = NULL;
            NFA *endState = NULL;
            parseItems(ruleName, &startState, &endState);
            closingStartState->arc(startState);
            endState->arc(closingEndState); 
        }
        *start = closingStartState;
        *end = closingEndState;
    }
}