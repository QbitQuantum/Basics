void UmlRelation::compute_dependency(Q3PtrList<CppRefType> & dependencies,
				     const Q3CString & cl_stereotype,
				     bool all_in_h) {
  if (cl_stereotype == "enum")
    return;
  
  switch (relationKind()) {
  case aDependency:
    if (stereotype() == "friend")
      break;
    CppRefType::add(roleType(), dependencies, cppDecl() != "#include in source",
		    roleType()->isCppExternal());
    break;
  case aGeneralisation:
  case aRealization:
    CppRefType::add(roleType(), dependencies, TRUE);
    break;
  default:
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
    if ((index = decl.find("${name}")) != -1)
      decl.remove((unsigned) index, 7);
    if ((index = decl.find("${inverse_name}")) != -1)
      decl.remove((unsigned) index, 15);
    if ((index = decl.find("${value}")) != -1)
      decl.remove((unsigned) index, 8);
    if ((index = decl.find("${h_value}")) != -1)
      decl.remove((unsigned) index, 10);
    if ((index = decl.find("${stereotype}")) != -1)
      decl.replace((unsigned) index, 13,
		   CppSettings::relationAttributeStereotype(stereotype()));
    if ((index = decl.find("${association}")) != -1) {
      decl.replace((unsigned) index, 14,
		   association().toString());
    }
    replace_alias(decl);
    
    UmlTypeSpec type;
    
    type.type = roleType();
    UmlClassMember::compute_dependency(dependencies, decl, type, all_in_h);
  }
}