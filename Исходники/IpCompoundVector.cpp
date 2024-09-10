 void CompoundVector::PrintImpl(const Journalist& jnlst,
                                EJournalLevel level,
                                EJournalCategory category,
                                const std::string& name,
                                Index indent,
                                const std::string& prefix) const
 {
   DBG_START_METH("CompoundVector::PrintImpl", dbg_verbosity);
   jnlst.Printf(level, category, "\n");
   jnlst.PrintfIndented(level, category, indent,
                        "%sCompoundVector \"%s\" with %d components:\n",
                        prefix.c_str(), name.c_str(), NComps());
   for (Index i=0; i<NComps(); i++) {
     jnlst.Printf(level, category, "\n");
     jnlst.PrintfIndented(level, category, indent,
                          "%sComponent %d:\n", prefix.c_str(), i+1);
     if (ConstComp(i)) {
       DBG_ASSERT(name.size()<200);
       char buffer[256];
       Snprintf(buffer, 255, "%s[%2d]", name.c_str(), i);
       std::string term_name = buffer;
       ConstComp(i)->Print(&jnlst, level, category, term_name,
                           indent+1, prefix);
     }
     else {
       jnlst.PrintfIndented(level, category, indent,
                            "%sComponent %d is not yet set!\n",
                            prefix.c_str(), i+1);
     }
   }
 }