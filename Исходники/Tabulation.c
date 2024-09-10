void setLiteralsAndValues(char *lits, unsigned litCount, unsigned *vals, unsigned valCount) {
        // Check wether process is already running
    if (processRunning) {
        fprintf(stderr, "Process already started - literals and values cannot be set at this stage");
        return;
    }
    
        // Copy the literals and values
    if (UNEXPECTED((literals = (char *)malloc(litCount * sizeof(char))) == NULL)) {
        fprintf(stderr, "Not enough memory");
        return;
    } else {
        memcpy(literals, lits, sizeof(unsigned)*litCount);
    }
    
    values = copyUnsigned(vals, valCount);
    literalCount = litCount;
    valueCount = valCount;
    literalsSet = true;
}