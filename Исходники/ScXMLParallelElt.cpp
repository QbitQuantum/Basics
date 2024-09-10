ScXMLElt *
ScXMLParallelEltReader::read(ScXMLElt * container, cc_xml_elt * xmlelt, ScXMLDocument * doc, ScXMLStateMachine * sm)
{
  assert(container && xmlelt);
  ScXMLParallelElt * parallel = new ScXMLParallelElt;
  parallel->setContainer(container);
  this->setXMLAttributes(parallel, xmlelt);

  // handle XML attributes
  if (unlikely(!parallel->handleXMLAttributes())) {
    SoDebugError::post("ScXMLParallelEltReader::read",
                       "invalid XML attributes");
    delete parallel;
    return NULL;
  }

  const char * extref = parallel->getSrcAttribute();
  if ((extref != NULL) && (extref[0] != '\0')) {
    SbString reference(extref);
    char * eltnameref = const_cast<char *>(strchr(reference.getString(), '#'));
    if (eltnameref) {
      eltnameref[0] = '\0';
      ++eltnameref;
    }
    ScXMLDocument * refdoc = ScXMLDocument::readFile(reference.getString());
    if (refdoc) {
      ScXMLElt * parentelt = refdoc->getRoot();
      if (eltnameref) {
        parentelt = refdoc->getStateById(SbName(eltnameref));
      }
      if (parentelt) {
        if (parentelt->isOfType(ScXMLScxmlElt::getClassTypeId())) {
          ScXMLScxmlElt * parent =
            coin_assert_cast<ScXMLScxmlElt *>(parentelt);
          int c = 0;
#if 0
          if (parent->getInitial()) {
            ScXMLInitialElt * initialelt =
              coin_assert_cast<ScXMLInitialElt *>(parent->getInitial()->clone());
            parallel->setInitial(initialelt);
          }
#endif
          for (c = 0; c < parent->getNumStates(); ++c) {
            ScXMLStateElt * stateelt = ::ScXMLParallelNS::clone(parent->getState(c));
//            coin_assert_cast<ScXMLStateElt *>(parent->getState(c)->clone());
            parallel->addState(stateelt);
          }
          for (c = 0; c < parent->getNumParallels(); ++c) {
            ScXMLParallelElt * parallelelt =
              coin_assert_cast<ScXMLParallelElt *>(parent->getParallel(c)->clone());
            parallel->addParallel(parallelelt);
          }
          for (c = 0; c < parent->getNumFinals(); ++c) {
            ScXMLFinalElt * finalelt =
              coin_assert_cast<ScXMLFinalElt *>(parent->getFinal(c)->clone());
            parallel->addFinal(finalelt);
          }
          if (parent->getDataModel()) {
            ScXMLDataModelElt * datamodelelt =
              coin_assert_cast<ScXMLDataModelElt *>(parent->getDataModel()->clone());
            parallel->setDataModel(datamodelelt);
          }
#if 0
          for (c = 0; c < parent->getNumScripts(); ++c) {
            ScXMLScriptElt * scriptelt =
              coin_assert_cast<ScXMLScriptElt *>(parent->getScript(c)->clone());
            parallel->addScript(scriptelt);
          }
#endif
        }
        else if (parentelt->isOfType(ScXMLStateElt::getClassTypeId())) {
          ScXMLStateElt * parent =
            coin_assert_cast<ScXMLStateElt *>(parentelt);
          int c = 0;
          if (parent->getOnEntry()) {
            ScXMLOnEntryElt * onentryelt =
              coin_assert_cast<ScXMLOnEntryElt *>(parent->getOnEntry()->clone());
            parallel->setOnEntry(onentryelt);
          }
          if (parent->getOnExit()) {
            ScXMLOnExitElt * onexitelt =
              coin_assert_cast<ScXMLOnExitElt *>(parent->getOnExit()->clone());
            parallel->setOnExit(onexitelt);
          }
          for (c = 0; c < parent->getNumTransitions(); ++c) {
            ScXMLTransitionElt * transitionelt =
              coin_assert_cast<ScXMLTransitionElt *>(parent->getTransition(c)->clone());
            parallel->addTransition(transitionelt);
          }
#if 0
          if (parent->getInitial()) {
            ScXMLInitialElt * initialelt =
              coin_assert_cast<ScXMLInitialElt *>(parent->getInitial()->clone());
            parallel->setInitial(initialelt);
          }
#endif
          for (c = 0; c < parent->getNumStates(); ++c) {
            ScXMLStateElt * stateelt =
              coin_assert_cast<ScXMLStateElt *>(parent->getState(c)->clone());
            parallel->addState(stateelt);
          }
          for (c = 0; c < parent->getNumParallels(); ++c) {
            ScXMLParallelElt * parallelelt =
              coin_assert_cast<ScXMLParallelElt *>(parent->getParallel(c)->clone());
            parallel->addParallel(parallelelt);
          }
          for (c = 0; c < parent->getNumFinals(); ++c) {
            ScXMLFinalElt * finalelt =
              coin_assert_cast<ScXMLFinalElt *>(parent->getFinal(c)->clone());
            parallel->addFinal(finalelt);
          }
          for (c = 0; c < parent->getNumHistories(); ++c) {
            ScXMLHistoryElt * historyelt =
              coin_assert_cast<ScXMLHistoryElt *>(parent->getHistory(c)->clone());
            parallel->addHistory(historyelt);
          }
          for (c = 0; c < parent->getNumAnchors(); ++c) {
            ScXMLAnchorElt * anchorelt =
              coin_assert_cast<ScXMLAnchorElt *>(parent->getAnchor(c)->clone());
            parallel->addAnchor(anchorelt);
          }
          if (parent->getDataModel()) {
            ScXMLDataModelElt * datamodelelt =
              coin_assert_cast<ScXMLDataModelElt *>(parent->getDataModel()->clone());
            parallel->setDataModel(datamodelelt);
          }
        }
        else if (parentelt->isOfType(ScXMLParallelElt::getClassTypeId())) {
          ScXMLParallelElt * parent =
            coin_assert_cast<ScXMLParallelElt *>(parentelt);
          int c = 0;
          if (parent->getOnEntry()) {
            ScXMLOnEntryElt * onentryelt =
              coin_assert_cast<ScXMLOnEntryElt *>(parent->getOnEntry()->clone());
            parallel->setOnEntry(onentryelt);
          }
          if (parent->getOnExit()) {
            ScXMLOnExitElt * onexitelt =
              coin_assert_cast<ScXMLOnExitElt *>(parent->getOnExit()->clone());
            parallel->setOnExit(onexitelt);
          }
          for (c = 0; c < parent->getNumTransitions(); ++c) {
            ScXMLTransitionElt * transitionelt =
              coin_assert_cast<ScXMLTransitionElt *>(parent->getTransition(c)->clone());
            parallel->addTransition(transitionelt);
          }
#if 0
          if (parent->getInitial()) {
            ScXMLInitialElt * initialelt =
              coin_assert_cast<ScXMLInitialElt *>(parent->getInitial()->clone());
            parallel->setInitial(initialelt);
          }
#endif
          for (c = 0; c < parent->getNumStates(); ++c) {
            ScXMLStateElt * stateelt =
              coin_assert_cast<ScXMLStateElt *>(parent->getState(c)->clone());
            parallel->addState(stateelt);
          }
          for (c = 0; c < parent->getNumParallels(); ++c) {
            ScXMLParallelElt * parallelelt =
              coin_assert_cast<ScXMLParallelElt *>(parent->getParallel(c)->clone());
            parallel->addParallel(parallelelt);
          }
          for (c = 0; c < parent->getNumFinals(); ++c) {
            ScXMLFinalElt * finalelt =
              coin_assert_cast<ScXMLFinalElt *>(parent->getFinal(c)->clone());
            parallel->addFinal(finalelt);
          }
          for (c = 0; c < parent->getNumHistories(); ++c) {
            ScXMLHistoryElt * historyelt =
              coin_assert_cast<ScXMLHistoryElt *>(parent->getHistory(c)->clone());
            parallel->addHistory(historyelt);
          }
          for (c = 0; c < parent->getNumAnchors(); ++c) {
            ScXMLAnchorElt * anchorelt =
              coin_assert_cast<ScXMLAnchorElt *>(parent->getAnchor(c)->clone());
            parallel->addAnchor(anchorelt);
          }
          if (parent->getDataModel()) {
            ScXMLDataModelElt * datamodelelt =
              coin_assert_cast<ScXMLDataModelElt *>(parent->getDataModel()->clone());
            parallel->setDataModel(datamodelelt);
          }
        }
        else if (parentelt->isOfType(ScXMLFinalElt::getClassTypeId())) {
          // huh?
        }
      }
      delete refdoc;
    }
  }

  // read in all children, and recurse down
  const int numchildren = cc_xml_elt_get_num_children(xmlelt);
  for (int c = 0; c < numchildren; ++c) {
    cc_xml_elt * element = cc_xml_elt_get_child(xmlelt, c);
    const char * elementtype = cc_xml_elt_get_type(element);

    if (strcmp(elementtype, COIN_XML_CDATA_TYPE) == 0) {
      // ignore CDATA
      continue;
    }

    if (strcmp(elementtype, "onentry") == 0) {
      // <onentry> - zero or one time
      if (unlikely(parallel->getOnEntry())) {
        SoDebugError::post("ScXMLParallelEltReader::read",
                           "<parallel> elements can only have one <onentry> element");
        delete parallel;
        return NULL;
      }
      ScXMLEltReader * onentryreader = ScXMLOnEntryElt::getElementReader();
      ScXMLElt * onentryobj = onentryreader->read(parallel, element, doc, sm);
      if (unlikely(!onentryobj)) {
        delete parallel;
        return NULL;
      }
      assert(onentryobj->isOfType(ScXMLOnEntryElt::getClassTypeId()));
      parallel->setOnEntry(static_cast<ScXMLOnEntryElt *>(onentryobj));
    }

    else if (strcmp(elementtype, "onexit") == 0) {
      // <onexit> - zero or one time
      if (unlikely(parallel->getOnExit())) {
        SoDebugError::post("ScXMLParallelEltReader::read",
                           "<parallel> elements can only have one <onexit> element");
        delete parallel;
        return NULL;
      }
      ScXMLEltReader * onexitreader = ScXMLOnExitElt::getElementReader();
      ScXMLElt * onexitobj = onexitreader->read(parallel, element, doc, sm);
      if (unlikely(!onexitobj)) {
        delete parallel;
        return NULL;
      }
      assert(onexitobj->isOfType(ScXMLOnExitElt::getClassTypeId()));
      parallel->setOnExit(static_cast<ScXMLOnExitElt *>(onexitobj));
    }

    else if (strcmp(elementtype, "transition") == 0) {
      // <transition> - zero or more times
      ScXMLEltReader * transitionreader = ScXMLTransitionElt::getElementReader();
      ScXMLElt * transitionobj = transitionreader->read(parallel, element, doc, sm);
      if (unlikely(!transitionobj)) {
        delete parallel;
        return NULL;
      }
      assert(transitionobj->isOfType(ScXMLTransitionElt::getClassTypeId()));
      parallel->addTransition(static_cast<ScXMLTransitionElt *>(transitionobj));
    }

    else if (strcmp(elementtype, "initial") == 0) {
      // <initial> - must occur iff states+parallels >= 1
      if (unlikely(parallel->getInitial())) {
        SoDebugError::post("ScXMLInitialEltReader::read",
                           "<parallel> elements can contain only one <initial> element");
        delete parallel;
        return NULL;
      }
      ScXMLEltReader * initialreader = ScXMLInitialElt::getElementReader();
      ScXMLElt * initialobj = initialreader->read(parallel, element, doc, sm);
      if (unlikely(!initialobj)) {
        delete parallel;
        return NULL;
      }
      assert(initialobj->isOfType(ScXMLInitialElt::getClassTypeId()));
      parallel->setInitial(static_cast<ScXMLInitialElt *>(initialobj));
    }

    else if (strcmp(elementtype, "state") == 0) {
      // <state> - zero or more times
      ScXMLEltReader * statereader = ScXMLStateElt::getElementReader();
      ScXMLElt * stateobj = statereader->read(parallel, element, doc, sm);
      if (unlikely(!stateobj)) {
        delete parallel;
        return NULL;
      }
      assert(stateobj->isOfType(ScXMLStateElt::getClassTypeId()));
      parallel->addState(static_cast<ScXMLStateElt *>(stateobj));
    }

    else if (strcmp(elementtype, "parallel") == 0) {
      // <parallel> - zero or more times
      ScXMLEltReader * parallelreader = ScXMLParallelElt::getElementReader();
      ScXMLElt * parallelobj = parallelreader->read(parallel, element, doc, sm);
      if (unlikely(!parallelobj)) {
        delete parallel;
        return NULL;
      }
      assert(parallelobj->isOfType(ScXMLParallelElt::getClassTypeId()));
      parallel->addParallel(static_cast<ScXMLParallelElt *>(parallelobj));
    }

    else if (strcmp(elementtype, "final") == 0) {
      // <final> - zero or more times
      ScXMLEltReader * finalreader = ScXMLFinalElt::getElementReader();
      ScXMLElt * finalobj = finalreader->read(parallel, element, doc, sm);
      if (unlikely(!finalobj)) {
        delete parallel;
        return NULL;
      }
      assert(finalobj->isOfType(ScXMLFinalElt::getClassTypeId()));
      parallel->addFinal(static_cast<ScXMLFinalElt *>(finalobj));
    }

    else if (strcmp(elementtype, "history") == 0) {
      // <history> - zero or more times
      ScXMLEltReader * historyreader = ScXMLHistoryElt::getElementReader();
      ScXMLElt * historyobj = historyreader->read(parallel, element, doc, sm);
      if (unlikely(!historyobj)) {
        delete parallel;
        return NULL;
      }
      assert(historyobj->isOfType(ScXMLHistoryElt::getClassTypeId()));
      parallel->addHistory(static_cast<ScXMLHistoryElt *>(historyobj));
    }

    else if (strcmp(elementtype, "anchor") == 0) {
      // <anchor> - zero or more times
      ScXMLEltReader * anchorreader = ScXMLAnchorElt::getElementReader();
      ScXMLElt * anchorobj = anchorreader->read(parallel, element, doc, sm);
      if (unlikely(!anchorobj)) {
        delete parallel;
        return NULL;
      }
      assert(anchorobj->isOfType(ScXMLAnchorElt::getClassTypeId()));
      parallel->addAnchor(static_cast<ScXMLAnchorElt *>(anchorobj));
    }

    else if (strcmp(elementtype, "datamodel") == 0) {
      // <datamodel> - zero or one time
      if (unlikely(parallel->getDataModel())) {
        SoDebugError::post("ScXMLParallelEltReader::read",
                           "<parallel> elements can only have one <datamodel> element");
        delete parallel;
        return NULL;
      }
      ScXMLEltReader * datamodelreader = ScXMLDataModelElt::getElementReader();
      ScXMLElt * datamodelobj = datamodelreader->read(parallel, element, doc, sm);
      if (unlikely(!datamodelobj)) {
        delete parallel;
        return NULL;
      }
      assert(datamodelobj->isOfType(ScXMLDataModelElt::getClassTypeId()));
      parallel->setDataModel(static_cast<ScXMLDataModelElt *>(datamodelobj));
    }

#if 0
#if 0
    // <invoke> - one time iff states+parallel == 0
    else if (strcmp(elementtype, "invoke") == 0) {
      ScXMLObject * invokeobj = ScXMLP::readScXMLInvokeElt(state, element, xmlns);
      if (invokeobj) {
        assert(invokeobj->isOfType(ScXMLInvokeElt::getClassTypeId()));
        state->addInvoke(static_cast<ScXMLInvokeElt *>(invokeobj));
      } else {
        SoDebugError::post("ScXML::readFile", "error reading <%s> element", elementtype);
        delete state;
        return NULL;
      }
    }
#endif
#endif
    else {
      SoDebugError::post("ScXML::readFile",
                         "unexpected XML element '<%s>' found in <parallel>",
                         elementtype);
      delete parallel;
      return NULL;
    }
  }

  return parallel;
}