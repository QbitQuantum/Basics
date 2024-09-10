  /*!
   * @if jp
   * @brief 途中のコンテキストを再帰的に bind しながら Object を bind する
   * @else
   * @brief Bind intermediate context recursively and bind object
   * @endif
   */
  void CorbaNaming::bindRecursive(CosNaming::NamingContext_ptr context,
				  const CosNaming::Name& name,
				  CORBA::Object_ptr obj)
    throw (SystemException, CannotProceed, InvalidName, AlreadyBound)
  {
    CORBA::ULong len(name.length());
    CosNaming::NamingContext_var cxt;
    cxt = CosNaming::NamingContext::_duplicate(context);
    
    for (CORBA::ULong i = 0; i < len; ++i)
      {
	if (i == (len - 1))
	  { // this operation may throw AlreadyBound, 
	    cxt->bind(subName(name, i, i), obj);
	    return;
	  }
	else
	  { // If the context is not a NamingContext, CannotProceed is thrown
	    if (isNamingContext(cxt))
	      cxt = bindOrResolveContext(cxt, subName(name, i, i));
	    else
	      throw CannotProceed(cxt, subName(name, i));
	  }
      }
    return;
  }