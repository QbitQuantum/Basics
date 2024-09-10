/* Compile - compile a program */
int Compile(ParseContext *c, uint8_t *imageSpace, size_t imageSize, size_t textMax, size_t dataMax)
{
    ImageHdr *image = (ImageHdr *)imageSpace;
    VMUVALUE textSize;

    /* setup an error target */
    if (setjmp(c->errorTarget) != 0)
        return -1;

    /* initialize the image */
    if (imageSize < sizeof(ImageHdr) + textMax + dataMax)
        return -1;
    memset(image, 0, sizeof(ImageHdr));
    c->image = image;
    
    /* empty the heap */
    c->localFree = c->heapBase;
    c->globalFree = c->heapTop;

    /* initialize the image */
    c->textBase = c->textFree = imageSpace + sizeof(ImageHdr);
    c->textTop = c->textBase + textMax;
    c->dataBase = c->dataFree = c->textBase + textMax;
    c->dataTop = c->dataBase + dataMax;
    
    /* initialize the code buffer */
    c->codeFree = c->codeBuf;
	c->codeTop = c->codeBuf + sizeof(c->codeBuf);

    /* initialize block nesting table */
    c->btop = (Block *)((char *)c->blockBuf + sizeof(c->blockBuf));
    c->bptr = c->blockBuf - 1;

    /* initialize the global symbol table and string table */
    InitSymbolTable(&c->globals);
    
    /* enter the built-in functions */
    EnterBuiltInFunction(c, "delayMs", bi_delayms, sizeof(bi_delayms));
    EnterBuiltInFunction(c, "updateLeds", bi_updateleds, sizeof(bi_updateleds));
    
    /* enter the built-in variables */
    /*
        typedef struct {
            int32_t triggerTop;
            int32_t triggerBottom;
            int32_t numLeds;
            int32_t led[RGB_SIZE];
			int32_t patternnum;
        } VM_variables;
    */
    EnterBuiltInVariable(c, "triggerTop", sizeof(VMVALUE));
    EnterBuiltInVariable(c, "triggerBottom", sizeof(VMVALUE));
    EnterBuiltInVariable(c, "numLeds", sizeof(VMVALUE));
    EnterBuiltInVariable(c, "led", sizeof(VMVALUE) * RGB_SIZE);
	EnterBuiltInVariable(c, "patternNum", sizeof(VMVALUE));
    
    /* initialize the string table */
    c->strings = NULL;

    /* initialize the label table */
    c->labels = NULL;

    /* start in the main code */
    c->codeType = CODE_TYPE_MAIN;

    /* initialize scanner */
    c->inComment = VMFALSE;
    c->lineNumber = 0;
    
    /* compile each line */
    while (GetLine(c)) {
        int tkn;
        if ((tkn = GetToken(c)) != T_EOL)
            ParseStatement(c, tkn);
    }

    /* end the main code with a halt */
    putcbyte(c, OP_HALT);
    
    /* write the main code */
    StartCode(c, CODE_TYPE_MAIN);
    image->entry = StoreCode(c);
    
    /* determine the text size */
    textSize = c->textFree - c->textBase;

    /* fill in the image header */
    image->dataOffset = sizeof(ImageHdr) + textSize;
    image->dataSize = c->dataFree - c->dataBase;
    image->imageSize = image->dataOffset + image->dataSize;
    
    /* make the data contiguous with the code */
    memcpy(&imageSpace[image->dataOffset], c->dataBase, image->dataSize);

#ifdef COMPILER_DEBUG
    VM_printf("entry      "); PrintValue(image->entry); VM_printf("\n");
    VM_printf("imageSize  "); PrintValue(image->imageSize); VM_printf("\n");
    VM_printf("textSize   "); PrintValue(textSize); VM_printf("\n");
    VM_printf("dataOffset ");  PrintValue(image->dataOffset); VM_printf("\n");
    VM_printf("dataSize   "); PrintValue(image->dataSize); VM_printf("\n");
    DumpSymbols(&c->globals, "symbols");
#endif

    /* return successfully */
    return 0;
}