    bool testEquals( const char * actualValue, const char * expectedValue,
            const char * lineText, int lineNumber )
    {
        int i;
        for( i = 0; expectedValue[i] != '\0'; ++i )
            if( expectedValue[i] != actualValue[i] ) {
                printf( "%s\nat line %i - "
                        "Actual: %s - Expected: %s\n"
                        "First non-match is at %i\n\n",
                        lineText, lineNumber,
                        actualValue, expectedValue, i );
                return false;
            }
        if( actualValue[i] != '\0' ) {
            printf( "%s\nat line %i - "
                    "Actual: %s - Expected: %s\n"
                    "Actual string is longer\n\n",
                    lineText, lineNumber,
                    actualValue, expectedValue );
            return false;
        }

        return true;
    }