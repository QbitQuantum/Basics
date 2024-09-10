bool ClassContainer::find_type(Q3CString type, UmlTypeSpec & typespec,
			       NDict<Class> & defined) {
  typespec.explicit_type = 0;
  
  if ((typespec.type = UmlClass::used(type)) != 0)
    return TRUE;
  
  Class * cl = defined[type];
  
  if (cl == 0) {
    int index = 0;
    
    while ((index = type.find('<', index)) != -1) {
      // goes after <...>
      int index2 = index + 1;
      unsigned level = 1;
    
      for (;;) {
	int c = type[index2++];
      
	if (c == '<')
	  level += 1;
	else if (c == 0)
	  // wrong template spec
	  return FALSE;
	else if ((c == '>') && (--level == 0)) {
	  break;
	}
      }
      
      if ((type[index2] != (char)0) && (defined[type.left(index2)] != (char)0))
	// explicit template
	index = index2;
      else if (defined[type.left(index)] != 0)
	// non explicit template, remove <>
	type.remove(index, index2 - index);
      else
	// unknown type
	return FALSE;

      typespec.type = 0;
      
      if ((cl = defined[type]) != 0)
	break;
    }
  }
  
  return ((cl != 0) && ((typespec.type = cl->get_uml()) != 0));
}