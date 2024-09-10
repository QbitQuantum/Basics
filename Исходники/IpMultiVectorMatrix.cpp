  void MultiVectorMatrix::PrintImpl(const Journalist& jnlst,
                                    EJournalLevel level,
                                    EJournalCategory category,
                                    const std::string& name,
                                    Index indent,
                                    const std::string& prefix) const
  {
    jnlst.Printf(level, category, "\n");
    jnlst.PrintfIndented(level, category, indent,
                         "%sMultiVectorMatrix \"%s\" with %d columns:\n",
                         prefix.c_str(), name.c_str(), NCols());

    for (Index i=0; i<NCols(); i++) {
      if (ConstVec(i)) {
        DBG_ASSERT(name.size()<200);
        char buffer[256];
        Snprintf(buffer, 255, "%s[%2d]", name.c_str(), i);
        std::string term_name = buffer;
        ConstVec(i)->Print(&jnlst, level, category, term_name,
                           indent+1, prefix);
      }
      else {
        jnlst.PrintfIndented(level, category, indent,
                             "%sVector in column %d is not yet set!\n",
                             prefix.c_str(), i);
      }
    }
  }