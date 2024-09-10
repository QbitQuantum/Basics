int CommonLanguageAnalyzer::analyze_impl(const Term& input, void* data, HookType func)
{
    parse(input.text_);

    unsigned char topAndOrBit = Term::AND;
    int tempOffset = 0;
    int lastWordOffset = -1;

    while (nextToken())
    {
        if (len_ == 0)
            continue;

        if (bRemoveStopwords_ && isStopword())
            continue;

/*            {
            UString foo(token_, len_); string bar; foo.convertString(bar, UString::UTF_8);
            cout << "(" << bar << ") --<> " << isIndex_ << "," << offset_ << "," << isRaw_ << "," << level_ << endl;
            }*/

        if (bChinese_)
        {
            int curWordOffset = offset_;
            if (curWordOffset == lastWordOffset)
                topAndOrBit = Term::OR;
            else
                topAndOrBit = Term::AND;
            lastWordOffset = curWordOffset;
        }

        if (isIndex_)
        {
            if (isSpecialChar())
            {
                func(data, token_, len_, offset_, Term::SpecialCharPOS, Term::AND, level_, true);
                tempOffset = offset_;
                continue;
            }
            if (isRaw_)
            {
                func(data, token_, len_, offset_, pos_, Term::OR, level_, false);
                tempOffset = offset_;
                continue;
            }

            // foreign language, e.g. English
            if (isAlpha())
            {
                UString::CharT* lowercaseTermUstr = lowercase_ustring_buffer_;
                bool lowercaseIsDifferent = UString::toLowerString(token_, len_,
                                            lowercase_ustring_buffer_, term_ustring_buffer_limit_);

                char* lowercaseTerm = lowercase_string_buffer_;
                UString::convertString(UString::UTF_8, lowercaseTermUstr, len_, lowercase_string_buffer_, term_string_buffer_limit_);

                UString::CharT* stemmingTermUstr = NULL;
                size_t stemmingTermUstrSize = 0;

                UString::CharT * synonymResultUstr = NULL;
                size_t synonymResultUstrLen = 0;

                if (bExtractEngStem_)
                {
                    /// TODO: write a UCS2 based stemmer
                    string stem_term;
                    pStemmer_->stem(lowercaseTerm, stem_term);
                    if (strcmp(stem_term.c_str(), lowercaseTerm))
                    {
                        stemmingTermUstr = stemming_ustring_buffer_;
                        stemmingTermUstrSize = UString::toUcs2(UString::UTF_8,
                                stem_term.c_str(), stem_term.size(), stemming_ustring_buffer_, term_ustring_buffer_limit_);
                    }
                }

//              if (false /*bExtractSynonym_, preprocessed*/)
//              {
//                  pSynonymContainer_ = uscSPtr_->getSynonymContainer();
//                  pSynonymContainer_->searchNgetSynonym(lowercaseTerm, pSynonymResult_);
//                  char * synonymResult = pSynonymResult_->getHeadWord(0);
//                  if (synonymResult)
//                  {
//                      size_t synonymResultLen = strlen(synonymResult);
//                      if (synonymResultLen <= term_ustring_buffer_limit_)
//                      {
//                          synonymResultUstr = synonym_ustring_buffer_;
//                          synonymResultUstrLen = UString::toUcs2(synonymEncode_,
//                                  synonymResult, synonymResultLen, synonym_ustring_buffer_, term_ustring_buffer_limit_);
//                      }
//                  }
//              }

                if (stemmingTermUstr || synonymResultUstr || (bCaseSensitive_ && bContainLower_ && lowercaseIsDifferent))
                {
                    /// have more than one output
                    if (bCaseSensitive_)
                    {
                        func(data,  token_, len_, offset_, Term::EnglishPOS, Term::OR, level_+1, false);
                        tempOffset = offset_;
                    }
                    else
                    {
                        func(data, lowercaseTermUstr, len_, offset_, Term::EnglishPOS, Term::OR, level_+1, false);
                        tempOffset = offset_;
                    }
                    if (stemmingTermUstr)
                    {
                        func(data, stemmingTermUstr, stemmingTermUstrSize, offset_, Term::EnglishPOS, Term::OR, level_+1, false);
                        tempOffset = offset_;
                    }
                    if (synonymResultUstr)
                    {
                        func(data, synonymResultUstr, synonymResultUstrLen, offset_, NULL, Term::OR, level_+1, false);
                        tempOffset = offset_;
                    }
                    if (bCaseSensitive_ && bContainLower_ && lowercaseIsDifferent)
                    {
                        func(data, lowercaseTermUstr, len_, offset_, Term::EnglishPOS, Term::OR, level_+1, false);
                        tempOffset = offset_;
                    }
                }
                else
                {
                    /// have only one output
                    if (bCaseSensitive_)
                    {
                        func(data,  token_, len_, offset_, Term::EnglishPOS, Term::AND, level_, false);
                        tempOffset = offset_;
                    }
                    else
                    {
                        func(data, lowercaseTermUstr, len_, offset_, Term::EnglishPOS, Term::AND, level_, false);
                        tempOffset = offset_;
                    }
                }
            }
            else
            {
//              if (false /*bExtractSynonym_, preprocessed*/)
//              {
//                  UString::CharT * synonymResultUstr = NULL;
//                  size_t synonymResultUstrLen = 0;

//                  pSynonymContainer_ = uscSPtr_->getSynonymContainer();
//                  pSynonymContainer_->searchNgetSynonym(nativeToken_, pSynonymResult_);

//                  bool hasSynonym = false;
//                  for (int i =0; i<pSynonymResult_->getSynonymCount(0); i++)
//                  {
//                      char * synonymResult = pSynonymResult_->getWord(0, i);
//                      if (synonymResult)
//                      {
//                          if (strcmp(nativeToken_, synonymResult) == 0)
//                          {
//                              //cout << "synonym self: "<<string(synonymResult) <<endl;
//                              continue;
//                          }
//                          //cout << "synonym : "<<string(synonymResult) <<endl;

//                          size_t synonymResultLen = strlen(synonymResult);
//                          if (synonymResultLen <= term_ustring_buffer_limit_)
//                          {
//                              synonymResultUstr = synonym_ustring_buffer_;
//                              synonymResultUstrLen = UString::toUcs2(synonymEncode_,
//                                      synonymResult, synonymResultLen, synonym_ustring_buffer_, term_ustring_buffer_limit_);
//                          }

//                          hasSynonym = true;
//                          func(data, synonymResultUstr, synonymResultUstrLen, offset_, NULL, Term::OR, level_+1, false);
//                      }
//                  }

//                  if (hasSynonym)
//                  {
//                      func(data, token_, len_, offset_, pos_, Term::OR, level_+1, false);
//                  }
//                  else
//                  {
//                      func(data, token_, len_, offset_, pos_, topAndOrBit, level_, false);
//                  }
//              }
//              else
                {
                    func(data, token_, len_, offset_, pos_, topAndOrBit, level_, false);
                    tempOffset = offset_;
                }
            }
        }
    }
    return tempOffset + 1;
}