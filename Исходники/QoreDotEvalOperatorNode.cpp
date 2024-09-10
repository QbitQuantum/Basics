AbstractQoreNode *QoreDotEvalOperatorNode::parseInitImpl(LocalVar *oflag, int pflag, int &lvids, const QoreTypeInfo *&returnTypeInfo) {
   assert(!returnTypeInfo);
   const QoreTypeInfo* typeInfo = 0;
   left = left->parseInit(oflag, pflag, lvids, typeInfo);

   QoreClass* qc = const_cast<QoreClass*>(typeInfo->getUniqueReturnClass());

   const QoreMethod* meth = 0;

   const char* mname = m->getName();

   if (!qc) {
      // if the left side has a type and it's not an object, then we try to match pseudo-methods
      if (typeInfo->hasType()
	  && !objectTypeInfo->parseAccepts(typeInfo)) {
	 // check for pseudo-methods
	 bool possible_match;
	 meth = pseudo_classes_find_method(typeInfo, mname, qc, possible_match);

	 if (meth) {
	    m->setPseudo();
	    // save method for optimizing calls later
	    m->parseSetClassAndMethod(qc, meth);

	    // check parameters, if any
	    lvids += m->parseArgs(oflag, pflag, meth->getFunction(), returnTypeInfo);

	    return this;
	 }
	 else if (!possible_match && !hashTypeInfo->parseAccepts(typeInfo)) {
	    // issue an error if there was no match and it's not a hash
	    QoreStringNode* edesc = new QoreStringNode;
	    edesc->sprintf("no pseudo-method <%s>.%s() can be found", typeInfo->getName(), mname);
	    qore_program_private::makeParseException(getProgram(), loc, "PARSE-TYPE-ERROR", edesc);
	 }
      }

#ifdef DEBUG
      typeInfo = 0;
      AbstractQoreNode* n = m->parseInit(oflag, pflag, lvids, typeInfo);
      assert(n == m);
#else
      m->parseInit(oflag, pflag, lvids, typeInfo);
#endif
      return this;
   }

   // make sure method arguments and return types are resolved
   qore_class_private::parseInitPartial(*qc);

   if (!m)
      return this;

   bool m_priv = false;
   meth = qore_class_private::parseFindMethodTree(*qc, mname, m_priv);

   //printd(5, "QoreDotEvalOperatorNode::parseInitImpl() %s::%s() method: %p (%s) (private: %s)\n", qc->getName(), mname, meth, meth ? meth->getClassName() : "n/a", m_priv ? "true" : "false");
   // FIXME

   const QoreListNode* args = m->getArgs();
   if (!strcmp(mname, "copy")) {
      if (args && args->size())
	 parse_error(loc, "no arguments may be passed to copy methods (%d argument%s given in call to %s::copy())", args->size(), args->size() == 1 ? "" : "s", qc->getName());

      if (meth && meth->parseIsPrivate() && (!oflag || !qore_class_private::parseCheckCompatibleClass(*qc, *(getParseClass()))))
	 parse_error(loc, "illegal call to private %s::copy() method", qc->getName());

      // do not save method pointer for copy methods
      returnTypeInfo = qc->getTypeInfo();
#ifdef DEBUG
      typeInfo = 0;
      AbstractQoreNode *n = m->parseInit(oflag, pflag, lvids, typeInfo);
      assert(n == m);
#else
      m->parseInit(oflag, pflag, lvids, typeInfo);
#endif
      return this;
   }

   // if a normal method is not found, then look for a static method
   if (!meth)
      meth = qore_class_private::parseFindStaticMethodTree(*qc, mname, m_priv);

   if (!meth) {
      if (!qc->parseHasMethodGate()) {
	 // check if it could be a pseudo-method call
	 meth = pseudo_classes_find_method(NT_OBJECT, mname, qc);
	 if (meth)
	    m->setPseudo();
	 else
	    raiseNonExistentMethodCallWarning(qc, mname);
      }

      if (!meth) {
#ifdef DEBUG
         typeInfo = 0;
	 AbstractQoreNode *n = m->parseInit(oflag, pflag, lvids, typeInfo);
	 assert(n == m);
#else
	 m->parseInit(oflag, pflag, lvids, typeInfo);
#endif
	 return this;
      }
   }

   if (m_priv && !qore_class_private::parseCheckPrivateClassAccess(*qc))
      parse_error(loc, "illegal call to private method %s::%s()", qc->getName(), mname);
   else // save method for optimizing calls later
      m->parseSetClassAndMethod(qc, meth);

   // check parameters, if any
   lvids += m->parseArgs(oflag, pflag, meth->getFunction(), returnTypeInfo);

   printd(5, "QoreDotEvalOperatorNode::parseInitImpl() %s::%s() method=%p (%s::%s()) (private=%s, static=%s) rv=%s\n", qc->getName(), mname, meth, meth ? meth->getClassName() : "n/a", mname, meth && meth->parseIsPrivate() ? "true" : "false", meth->isStatic() ? "true" : "false", returnTypeInfo->getName());

   return this;
}