Symbol term_get_escaping_exit_level(Term* term)
{
    // Check for a call that directly causes exit: return/continue/etc.
    Symbol directExitLevel = term_get_highest_exit_level(term);
    if (directExitLevel != s_none)
        return directExitLevel;

    // For-block
    if (term->function == FUNCS.for_func) {
        Block* contents = nested_contents(term);

        for (int i=0; i < contents->length(); i++) {
            Symbol exit = term_get_highest_exit_level(contents->get(i));

            // Only ExitRankFunction escapes from for-block.
            if (exit == s_ExitLevelFunction)
                return exit;
        }

        return s_none;
    }

    // If-block
    if (term->function == FUNCS.if_block) {
        Block* topContents = nested_contents(term);
        Symbol highestExit = s_none;
        for (int caseIndex=0; caseIndex < topContents->length(); caseIndex++) {
            Block* caseBlock = nested_contents(topContents->get(caseIndex));
            for (int i=0; i < caseBlock->length(); i++) {

                Symbol exit = term_get_highest_exit_level(caseBlock->get(i));

                // All exits escape from if-block.
                highestExit = max_exit_level(exit, highestExit);
            }
        }
        return highestExit;
    }

    return s_none;
}