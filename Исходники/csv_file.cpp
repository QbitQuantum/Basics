// Reads the next line from the file into dataLine
// Returns true if successful, false if EOF, -1 if blank line
int CSVFile::getLine (void)
{
    if (eof())
        return FALSE;

    fpIn.getline (dataLine, LARGE);
    curPos = 0;

    // get the length of the dataLine
    lineLength = strlen (dataLine);

    return (isBlank())? -1: TRUE;
}