TypeNameFossilIntTab *readFossilIntTab(FILE *f) {
    int sizeBuf;
    char c;
    TypeNameFossilIntTab *res;

    res = (TypeNameFossilIntTab *) malloc(sizeof(TypeNameFossilIntTab));
    sizeBuf = INC_FOSSIL_ITEM;
    res->name = (char**) malloc(sizeBuf*sizeof(char*));
    res->fossilIntTab = (TypeFossilIntTab*) malloc(sizeBuf*sizeof(TypeFossilIntTab));
    res->size = 0;
    do {
        char *tmp;
        int i;
        tmp = (char*) malloc((MAX_NAME_SIZE+1)*sizeof(char));
        for(c = fgetc(f); c != EOF && issepline(c); c = fgetc(f));
        if(c == '\'' || c == '"') {
            c = fgetc(f);
            for(i=0; i<MAX_NAME_SIZE && c != EOF && c != '\'' && c != '"'; i++) {
                tmp[i] = c;
                c = fgetc(f);
            }
            if(c == '\'' || c == '"')
                c = fgetc(f);
        } else {
            for(i=0; i<MAX_NAME_SIZE && c !=EOF && !issep(c); i++) {
                tmp[i] = c;
                c = fgetc(f);
            }
        }
        if(i == MAX_NAME_SIZE)
            exitProg(ErrorExec, "Name too much long...");
        tmp[i++] = '\0';
        if(i>1) {
            char bof[MAX_NAME_SIZE+1];
            int sizeFossilIntBuf = INC_FOSSIL_ITEM;
            if(res->size >= sizeBuf) {
                sizeBuf += INC_FOSSIL_ITEM;
                res->name = (char**) realloc((void*) res->name, sizeBuf*sizeof(char*));
                res->fossilIntTab = (TypeFossilIntTab*) realloc((void*) res->fossilIntTab, sizeBuf*sizeof(TypeFossilIntTab));
            }
            res->name[res->size] = (char *) realloc((void*) tmp, i*sizeof(char));
            fixSpace(res->name[res->size]);
            res->fossilIntTab[res->size].size = 0;
            res->fossilIntTab[res->size].fossilInt = (TypeTimeInterval*) malloc(sizeFossilIntBuf*sizeof(TypeTimeInterval));
            for(; c != EOF && issep(c); c = fgetc(f));
            while(c != EOF && !isline(c)) {
                for(i=0; c != EOF && !issepline(c) && i<MAX_NAME_SIZE; i++) {
                    bof[i] = c;
                    c = fgetc(f);
                }
                bof[i++] = '\0';
                if(res->fossilIntTab[res->size].size>=sizeFossilIntBuf) {
                    sizeFossilIntBuf += INC_FOSSIL_ITEM;
                    res->fossilIntTab[res->size].fossilInt = (TypeTimeInterval*) realloc((void*) res->fossilIntTab[res->size].fossilInt, sizeFossilIntBuf*sizeof(TypeTimeInterval));
                }
                res->fossilIntTab[res->size].fossilInt[res->fossilIntTab[res->size].size++] = toFossilInt(bof);
DEBUG(
    printf("\"%s\"\t%s\t", tmp, bof);
    fprintFossilInt(stdout, res->fossilIntTab[res->size].fossilInt[res->fossilIntTab[res->size].size-1]);
    printf("\n");
)
                for(; c != EOF && issep(c); c = fgetc(f));
            }
            res->size++;
        } else