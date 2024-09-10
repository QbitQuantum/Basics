SDF_Symbol PTSymbolToSDFSymbol(PT_Symbol ptSymbol)
{
  SDF_Symbol result;

  if (PT_isSymbolLit(ptSymbol)) {
    char *str = PT_getSymbolString(ptSymbol);
    char *qstr = escape(str, "\"\\", QUOTED);
    SDF_Literal lit = SDF_makeLiteralQlit(SDF_makeQLiteralQuoted(SDF_makeCHARLISTString(qstr)));
    free(qstr);

    result = SDF_makeSymbolLit(lit);
  }
  else if (PT_isSymbolCf(ptSymbol)
	   || PT_isSymbolLex(ptSymbol)
	   || PT_isSymbolVarSym(ptSymbol)) {
    result = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));
  }
  else if (PT_isSymbolEmpty(ptSymbol)) {
    result = SDF_makeSymbolEmpty(SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolSeq(ptSymbol)) {
    PT_Symbols ptSymbols = PT_getSymbolSymbols(ptSymbol);
    PT_Symbol ptHead = PT_getSymbolsHead(ptSymbols);
    SDF_Symbol sdfHead = PTSymbolToSDFSymbol(ptHead);
    PT_Symbols ptTail = PT_getSymbolsTail(ptSymbols);
 
    if (PT_isSymbolsEmpty(ptTail)) {
      ATabort("PTSymbolToSDFSymbol: empty tail in %s\n",
              PT_yieldSymbol(ptSymbol));

      result = NULL;
    }
    else {
      SDF_SymbolTail sdfSymbolTail = 
        (SDF_SymbolTail)PTSymbolsToSDFSymbolList(ptTail);

      result = SDF_makeSymbolSeq(SDF_makeLayoutEmpty(),
                                 sdfHead, 
                                 SDF_makeLayoutSpace(),
                                 sdfSymbolTail,
                                 SDF_makeLayoutEmpty());
    }
  }
  else if (PT_isSymbolOpt(ptSymbol)) {
    SDF_Symbol sdfSymbol = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));

    result = SDF_makeSymbolOpt(sdfSymbol, SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolAlt(ptSymbol)) {
    SDF_Symbol sdfLhs = PTSymbolToSDFSymbol(PT_getSymbolLhs(ptSymbol));
    SDF_Symbol sdfRhs = PTSymbolToSDFSymbol(PT_getSymbolRhs(ptSymbol));

    result = SDF_makeSymbolAlt(sdfLhs, 
                               SDF_makeLayoutEmpty(), 
                               SDF_makeLayoutEmpty(),
                               sdfRhs);
  }
  else if (PT_isSymbolTuple(ptSymbol)) {
    SDF_Symbol sdfHead = PTSymbolToSDFSymbol(PT_getSymbolHead(ptSymbol));
    SDF_SymbolRest sdfRest = PTSymbolsToSDFSymbolRest(PT_getSymbolRest(ptSymbol));

    result = SDF_makeSymbolTuple(SDF_makeLayoutEmpty(),
                                 sdfHead, 
                                 SDF_makeLayoutEmpty(), 
                                 SDF_makeLayoutEmpty(),
                                 sdfRest,
                                 SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolSort(ptSymbol)) {
    char *str = PT_getSymbolSort(ptSymbol);
    SDF_Sort sort = SDF_makeSortMoreChars(SDF_makeCHARLISTString(str));

    result = SDF_makeSymbolSort(sort);
  }
  else if (PT_isSymbolIterPlus(ptSymbol)) { 
    SDF_Symbol sdfSymbol = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));

    result = SDF_makeSymbolIter(sdfSymbol, SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolIterStar(ptSymbol)) { 
    SDF_Symbol sdfSymbol = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));

    result = SDF_makeSymbolIterStar(sdfSymbol, SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolIterPlusSep(ptSymbol)) { 
    SDF_Symbol sdfSymbol = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));
    SDF_Symbol sdfSep = PTSymbolToSDFSymbol(PT_getSymbolSeparator(ptSymbol));

    result = SDF_makeSymbolIterSep(SDF_makeLayoutEmpty(),
                                   sdfSymbol, 
                                   SDF_makeLayoutSpace(),
                                   sdfSep,
                                   SDF_makeLayoutEmpty(),
                                   SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolIterStarSep(ptSymbol)) { 
    SDF_Symbol sdfSymbol = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));
    SDF_Symbol sdfSep = PTSymbolToSDFSymbol(PT_getSymbolSeparator(ptSymbol));

    result = SDF_makeSymbolIterStarSep(SDF_makeLayoutEmpty(),
                                       sdfSymbol, 
                                       SDF_makeLayoutSpace(),
                                       sdfSep,
                                       SDF_makeLayoutEmpty(),
                                       SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolIterN(ptSymbol)) { 
    char str[BUFSIZ];
    SDF_Symbol sdfSymbol = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));
    int nr = PT_getSymbolNumber(ptSymbol);
    SDF_NatCon sdfNatCon;
    sprintf(str, "%d", nr);
    
    sdfNatCon = SDF_makeNatConDigits(SDF_makeCHARLISTString(str));

    result = SDF_makeSymbolIterN(sdfSymbol, 
                                 SDF_makeLayoutSpace(),
                                 sdfNatCon,
                                 SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolIterSepN(ptSymbol)) { 
    char str[BUFSIZ];
    SDF_Symbol sdfSymbol = PTSymbolToSDFSymbol(PT_getSymbolSymbol(ptSymbol));
    SDF_Symbol sdfSep = PTSymbolToSDFSymbol(PT_getSymbolSeparator(ptSymbol));
    int nr = PT_getSymbolNumber(ptSymbol);
    SDF_NatCon sdfNatCon;
    sprintf(str, "%d", nr);
    
    sdfNatCon = SDF_makeNatConDigits(SDF_makeCHARLISTString(str));

    result = SDF_makeSymbolIterSepN(SDF_makeLayoutEmpty(),
                                    sdfSymbol, 
                                    SDF_makeLayoutSpace(),
                                    sdfSep,
                                    SDF_makeLayoutEmpty(),
                                    SDF_makeLayoutEmpty(),
                                    sdfNatCon,
                                    SDF_makeLayoutEmpty());
  }
  else if (PT_isSymbolLayout(ptSymbol)) {
    ATabort("PTSymbolToSDFSymbol: layout.\n");
    result = NULL;
  }
  else {
    ATabort("PTSymbolToSDFSymbol: unable to convert symbol %t: %s\n",
            ptSymbol, PT_yieldSymbol(ptSymbol));

    result = NULL;
  }
  return result;
}