boolean faReadMixedNext(FILE *f, boolean preserveCase, char *defaultName, 
    boolean mustStartWithComment, char **retCommentLine, struct dnaSeq **retSeq)
/* Read next sequence from .fa file. Return sequence in retSeq.  
 * If retCommentLine is non-null return the '>' line in retCommentLine.
 * The whole thing returns FALSE at end of file. 
 * Contains parameter to preserve mixed case. */
{
char lineBuf[1024];
int lineSize;
char *words[1];
int c;
off_t offset = ftello(f);
size_t dnaSize = 0;
DNA *dna, *sequence;
char *name = defaultName;

if (name == NULL)
    name = "";
dnaUtilOpen();
if (retCommentLine != NULL)
    *retCommentLine = NULL;
*retSeq = NULL;

/* Skip first lines until it starts with '>' */
for (;;)
    {
    if(fgets(lineBuf, sizeof(lineBuf), f) == NULL)
        {
        if (ferror(f))
            errnoAbort("read of fasta file failed");
        return FALSE;
        }
    lineSize = strlen(lineBuf);
    if (lineBuf[0] == '>')
        {
	if (retCommentLine != NULL)
            *retCommentLine = cloneString(lineBuf);
        offset = ftello(f);
        chopByWhite(lineBuf, words, ArraySize(words));
        name = words[0]+1;
        break;
        }
    else if (!mustStartWithComment)
        {
        if (fseeko(f, offset, SEEK_SET) < 0)
            errnoAbort("fseek on fasta file failed");
        break;
        }
    else
        offset += lineSize;
    }
/* Count up DNA. */
for (;;)
    {
    c = fgetc(f);
    if (c == EOF || c == '>')
        break;
    if (isalpha(c))
        {
        ++dnaSize;
        }
    }

if (dnaSize == 0)
    {
    warn("Invalid fasta format: sequence size == 0 for element %s",name);
    }

/* Allocate DNA and fill it up from file. */
dna = sequence = needHugeMem(dnaSize+1);
if (fseeko(f, offset, SEEK_SET) < 0)
    errnoAbort("fseek on fasta file failed");
for (;;)
    {
    c = fgetc(f);
    if (c == EOF || c == '>')
        break;
    if (isalpha(c))
        {
        /* check for non-DNA char */
        if (ntChars[c] == 0)
            {
            *dna++ = preserveCase ? 'N' : 'n';
            }
        else
            {
            *dna++ = preserveCase ? c : ntChars[c];
            }
        }
    }
if (c == '>')
    ungetc(c, f);
*dna = 0;

*retSeq = newDnaSeq(sequence, dnaSize, name);
if (ferror(f))
    errnoAbort("read of fasta file failed");    
return TRUE;
}