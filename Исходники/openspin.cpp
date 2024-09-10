void PrintError(const char* pFilename, const char* pErrorString)
{
    int lineNumber = 1;
    int column = 1;
    int offsetToStartOfLine = -1;
    int offsetToEndOfLine = -1;
    int offendingItemStart = 0;
    int offendingItemEnd = 0;
    GetErrorInfo(lineNumber, column, offsetToStartOfLine, offsetToEndOfLine, offendingItemStart, offendingItemEnd);

    printf("%s(%d:%d) : error : %s\n", pFilename, lineNumber, column, pErrorString);

    char errorItem[512];
    char errorLine[512];
    if ( offendingItemStart == offendingItemEnd && s_pCompilerData->source[offendingItemStart] == 0 )
    {
        strcpy(errorLine, "End Of File");
        strcpy(errorItem, "N/A");
    }
    else
    {
        strncpy(errorLine, &s_pCompilerData->source[offsetToStartOfLine], offsetToEndOfLine - offsetToStartOfLine);
        errorLine[offsetToEndOfLine - offsetToStartOfLine] = 0;

        strncpy(errorItem, &s_pCompilerData->source[offendingItemStart], offendingItemEnd - offendingItemStart);
        errorItem[offendingItemEnd - offendingItemStart] = 0;
    }

    printf("Line:\n%s\nOffending Item: %s\n", errorLine, errorItem);
}