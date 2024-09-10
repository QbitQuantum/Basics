void UmlAttribute::compute_dependency(Q3PtrList<CppRefType> & dependency,
				      const Q3CString & cl_stereotype,
				      bool all_in_h) {
  if ((cl_stereotype == "enum") || (cl_stereotype == "typedef"))
    return;
  
  Q3CString decl = cppDecl();
  
  int index;
  
  if ((index = decl.find("${static}")) != -1)
    decl.remove((unsigned) index, 9);
  if ((index = decl.find("${mutable}")) != -1)
    decl.remove((unsigned) index, 10);
  if ((index = decl.find("${volatile}")) != -1)
    decl.remove((unsigned) index, 11);
  if ((index = decl.find("${const}")) != -1)
    decl.remove((unsigned) index, 8);
  if ((index = decl.find("${multiplicity}")) != -1)
    decl.remove((unsigned) index, 15);
  if ((index = decl.find("${value}")) != -1)
    decl.remove((unsigned) index, 8);
  if ((index = decl.find("${h_value}")) != -1)
    decl.remove((unsigned) index, 10);
  if ((index = decl.find("${name}")) != -1)
    decl.remove((unsigned) index, 7);
  if ((index = decl.find("${stereotype}")) != -1)
    decl.replace((unsigned) index, 13,
		 CppSettings::relationAttributeStereotype(stereotype()));
  replace_alias(decl);

  if (!UmlClassMember::compute_dependency(dependency, decl, type(), all_in_h)) {
    write_trace_header();
    UmlCom::trace(Q3CString("&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"red\"><b>type missing for attribute <i>")
		  + name() + "</i></b></font><br>");
    incr_error();
  }
}