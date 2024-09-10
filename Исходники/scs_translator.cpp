SCsTranslator::eSentenceType SCsTranslator::determineSentenceType(pANTLR3_BASE_TREE node)
{
    pANTLR3_COMMON_TOKEN tok = node->getToken(node);
    assert(tok);

    if (tok->type == SEP_SIMPLE)
        return SentenceLevel1;

    if (tok->type == CONNECTORS)
        return SentenceLevel2_7;

    if (tok->type == SEP_ASSIGN)
        return SentenceAssign;

    if (tok->type == EOF)
        return SentenceEOF;

    return SentenceUnknown;
}