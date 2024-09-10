/* This is the final, internal function for printing text to a console */
void OGLCONSOLE_Output(OGLCONSOLE_Console console, const char *s, ...)
{
    va_list argument;

    /* cache some console properties */
    int lineQueueIndex = C->lineQueueIndex;
    int lineScrollIndex = C->lineScrollIndex;
    int textWidth = C->textWidth;
    int maxLines = C->maxLines;

    /* String buffer */
    char output[4096];

    /* string copy cursors */
    char *consoleCursor, *outputCursor = output;

    /* Acrue arguments in argument list */
    va_start(argument, s);
    vsnprintf(output, 4096, s, argument);
    va_end(argument);



    /* This cursor tells us where in the console display we are currently
     * copying text into from the "output" string */
    consoleCursor = C->outputCursor;

    while (*outputCursor)
    {
        /* Here we check to see if any conditions require console line
         * advancement. These two conditions are:
            1) Hitting the end of the screen
            2) Getting a newline character (indicated by "outputNewline") */
        if((C->outputNewline) ||
            (consoleCursor - (C->lines + lineQueueIndex * textWidth))
                >= (textWidth - 1))
        {
            C->outputNewline = 0;

            //puts("incrementing to the next line");

            /* Inrement text-line index, with wrapping */
            if (++lineQueueIndex >= maxLines)
                lineQueueIndex = 0;

            /* Scroll the console display one line TODO: Don't scroll if the console is
             * currently scrolled away from the end of output? */
            if (++lineScrollIndex >= maxLines)
                lineScrollIndex = 0;

            /* Reposition the cursor at the beginning of the new line */
            consoleCursor = C->lines + lineQueueIndex * C->textWidth;
        }
        
        /* If we encounter a newline character, we set the newline flag, which
         * tells the console to advance one line before it prints the next
         * character. The reason we do it this way is to defer line-advancement,
         * and thus we needn't suffer through a needless blank line between
         * console output and the command line, wasting precious screen
         * real-estate */
        if (*outputCursor == '\n')
        {
            C->outputNewline = 1;
            outputCursor++;
            continue;
        }

        /* If we encounter a tab character we must expand that character
         * appropriately */
        if (*outputCursor == '\t')
        {
            const int TAB_WIDTH = 8;

            int n = (consoleCursor - (C->lines + lineQueueIndex * textWidth)) % TAB_WIDTH;

            /* Are we indenting our way off the edge of the screen? */
            if (textWidth - n <= TAB_WIDTH)
            {
                /* Switch on the console's newline bit, and advance through the
                 * string output we've been given */
                C->outputNewline = 1;
                outputCursor++;
                continue;
            }

            /* Normal indent */
            else
            {
                n = TAB_WIDTH - n % TAB_WIDTH;
                while (n--) *(consoleCursor++) = ' ';
                outputCursor++;
                continue;
            }
        }

        /* copy a single character */
        *(consoleCursor++) = *(outputCursor++);
    }

    /* Unless we're at the very end of our current line, we finish up by capping
     * a NULL terminator on the current line */
    if (consoleCursor != C->lines + (lineQueueIndex+1) *C->textWidth -1)
        *consoleCursor = '\0';

    /* Restore cached values */
    C->lineQueueIndex = lineQueueIndex;
    C->lineScrollIndex = lineScrollIndex;
    C->outputCursor = consoleCursor; // TODO: confusing variable names

    /* old way of copying the text into the console */
    //strcpy(C->lines[C->lineQueueIndex], output);
#ifdef DEBUG
    printf("Copied \"%s\" into line %i\n", output, C->lineQueueIndex);
#endif
}