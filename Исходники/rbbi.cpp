//-----------------------------------------------------------------------------------
//
//  handlePrevious()
//
//      Iterate backwards, according to the logic of the reverse rules.
//      This version handles the exact style backwards rules.
//
//      The logic of this function is very similar to handleNext(), above.
//
//-----------------------------------------------------------------------------------
int32_t BreakIterator::handlePrevious(const RBBIStateTable *statetable) {
    int32_t             state;
    int16_t             category        = 0;
    RBBIRunMode         mode;
    RBBIStateTableRow  *row;
    UChar32             c;
    int32_t             lookaheadStatus = 0;
    int32_t             result          = 0;
    int32_t             initialPosition = 0;
    int32_t             lookaheadResult = 0;
    UBool               lookAheadHardBreak = (statetable->fFlags & RBBI_LOOKAHEAD_HARD_BREAK) != 0;

    #ifdef RBBI_DEBUG
        if (fTrace) {
            RBBIDebugPuts("Handle Previous   pos   char  state category");
        }
    #endif

    // handlePrevious() never gets the rule status.
    // Flag the status as invalid; if the user ever asks for status, we will need
    // to back up, then re-find the break position using handleNext(), which does
    // get the status value.
    fLastStatusIndexValid = FALSE;
    fLastRuleStatusIndex = 0;

    // if we're already at the start of the text, return DONE.
    if (fText == NULL || fData == NULL || UTEXT_GETNATIVEINDEX(fText)==0) {
        return BreakIterator::DONE;
    }

    //  Set up the starting char.
    initialPosition = (int32_t)UTEXT_GETNATIVEINDEX(fText);
    result          = initialPosition;
    c               = UTEXT_PREVIOUS32(fText);

    //  Set the initial state for the state machine
    state = START_STATE;
    row = (RBBIStateTableRow *)
            (statetable->fTableData + (statetable->fRowLen * state));
    category = 3;
    mode     = RBBI_RUN;
    if (statetable->fFlags & RBBI_BOF_REQUIRED) {
        category = 2;
        mode     = RBBI_START;
    }


    // loop until we reach the start of the text or transition to state 0
    //
    for (;;) {
        if (c == U_SENTINEL) {
            // Reached end of input string.
            if (mode == RBBI_END || 
                *(int32_t *)fHeader->fFormatVersion == 1 ) {
                // We have already run the loop one last time with the 
                //   character set to the psueudo {eof} value.  Now it is time
                //   to unconditionally bail out.
                //  (Or we have an old format binary rule file that does not support {eof}.)
                if (lookaheadResult < result) {
                    // We ran off the end of the string with a pending look-ahead match.
                    // Treat this as if the look-ahead condition had been met, and return
                    //  the match at the / position from the look-ahead rule.
                    result               = lookaheadResult;
                    lookaheadStatus = 0;
                } else if (result == initialPosition) {
                    // Ran off start, no match found.
                    // move one index one (towards the start, since we are doing a previous())
                    UTEXT_SETNATIVEINDEX(fText, initialPosition);
                    UTEXT_PREVIOUS32(fText);   // TODO:  shouldn't be necessary.  We're already at beginning.  Check.
                }
                break;
            }
            // Run the loop one last time with the fake end-of-input character category.
            mode = RBBI_END;
            category = 1;
        }

        //
        // Get the char category.  An incoming category of 1 or 2 means that
        //      we are preset for doing the beginning or end of input, and
        //      that we shouldn't get a category from an actual text input character.
        //
        if (mode == RBBI_RUN) {
            // look up the current character's character category, which tells us
            // which column in the state table to look at.
            // Note:  the 16 in UTRIE_GET16 refers to the size of the data being returned,
            //        not the size of the character going in, which is a UChar32.
            //
            UTRIE_GET16(&fTrie, c, category);

            // Check the dictionary bit in the character's category.
            //    Counter is only used by dictionary based iterators (subclasses).
            //    Chars that need to be handled by a dictionary have a flag bit set
            //    in their category values.
            //
            if ((category & 0x4000) != 0)  {
                fDictionaryCharCount++;
                //  And off the dictionary flag bit.
                category &= ~0x4000;
            }
        }

        #ifdef RBBI_DEBUG
            if (fTrace) {
                RBBIDebugPrintf("             %4d   ", (int32_t)utext_getNativeIndex(fText));
                if (0x20<=c && c<0x7f) {
                    RBBIDebugPrintf("\"%c\"  ", c);
                } else {
                    RBBIDebugPrintf("%5x  ", c);
                }
                RBBIDebugPrintf("%3d  %3d\n", state, category);
            }
        #endif

        // State Transition - move machine to its next state
        //
        state = row->fNextState[category];
        row = (RBBIStateTableRow *)
            (statetable->fTableData + (statetable->fRowLen * state));

        if (row->fAccepting == -1) {
            // Match found, common case.
            result = (int32_t)UTEXT_GETNATIVEINDEX(fText);
        }

        if (row->fLookAhead != 0) {
            if (lookaheadStatus != 0
                && row->fAccepting == lookaheadStatus) {
                // Lookahead match is completed.  
                result               = lookaheadResult;
                lookaheadStatus      = 0;
                // TODO:  make a standalone hard break in a rule work.
                if (lookAheadHardBreak) {
                    UTEXT_SETNATIVEINDEX(fText, result);
                    return result;
                }
                // Look-ahead completed, but other rules may match further.  Continue on
                //  TODO:  junk this feature?  I don't think it's used anywhwere.
                goto continueOn;
            }

            int32_t  r = (int32_t)UTEXT_GETNATIVEINDEX(fText);
            lookaheadResult = r;
            lookaheadStatus = row->fLookAhead;
            goto continueOn;
        }


        if (row->fAccepting != 0) {
            // Because this is an accepting state, any in-progress look-ahead match
            //   is no longer relavant.  Clear out the pending lookahead status.
            lookaheadStatus = 0;    
        }

continueOn:
        if (state == STOP_STATE) {
            // This is the normal exit from the lookup state machine.
            // We have advanced through the string until it is certain that no
            //   longer match is possible, no matter what characters follow.
            break;
        }

        // Move (backwards) to the next character to process.  
        // If this is a beginning-of-input loop iteration, don't advance
        //    the input position.  The next iteration will be processing the
        //    first real input character.
        if (mode == RBBI_RUN) {
            c = UTEXT_PREVIOUS32(fText);
        } else {            
            if (mode == RBBI_START) {
                mode = RBBI_RUN;
            }
        }
    }

    // The state machine is done.  Check whether it found a match...

    // If the iterator failed to advance in the match engine, force it ahead by one.
    //   (This really indicates a defect in the break rules.  They should always match
    //    at least one character.)
    if (result == initialPosition) {
        UTEXT_SETNATIVEINDEX(fText, initialPosition);
        UTEXT_PREVIOUS32(fText);
        result = (int32_t)UTEXT_GETNATIVEINDEX(fText);
    }

    // Leave the iterator at our result position.
    UTEXT_SETNATIVEINDEX(fText, result);
    #ifdef RBBI_DEBUG
        if (fTrace) {
            RBBIDebugPrintf("result = %d\n\n", result);
        }
    #endif
    return result;
}