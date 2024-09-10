//-----------------------------------------------------------------------------
void REXA_ParserImpl::NamedRegExp		(int nAnswer)
//-----------------------------------------------------------------------------
//$1 NamedRegExp= Ident "=" RegExp.
{
    m_scanner.Match(eIdent);
    REXA_BegEnd name= m_scanner.GetToken();

    m_scanner.AdvanceAndMatch(eAssign);
    m_scanner();
    REXA_NDFAState* pState=RegExp();
    if( m_scanner.GetLastSymbol()!=eEof) {
        throw REXA_Exception(
            m_scanner.m_pTokBeg,
            m_scanner.m_pcszToParse,
            "unexpected symbol");
    }
    InsertNamedState(name,pState,nAnswer);
}