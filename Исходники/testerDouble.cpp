    bool TesterDouble::testEquals( double actualValue, double expectedValue,
            const char * lineText, int lineNumber ) const
    {
        if( fabs(actualValue - expectedValue) < epsilon )
            return true;

        printf( "%s\nat line %i - "
                "Actual: %le - Expected: %le\n"
                "The value is within %le of expected. Epsilon is %le\n\n",
                lineText, lineNumber,
                actualValue, expectedValue,
                fabs(actualValue - expectedValue), epsilon);
        return false;
    }