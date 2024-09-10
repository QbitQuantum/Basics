 void SumSymMatrix::PrintImpl(const Journalist& jnlst,
                              EJournalLevel level,
                              EJournalCategory category,
                              const std::string& name,
                              Index indent,
                              const std::string& prefix) const
 {
   jnlst.Printf(level, category, "\n");
   jnlst.PrintfIndented(level, category, indent,
                        "%sSumSymMatrix \"%s\" of dimension %d with %d terms:\n",
                        prefix.c_str(), name.c_str(), Dim(), NTerms());
   for (Index iterm=0; iterm<NTerms(); iterm++) {
     jnlst.PrintfIndented(level, category, indent,
                          "%sTerm %d with factor %23.16e and the following matrix:\n",
                          prefix.c_str(), iterm, factors_[iterm]);
     char buffer[256];
     Snprintf(buffer, 255, "Term: %d", iterm);
     std::string name = buffer;
     matrices_[iterm]->Print(&jnlst, level, category, name, indent+1, prefix);
   }
 }