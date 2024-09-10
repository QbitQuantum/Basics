  /** \brief Check wheter a token at a given position is a string.
      \param a_Tok [out] If a variable token has been found it will be placed here.
  	  \return true if a string token has been found.
      \sa IsOprt, IsFunTok, IsStrFunTok, IsValTok, IsVarTok, IsEOF, IsInfixOpTok, IsPostOpTok
      \throw nothrow
  */
  bool ParserTokenReader::IsString(token_type &a_Tok)
  {
    if (m_strFormula[m_iPos]!='"') 
      return false;

    string_type strBuf(&m_strFormula[m_iPos+1]);
    std::size_t iEnd(0), iSkip(0);

    // parser over escaped '\"' end replace them with '"'
    for(iEnd=(int)strBuf.find( _T("\"") ); iEnd!=0 && iEnd!=string_type::npos; iEnd=(int)strBuf.find( _T("\""), iEnd))
    {
      if (strBuf[iEnd-1]!='\\') break;
      strBuf.replace(iEnd-1, 2, _T("\"") );
      iSkip++;
    }

    if (iEnd==string_type::npos)
      Error(ecUNTERMINATED_STRING, m_iPos, _T("\"") );

    string_type strTok(strBuf.begin(), strBuf.begin()+iEnd);

    if (m_iSynFlags & noSTR)
      Error(ecUNEXPECTED_STR, m_iPos, strTok);

		m_pParser->m_vStringBuf.push_back(strTok); // Store string in internal buffer
    a_Tok.SetString(strTok, m_pParser->m_vStringBuf.size());

    m_iPos += (int)strTok.length() + 2 + (int)iSkip;  // +2 wg Anführungszeichen; +iSkip für entfernte escape zeichen
    m_iSynFlags = noANY ^ ( noARG_SEP | noBC | noOPT | noEND );

    return true;
  }