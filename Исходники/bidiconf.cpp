/*
*******************************************************************************
*
*   created on: 2013jul01
*   created by: Matitiahu Allouche

This function performs a conformance test for implementations of the
Unicode Bidirectional Algorithm, specified in UAX #9: Unicode
Bidirectional Algorithm, at http://www.unicode.org/unicode/reports/tr9/

Each test case is represented in a single line which is read from a file
named BidiCharacter.txt.  Empty, blank and comment lines may also appear
in this file.

The format of the test data is specified below.  Note that each test
case constitutes a single line of text; reordering is applied within a
single line and independently of a rendering engine, and rules L3 and L4
are out of scope.

The number sign '#' is the comment character: everything is ignored from
the occurrence of '#' until the end of the line,
Empty lines and lines containing only spaces and/or comments are ignored.

Lines which represent test cases consist of 4 or 5 fields separated by a
semicolon.  Each field consists of tokens separated by whitespace (space
or Tab).  Whitespace before and after semicolons is optional.

Field 0: A sequence of hexadecimal code point values separated by space

Field 1: A value representing the paragraph direction, as follows:
    - 0 represents left-to-right
    - 1 represents right-to-left
    - 2 represents auto-LTR according to rules P2 and P3 of the algorithm
    - 3 represents auto-RTL according to rules P2 and P3 of the algorithm
    - a negative number whose absolute value is taken as paragraph level;
      this may be useful to test cases where the embedding level approaches
      or exceeds the maximum embedding level.

Field 2: The resolved paragraph embedding level.  If the input (field 0)
         includes more than one paragraph, this field represents the
         resolved level of the first paragraph.

Field 3: An ordered list of resulting levels for each token in field 0
         (each token represents one source character).
         The UBA does not assign levels to certain characters (e.g. LRO);
         characters removed in rule X9 are indicated with an 'x'.

Field 4: An ordered list of indices showing the resulting visual ordering
         from left to right; characters with a resolved level of 'x' are
         skipped.  The number are zero-based.  Each index corresponds to
         a character in the reordered (visual) string. It represents the
         index of the source character in the input (field 0).
         This field is optional.  When it is absent, the visual ordering
         is not verified.

Examples:

# This is a comment line.
L L ON R ; 0 ; 0 ; 0 0 0 1 ; 0 1 2 3
L L ON R;0;0;0 0 0 1;0 1 2 3

# Note: in the next line, 'B' represents a block separator, not the letter 'B'.
LRE A B C PDF;2;0;x 2 0 0 x;1 2 3
# Note: in the next line, 'b' represents the letter 'b', not a block separator.
a b c 05d0 05d1 x ; 0 ; 0 ; 0 0 0 1 1 0 ; 0 1 2 4 3 5

a R R x ; 1 ; 1 ; 2 1 1 2
L L R R R B R R L L L B ON ON ; 3 ; 0 ; 0 0 1 1 1 0 1 1 2 2 2 1 1 1

*
*******************************************************************************
*/
void BiDiConformanceTest::TestBidiCharacterTest() {
    IcuTestErrorCode errorCode(*this, "TestBidiCharacterTest");
    const char *sourceTestDataPath=getSourceTestData(errorCode);
    if(errorCode.logIfFailureAndReset("unable to find the source/test/testdata "
                                      "folder (getSourceTestData())")) {
        return;
    }
    char bidiTestPath[400];
    strcpy(bidiTestPath, sourceTestDataPath);
    strcat(bidiTestPath, "BidiCharacterTest.txt");
    LocalStdioFilePointer bidiTestFile(fopen(bidiTestPath, "r"));
    if(bidiTestFile.isNull()) {
        errln("unable to open %s", bidiTestPath);
        return;
    }
    LocalUBiDiPointer ubidi(ubidi_open());
    lineNumber=0;
    levelsCount=0;
    orderingCount=0;
    errorCount=0;
    while(errorCount<20 && fgets(line, (int)sizeof(line), bidiTestFile.getAlias())!=NULL) {
        ++lineNumber;
        paraLevelName="N/A";
        inputString="N/A";
        // Remove trailing comments and whitespace.
        char *commentStart=strchr(line, '#');
        if(commentStart!=NULL) {
            *commentStart=0;
        }
        u_rtrim(line);
        const char *start=u_skipWhitespace(line);
        if(*start==0) {
            continue;  // Skip empty and comment-only lines.
        }
        // Parse the code point string in field 0.
        UChar *buffer=inputString.getBuffer(200);
        int32_t length=u_parseString(start, buffer, inputString.getCapacity(), NULL, errorCode);
        if(errorCode.logIfFailureAndReset("Invalid string in field 0")) {
            errln("Input line %d: %s", (int)lineNumber, line);
            inputString.remove();
            continue;
        }
        inputString.releaseBuffer(length);
        start=strchr(start, ';');
        if(start==NULL) {
            errorCount++;
            errln("\nError on line %d: Missing ; separator on line: %s", (int)lineNumber, line);
            continue;
        }
        start=u_skipWhitespace(start+1);
        char *end;
        int32_t paraDirection=(int32_t)strtol(start, &end, 10);
        UBiDiLevel paraLevel=UBIDI_MAX_EXPLICIT_LEVEL+2;
        if(paraDirection==0) {
            paraLevel=0;
            paraLevelName="LTR";
        }
        else if(paraDirection==1) {
            paraLevel=1;
            paraLevelName="RTL";
        }
        else if(paraDirection==2) {
            paraLevel=UBIDI_DEFAULT_LTR;
            paraLevelName="Auto/LTR";
        }
        else if(paraDirection==3) {
            paraLevel=UBIDI_DEFAULT_RTL;
            paraLevelName="Auto/RTL";
        }
        else if(paraDirection<0 && -paraDirection<=(UBIDI_MAX_EXPLICIT_LEVEL+1)) {
            paraLevel=(UBiDiLevel)(-paraDirection);
            sprintf(levelNameString, "%d", (int)paraLevel);
            paraLevelName=levelNameString;
        }
        if(end<=start || (!U_IS_INV_WHITESPACE(*end) && *end!=';' && *end!=0) ||
                         paraLevel==(UBIDI_MAX_EXPLICIT_LEVEL+2)) {
            errln("\nError on line %d: Input paragraph direction incorrect at %s", (int)lineNumber, start);
            printErrorLine();
            continue;
        }
        start=u_skipWhitespace(end);
        if(*start!=';') {
            errorCount++;
            errln("\nError on line %d: Missing ; separator on line: %s", (int)lineNumber, line);
            continue;
        }
        start++;
        uint32_t resolvedParaLevel=(uint32_t)strtoul(start, &end, 10);
        if(end<=start || (!U_IS_INV_WHITESPACE(*end) && *end!=';' && *end!=0) ||
           resolvedParaLevel>1) {
            errln("\nError on line %d: Resolved paragraph level incorrect at %s", (int)lineNumber, start);
            printErrorLine();
            continue;
        }
        start=u_skipWhitespace(end);
        if(*start!=';') {
            errorCount++;
            errln("\nError on line %d: Missing ; separator on line: %s", (int)lineNumber, line);
            return;
        }
        start++;
        if(!parseLevels(start)) {
            continue;
        }
        start=u_skipWhitespace(start);
        if(*start==';') {
            if(!parseOrdering(start+1)) {
                continue;
            }
        }
        else
            orderingCount=-1;

        ubidi_setPara(ubidi.getAlias(), inputString.getBuffer(), inputString.length(),
                      paraLevel, NULL, errorCode);
        const UBiDiLevel *actualLevels=ubidi_getLevels(ubidi.getAlias(), errorCode);
        if(errorCode.logIfFailureAndReset("ubidi_setPara() or ubidi_getLevels()")) {
            errln("Input line %d: %s", (int)lineNumber, line);
            continue;
        }
        UBiDiLevel actualLevel;
        if((actualLevel=ubidi_getParaLevel(ubidi.getAlias()))!=resolvedParaLevel) {
            printErrorLine();
            errln("\nError on line %d: Wrong resolved paragraph level; expected %d actual %d",
                   (int)lineNumber, resolvedParaLevel, actualLevel);
            continue;
        }
        if(!checkLevels(actualLevels, ubidi_getProcessedLength(ubidi.getAlias()))) {
            continue;
        }
        if(orderingCount>=0 && !checkOrdering(ubidi.getAlias())) {
            continue;
        }
    }
}