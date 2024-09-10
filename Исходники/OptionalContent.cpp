OCGs::OCGs(Object *ocgObject, XRef *xref) :
  m_xref(xref)
{
  // we need to parse the dictionary here, and build optionalContentGroups
  ok = gTrue;
  optionalContentGroups = new GooList();

  Object ocgList;
  ocgObject->dictLookup("OCGs", &ocgList);
  if (!ocgList.isArray()) {
    error(-1, "Expected the optional content group list, but wasn't able to find it, or it isn't an Array");
    ocgList.free();
    ok = gFalse;
    return;
  }

  // we now enumerate over the ocgList, and build up the optionalContentGroups list.
  for(int i = 0; i < ocgList.arrayGetLength(); ++i) {
    Object ocg;
    ocgList.arrayGet(i, &ocg);
    if (!ocg.isDict()) {
      ocg.free();
      break;
    }
    OptionalContentGroup *thisOptionalContentGroup = new OptionalContentGroup(ocg.getDict());
    ocg.free();
    ocgList.arrayGetNF(i, &ocg);
    // TODO: we should create a lookup map from Ref to the OptionalContentGroup
    thisOptionalContentGroup->setRef( ocg.getRef() );
    ocg.free();
    // the default is ON - we change state later, depending on BaseState, ON and OFF
    thisOptionalContentGroup->setState(OptionalContentGroup::On);
    optionalContentGroups->append(thisOptionalContentGroup);
  }

  Object defaultOcgConfig;
  ocgObject->dictLookup("D", &defaultOcgConfig);
  if (!defaultOcgConfig.isDict()) {
    error(-1, "Expected the default config, but wasn't able to find it, or it isn't a Dictionary");
    defaultOcgConfig.free();
    ocgList.free();
    ok = gFalse;
    return;
  }
#if 0
  // this is untested - we need an example showing BaseState
  Object baseState;
  defaultOcgConfig.dictLookup("BaseState", &baseState);
  if (baseState.isString()) {
    // read the value, and set each OptionalContentGroup entry appropriately
  }
  baseState.free();
#endif
  Object on;
  defaultOcgConfig.dictLookup("ON", &on);
  if (on.isArray()) {
    // ON is an optional element
    for (int i = 0; i < on.arrayGetLength(); ++i) {
      Object reference;
      on.arrayGetNF(i, &reference);
      if (!reference.isRef()) {
	// there can be null entries
	reference.free();
	break;
      }
      OptionalContentGroup *group = findOcgByRef( reference.getRef() );
      reference.free();
      if (!group) {
	error(-1, "Couldn't find group for reference");
	break;
      }
      group->setState(OptionalContentGroup::On);
    }
  }
  on.free();

  Object off;
  defaultOcgConfig.dictLookup("OFF", &off);
  if (off.isArray()) {
    // OFF is an optional element
    for (int i = 0; i < off.arrayGetLength(); ++i) {
      Object reference;
      off.arrayGetNF(i, &reference);
      if (!reference.isRef()) {
	// there can be null entries
	reference.free();
	break;
      }
      OptionalContentGroup *group = findOcgByRef( reference.getRef() );
      reference.free();
      if (!group) {
	error(-1, "Couldn't find group for reference to set OFF");
	break;
      }
      group->setState(OptionalContentGroup::Off);
    }
  }
  off.free();

  defaultOcgConfig.dictLookup("Order", &order);
  defaultOcgConfig.dictLookup("RBGroups", &rbgroups);

  ocgList.free();
  defaultOcgConfig.free();
}