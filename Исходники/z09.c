OBJECT ClosureExpand(OBJECT x, OBJECT env, BOOLEAN crs_wanted,
OBJECT *crs, OBJECT *res_env)
{ OBJECT link, y, res, prnt_env, par, prnt;
  debug3(DCE, D, "[ ClosureExpand( %s, %s, %s, crs, res_env )",
    EchoObject(x), EchoObject(env), bool(crs_wanted));
  assert( type(x) == CLOSURE, "ClosureExpand given non-CLOSURE!");
  assert( predefined(actual(x)) == FALSE, "ClosureExpand given predefined!" );

  /* add tag to x if needed but not provided;  add cross-reference to crs  */
  if( has_tag(actual(x)) )  CrossAddTag(x);
  if( crs_wanted && has_tag(actual(x)) )
  { OBJECT tmp = CopyObject(x, no_fpos);  AttachEnv(env, tmp);
    y = CrossMake(actual(x), tmp, CROSS_TARG);
    New(tmp, CROSS_TARG);  actual(tmp) = y;  Link(tmp, y);
    if( *crs == nilobj )  New(*crs, CR_LIST);   Link(*crs, tmp);
  }

  /* case x is a parameter */
  res = *res_env = nilobj;
  if( is_par(type(actual(x))) )
  { prnt = SearchEnv(env, enclosing(actual(x)));
    if( prnt != nilobj )
    {
      prnt_env = GetEnv(prnt);
      for( link = Down(prnt);  link != prnt;  link = NextDown(link) )
      { Child(par, link);
        if( type(par) == PAR && actual(par) == actual(x) )
        { assert( Down(par) != par, "ExpandCLosure: Down(par)!");
	  Child(res, Down(par));
	  if( dirty(enclosing(actual(par))) || is_enclose(actual(par)) )
	  { debug2(DCE, DD, "copy %s %s", SymName(actual(par)), EchoObject(res));
	    res = CopyObject(res, no_fpos);
	  }
	  else
	  {
	    debug2(DCE, DD, "link %s %s",
	      FullSymName(actual(par), AsciiToFull(".")), EchoObject(res));
	    DeleteLink(Down(par));
	    y = MakeWord(WORD, STR_NOCROSS, &fpos(res));
	    Link(par, y);
	  }
	  ReplaceNode(res, x);
	  if( type(actual(x)) == RPAR && has_body(enclosing(actual(x))) )
	  { debug0(DCR, DDD, "  calling SetEnv from ClosureExpand (a)");
	    *res_env = SetEnv(prnt, nilobj);  DisposeObject(x);
	  }
	  else if( type(actual(x)) == NPAR && imports_encl(actual(x)) )
	  { debug0(DCR, DDD, "  calling SetEnv from ClosureExpand (x)");
	    AttachEnv(env, x);
	    *res_env = SetEnv(x, nilobj);
	  }
	  else
	  { AttachEnv(env, x);
	    debug0(DCR, DDD, "  calling SetEnv from ClosureExpand (b)");
	    *res_env = SetEnv(x, prnt_env);
	  }
	  break;
        }
      }
    }
    else
    {
      /* fail only if there is no default value available */
      if( sym_body(actual(x)) == nilobj )
      {
        debug3(DCE, D, "failing ClosureExpand( %s, crs, %s, %s, res_env )",
	  EchoObject(x), bool(crs_wanted), EchoObject(env));
        Error(9, 2, "no value for parameter %s of symbol %s:", WARN, &fpos(x),
	  SymName(actual(x)), SymName(enclosing(actual(x))));
        Error(9, 1, "symbol with import list misused", FATAL, &fpos(x));
      }
    }
  }

  /* case x is a user-defined symbol or default parameter */
  if( res == nilobj )
  { if( sym_body(actual(x)) == nilobj )
      res = MakeWord(WORD, STR_NOCROSS, &fpos(x));
    else
      res = CopyObject(sym_body(actual(x)), &fpos(x));
    ReplaceNode(res, x);  AttachEnv(env, x);
    debug0(DCR, DDD, "  calling SetEnv from ClosureExpand (c)");
    *res_env = SetEnv(x, nilobj);
  }

  assert( *res_env!=nilobj && type(*res_env)==ENV, "ClosureExpand: *res_env!");
  debug0(DCE, D, "] ClosureExpand returning, res =");
  ifdebug(DCE, D, DebugObject(res));
  debug1(DCE, D, "  environment = %s", EchoObject(*res_env));
  return res;
} /* end ClosureExpand */