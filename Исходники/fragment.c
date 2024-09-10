void
Swig_fragment_emit(Node *n) {
  String *code;
  char   *pc, *tok;
  String *t;
  String *mangle = 0;
  String *name = 0;
  String *type = 0;

  if (!fragments) {
    Swig_warning(WARN_FRAGMENT_NOT_FOUND, Getfile(n), Getline(n), "Fragment '%s' not found.\n", name);
    return;
  }
  

  name = Getattr(n,k_value);
  if (!name) {
    name = n;
  }
  type = Getattr(n,k_type);
  if (type) {
    mangle = Swig_string_mangle(type);
  }

  if (debug) Printf(stdout,"looking fragment %s %s\n",name, type);
  t = Copy(name);
  tok = Char(t);
  pc = char_index(tok,',');
  if (pc) *pc = 0;
  while (tok) {
    String *name = NewString(tok);
    if (mangle) Append(name,mangle);
    if (looking_fragments && Getattr(looking_fragments,name)) {
      return;
    }    
    code = Getattr(fragments,name);
    if (debug) Printf(stdout,"looking subfragment %s\n", name);
    if (code && (Strcmp(code,k_ignore) != 0)) {
      String *section = Getmeta(code,k_section);
      Hash *nn = Getmeta(code,k_kwargs);
      if (!looking_fragments) looking_fragments = NewHash();
      Setattr(looking_fragments,name,"1");      
      while (nn) {
	if (Equal(Getattr(nn,k_name),k_fragment)) {
	  if (debug) Printf(stdout,"emitting fragment %s %s\n",nn, type);
	  Setfile(nn, Getfile(n));
	  Setline(nn, Getline(n));
	  Swig_fragment_emit(nn);
	}
	nn = nextSibling(nn);
      }
      if (section) {
	File *f = Swig_filebyname(section);
	if (!f) {
	  Swig_error(Getfile(code),Getline(code),
		     "Bad section '%s' for code fragment '%s'\n", section,name);
	} else {
	  if (debug) Printf(stdout,"emitting subfragment %s %s\n",name, section);
	  if (debug) Printf(f,"/* begin fragment %s */\n",name);
	  Printf(f,"%s\n",code);
	  if (debug) Printf(f,"/* end fragment %s */\n\n",name);
	  Setattr(fragments,name,k_ignore);
	  Delattr(looking_fragments,name);      
	}
      }
    } else if (!code && type) {
      SwigType *rtype = SwigType_typedef_resolve_all(type);
      if (!Equal(type,rtype)) {
	String *name = Copy(Getattr(n,k_value));
	String *mangle = Swig_string_mangle(type);
	Append(name,mangle);
	Setfile(name, Getfile(n));
	Setline(name, Getline(n));
	Swig_fragment_emit(name);
	Delete(mangle);
	Delete(name);
      }
      Delete(rtype);
    }
    
    if (!code) {
      Swig_warning(WARN_FRAGMENT_NOT_FOUND, Getfile(n), Getline(n), "Fragment '%s' not found.\n", name);
    }
    tok = pc ? pc + 1 : 0;
    if (tok) {
      pc = char_index(tok,',');
      if (pc) *pc = 0;
    }
    Delete(name);
  }
  Delete(t);
}