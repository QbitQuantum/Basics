void main()
{
    ScriptRun scriptRun(testChars, 0, testLength);

    while (scriptRun.next()) {
        int32_t     start = scriptRun.getScriptStart();
        int32_t     end   = scriptRun.getScriptEnd();
        UScriptCode code  = scriptRun.getScriptCode();

        printf("Script '%s' from %d to %d.\n", uscript_getName(code), start, end);
    }
}