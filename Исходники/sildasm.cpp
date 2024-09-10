void DecodeIL(IMetaDataImport *pImport, BYTE *buffer, ULONG bufSize)
{
    // First decode the header
    COR_ILMETHOD *pHeader = (COR_ILMETHOD *) buffer;    
    COR_ILMETHOD_DECODER header(pHeader);    

    // Set globals
    position = 0;	
    pBuffer = (BYTE *) header.Code;

    UINT indentCount = 0;
    ULONG endCodePosition = header.GetCodeSize();
    while(position < endCodePosition)
    {	
        for (unsigned e=0;e<header.EHCount();e++)
        {
            IMAGE_COR_ILMETHOD_SECT_EH_CLAUSE_FAT ehBuff;
            const IMAGE_COR_ILMETHOD_SECT_EH_CLAUSE_FAT* ehInfo;
            
            ehInfo = header.EH->EHClause(e,&ehBuff);
            if (ehInfo->TryOffset == position)
            {
                printf ("%*s.try\n%*s{\n", indentCount, "", indentCount, "");
                indentCount+=2;
            }
            else if ((ehInfo->TryOffset + ehInfo->TryLength) == position)
            {
                indentCount-=2;
                printf("%*s} // end .try\n", indentCount, "");
            }

            if (ehInfo->HandlerOffset == position)
            {
                if (ehInfo->Flags == COR_ILEXCEPTION_CLAUSE_FINALLY)
                    printf("%*s.finally\n%*s{\n", indentCount, "", indentCount, "");
                else
                    printf("%*s.catch\n%*s{\n", indentCount, "", indentCount, "");

                indentCount+=2;
            }
            else if ((ehInfo->HandlerOffset + ehInfo->HandlerLength) == position)
            {
                indentCount-=2;
                
                if (ehInfo->Flags == COR_ILEXCEPTION_CLAUSE_FINALLY)
                    printf("%*s} // end .finally\n", indentCount, "");
                else
                    printf("%*s} // end .catch\n", indentCount, "");
            }
        }        
        
        printf("%*sIL_%04x: ", indentCount, "", position);
        unsigned int c = readOpcode();
        OpCode opcode = opcodes[c];
        printf("%s ", opcode.name);

        switch(opcode.args)
        {
        case InlineNone: break;
        
        case ShortInlineVar:
            printf("VAR OR ARG %d",readData<BYTE>()); break;
        case InlineVar:
            printf("VAR OR ARG %d",readData<unsigned short>()); break;
        case InlineI:
            printf("%d",readData<long>()); 
            break;
        case InlineR:
            printf("%f",readData<double>());
            break;
        case InlineBrTarget:
            printf("IL_%04x",readData<long>() + position); break;
        case ShortInlineBrTarget:
            printf("IL_%04x",readData<BYTE>()  + position); break;
        case InlineI8:
            printf("%ld", readData<__int64>()); break;
            
        case InlineMethod:
        case InlineField:
        case InlineType:
        case InlineTok:
        case InlineSig:        
        {
            long l = readData<long>();
            if (pImport != NULL)
            {
                DisassembleToken(pImport, l);
            }
            else
            {
                printf("TOKEN %x", l); 
            }
            break;
        }
            
        case InlineString:
        {
            long l = readData<long>();

            ULONG numChars;
            WCHAR str[84];

            if ((pImport != NULL) && (pImport->GetUserString((mdString) l, str, 80, &numChars) == S_OK))
            {
                if (numChars < 80)
                    str[numChars] = 0;
                wcscpy_s(&str[79], 4, W("..."));
                WCHAR* ptr = str;
                while(*ptr != 0) {
                    if (*ptr < 0x20 || * ptr >= 0x80) {
                        *ptr = '.';
                    }
                    ptr++;
                }

                printf("\"%S\"", str);
            }
            else
            {
                printf("STRING %x", l); 
            }
            break;
        }
            
        case InlineSwitch:
        {
            long cases = readData<long>();
            long *pArray = new long[cases];            
            long i=0;
            for(i=0;i<cases;i++)
            {
                pArray[i] = readData<long>();
            }
            printf("(");
            for(i=0;i<cases;i++)
            {
                if (i != 0)
                    printf(", ");
                printf("IL_%04x",pArray[i] + position);
            }
            printf(")");
            delete [] pArray;
            break;
        }
        case ShortInlineI:
            printf("%d", readData<char>()); break;
        case ShortInlineR:		
            printf("%f", readData<float>()); break;
        default: printf("Error, unexpected opcode type\n"); break;
        }

        printf("\n");
    }
}