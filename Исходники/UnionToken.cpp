// ---------------------------------------------------------------------------
//  UnionToken: Children manipulation methods
// ---------------------------------------------------------------------------
void UnionToken::addChild(Token* const child, TokenFactory* const tokFactory) {

    if (child == 0)
        return;

    if (fChildren == 0)
        fChildren = new (tokFactory->getMemoryManager()) RefVectorOf<Token>(INITIALSIZE, false, tokFactory->getMemoryManager());

    if (getTokenType() == T_UNION) {

        fChildren->addElement(child);
        return;
    }

    Token::tokType childType = child->getTokenType();
    if (childType == T_CONCAT) {

        XMLSize_t childSize = child->size();
        for (XMLSize_t i = 0; i < childSize; i++) {

            addChild(child->getChild(i), tokFactory);
        }

        return;
    }

    XMLSize_t childrenSize = fChildren->size();
    if (childrenSize == 0) {

        fChildren->addElement(child);
        return;
    }

    Token* previousTok = fChildren->elementAt(childrenSize - 1);
    Token::tokType previousType = previousTok->getTokenType();

    if (!((previousType == T_CHAR || previousType == T_STRING)
          && (childType == T_CHAR || childType == T_STRING))) {

        fChildren->addElement(child);
        return;
    }

    // Continue
    XMLBuffer stringBuf(1023, tokFactory->getMemoryManager());

    if (previousType == T_CHAR) {

        XMLInt32 ch = previousTok->getChar();

        if (ch >= 0x10000) {

            XMLCh* chSurrogate = RegxUtil::decomposeToSurrogates(ch, tokFactory->getMemoryManager());
            stringBuf.append(chSurrogate);
            tokFactory->getMemoryManager()->deallocate(chSurrogate);//delete [] chSurrogate;
        }
        else {
            stringBuf.append((XMLCh) ch);
        }

        previousTok = tokFactory->createString(0);
        fChildren->setElementAt(previousTok, childrenSize - 1);
    }
    else {
        stringBuf.append(previousTok->getString());
    }

    if (childType == T_CHAR) {

        XMLInt32 ch = child->getChar();

        if (ch >= 0x10000) {

            XMLCh* chSurrogate = RegxUtil::decomposeToSurrogates(ch, tokFactory->getMemoryManager());
            stringBuf.append(chSurrogate);
            tokFactory->getMemoryManager()->deallocate(chSurrogate);//delete [] chSurrogate;
        }
        else {
            stringBuf.append((XMLCh) ch);
        }
    }
    else {
        stringBuf.append(child->getString());
    }

    ((StringToken*) previousTok)->setString(stringBuf.getRawBuffer());
}