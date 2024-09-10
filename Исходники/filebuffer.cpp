// Handle preprocessor comamnds in the input
void FileBuffer::handlePreproc(string fileDataLine)
{
    /*Thanks to the preprocessor step, the location of text in
        the input file rarely matches that in the source file, but
        locations should refer to source. The preprocessor handles
        this by inserting source file locations into its output.
        These consist of a hash, a number, and the file name in
        quotes. Hunt for them here and update the source file
        location accordingly

        Anything else starting with a hash is an actual
        preprocessor command. The source code should be run
        through the preprocessor before calling this routine,
        so finding one is an error. Issue a warning and ignore
        it */

    // Search for the location by trying to extract it.
    bool haveLocation = false;
    unsigned int lineNo = 0;
    string fileName;
    bool wasWrapped = _haveWrap; // Wrapped from previous line
    _haveWrap = hasEscNewline(fileDataLine, false); // Wraps to next line
    // Locations never wrap
    if ((!wasWrapped) && (!_haveWrap)) {
        // Find the line number
        unsigned short start = 0;
        unsigned short end = 0;
        start = fileDataLine.find_first_of('#');
        start = burnSpaces(fileDataLine, start + 1); // Actual text of command
        if (start != string::npos) { // Something on line other than hash
            if (isdigit(fileDataLine[start])) {
                // Find first non digit and extract line number
                end = fileDataLine.find_first_not_of("0123456789", start);
                if (end != string::npos) { // Something after the digits
                    /* NOTE: This is not the "official" way of extracting
                        an integer from a string, but it is the fastest */
                    lineNo = atoi(fileDataLine.substr(start, end-start).c_str());
                    /* The line gives the location of the next source line. Since reading
                        that line will increment the line counter, need to decrement it here
                        to compensate */
                    lineNo--;

                    // Find the first non-space after the digits. Must be a quote
                    start = burnSpaces(fileDataLine, end);
                    if (start != string::npos) { // Found more data
                        if (fileDataLine[start] == '"') {
                            start++;
                            // Find next quote and extract file name
                            end = fileDataLine.find_first_of('"', start);
                            if (end != string::npos) {
                                // Filename with no chars is illegal
                                if (end > start) {
                                    fileName = fileDataLine.substr(start, end - start);
                                    /* Find the first non-space after the just extracted
                                        file name. If any exist, it's not a location */
                                    end++;
                                    if (end != fileDataLine.length()) {
                                        end = burnSpaces(fileDataLine, end);
                                        haveLocation = (end == string::npos);
                                    } // Quote not last char on the line
                                    else
                                        haveLocation = true;
                                    if (haveLocation)
                                        _bufferPosition = FilePosition(fileName, lineNo);
                                } // Have at least one char between quotes
                            } // Quote at end of filename exists
                        } // Quote at start of filename exists
                    } // Have non-space after the line number
                } // More chars exist after the line number
            } // First thing after hash is a digit
        } // Have something after the hash
    } // Preprocessor command did not wrap

    /* If a file location was no found, this is an actual preprocessor command
        which indicates a processing error */
    if ((!haveLocation) && (!wasWrapped))
        cout << "WARNING: Preprocessor directive " << fileDataLine << " ignored on "
             << _inputPosition << ". Must g++ -E source files before calling" << endl;
}