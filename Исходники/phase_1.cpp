bool tAddNode(const char* pType, const unsigned char* pValue, bool delim, bool nullTerminated, bool unicode)
{
        struct tNode* pTokenNode;

        pTokenNode = (struct tNode *) calloc( 1, sizeof(struct tNode ) );

        if( pTokenNode == NULL )                                //error allocating node
                return false;           
        else {                                  //ok allocating node
                memset(pTokenNode->chTokenType, NULL, 3);
                pTokenNode->pTokenValue = NULL;

                memcpy_s (pTokenNode->chTokenType, _countof(pTokenNode->chTokenType), pType, strlen((char*)pType));

                pTokenNode->pTokenValue = (unsigned char*) calloc (_msize((unsigned char*)pValue), sizeof(char));
                if (pTokenNode->pTokenValue == NULL) 
                        return false;
                
                memcpy_s (pTokenNode->pTokenValue, _msize(pTokenNode->pTokenValue), pValue, _msize((char*)pValue));

                pTokenNode->bDelim = delim;
                pTokenNode->bNullTerminated = nullTerminated;
                pTokenNode->bUnicode = unicode;
                pTokenNode->next = NULL;
        }

        nNodeCount++;
        tAdd(pTokenNode);

        return true;                 
}