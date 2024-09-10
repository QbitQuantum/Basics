enum cpp_ttype
/* APPLE LOCAL CW asm blocks C++ comments 6338079 */
c_lex_with_flags (tree *value, location_t *loc, unsigned char *cpp_flags, int defer)
{
  static bool no_more_pch;
  const cpp_token *tok;
  enum cpp_ttype type;
  unsigned char add_flags = 0;
  /* APPLE LOCAL CW asm blocks C++ */
  const cpp_token *lasttok;
  /* APPLE LOCAL begin CW asm blocks */
  /* Make a local copy of the flag for efficiency, since the compiler can't
     figure that it won't change during a compilation.  */
  int flag_iasm_blocks_local = flag_iasm_blocks;
  if (flag_iasm_blocks_local)
    ++c_lex_depth;
  /* APPLE LOCAL end CW asm blocks */

  timevar_push (TV_CPP);
 retry:
  /* APPLE LOCAL begin CW asm blocks */
  /* If there's a token we saved while returning the special BOL
     token, return it now.  */
  if (iasm_saved_token)
    {
      tok = iasm_saved_token;
      type = tok->type;
      iasm_saved_token = NULL;
      goto bypass;
    }
  /* APPLE LOCAL end CW asm blocks */
  tok = cpp_get_token (parse_in);
  type = tok->type;

  /* APPLE LOCAL begin CW asm blocks */
  /* This test should be as efficient as possible, because it affects
       all lexing with or without CW asm enabled.  */
  if (flag_iasm_blocks_local && iasm_state != iasm_none && c_lex_depth == 1
      && type != CPP_PADDING)
    {
      /* "}" switches us out of our special mode.  */
      if (tok->type == CPP_CLOSE_BRACE && iasm_state >= iasm_decls)
	iasm_state = iasm_none;

      /* This is tricky.  We're only ready to start parsing assembly
	 instructions if we're in the asm block, we're not in the
	 middle of parsing a C decl, and the next token is plausibly
	 the beginning of an asm line.  This works because if we have
	 a "typedef int nop", a nop at the beginning of a line should
	 be taken as an instruction rather than a declaration of type
	 nop.  (Doesn't have to go this way, but it's how CW works.)
	 We're not quite as good as CW yet, because CW knows about the
	 complete list of valid opcodes, and will try to take anything
	 as a decl that is not in the opcode list.  */
      if (iasm_state == iasm_decls
	  && !iasm_in_decl)
	{
	  if (tok->type == CPP_ATSIGN
	      || tok->type == CPP_DOT
	      || (tok->type == CPP_SEMICOLON)
	      || (tok->type == CPP_NAME
		  && (*value = HT_IDENT_TO_GCC_IDENT (HT_NODE (tok->val.node)))
		  && !iasm_typename_or_reserved (*value)))
	    {
	      iasm_state = iasm_asm;
	      inside_iasm_block = true;
	    }
	  else
	    {
	      iasm_in_decl = true;
	    }
	}
    }
 bypass:
  /* APPLE LOCAL end CW asm blocks */

 retry_after_at:
#ifdef USE_MAPPED_LOCATION
  *loc = tok->src_loc;
#else
  *loc = input_location;
#endif
  switch (type)
    {
    case CPP_PADDING:
      goto retry;

    case CPP_NAME:
      *value = HT_IDENT_TO_GCC_IDENT (HT_NODE (tok->val.node));
      /* APPLE LOCAL begin CW asm blocks */
      if (iasm_state >= iasm_decls
	  && flag_ms_asms
	  && strcasecmp (IDENTIFIER_POINTER (HT_IDENT_TO_GCC_IDENT (HT_NODE (tok->val.node))),
			 "offset") == 0)
	{
	  type = CPP_AND;
	  *value = NULL_TREE;
	  break;
	}
      /* APPLE LOCAL end CW asm blocks */
      break;

    case CPP_NUMBER:
      {
	/* APPLE LOCAL CW asm blocks C++ comments 6338079 */
	unsigned int flags = cpp_classify_number (parse_in, tok, defer);

	switch (flags & CPP_N_CATEGORY)
	  {
	  case CPP_N_INVALID:
	    /* APPLE LOCAL begin CW asm blocks C++ comments 6338079 */
	    if (flags & CPP_N_DEFER)
	      {
		add_flags = ERROR_DEFERRED;
		*value = error_mark_node;
		break;
	      }
	    /* APPLE LOCAL end CW asm blocks C++ comments 6338079 */

	    /* cpplib has issued an error.  */
	    *value = error_mark_node;
	    errorcount++;
	    break;

	  case CPP_N_INTEGER:
	    /* C++ uses '0' to mark virtual functions as pure.
	       Set PURE_ZERO to pass this information to the C++ parser.  */
	    if (tok->val.str.len == 1 && *tok->val.str.text == '0')
	      add_flags = PURE_ZERO;
	    *value = interpret_integer (tok, flags);
	    break;

	  case CPP_N_FLOATING:
	    *value = interpret_float (tok, flags);
	    break;

	  default:
	    gcc_unreachable ();
	  }
      }
      break;

    case CPP_ATSIGN:
      /* APPLE LOCAL begin CW asm blocks */
      if (iasm_state >= iasm_decls)
	{
	  /* Return the @-sign verbatim.  */
	  *value = NULL_TREE;
	  break;
	}
      lasttok = tok;
      /* APPLE LOCAL end CW asm blocks */

      /* An @ may give the next token special significance in Objective-C.  */
      if (c_dialect_objc ())
	{
	  location_t atloc = input_location;

	  /* APPLE LOCAL CW asm blocks */
	  ++parse_in->keep_tokens;
	retry_at:
	  tok = cpp_get_token (parse_in);
	  type = tok->type;
	  switch (type)
	    {
	    case CPP_PADDING:
	      goto retry_at;

	    case CPP_STRING:
	    case CPP_WSTRING:
	      type = lex_string (tok, value, true);
	      break;

	    case CPP_NAME:
	      *value = HT_IDENT_TO_GCC_IDENT (HT_NODE (tok->val.node));
	      if (objc_is_reserved_word (*value))
		{
		  type = CPP_AT_NAME;
		  break;
		}
	      /* FALLTHROUGH */

	    default:
	      /* APPLE LOCAL begin CW asm blocks C++ */
	      if (flag_iasm_blocks_local)
                {
                  /* This is necessary for C++, as we don't have the tight
                     integration between the lexer and the parser... */
		  _cpp_backup_tokens (parse_in, 1);
                  /* Return the @-sign verbatim.  */
                  *value = NULL;
                  tok = lasttok;
		  type = tok->type;
                  break;
                }
	      /* APPLE LOCAL end CW asm blocks C++ */

	      /* ... or not.  */
	      error ("%Hstray %<@%> in program", &atloc);
	      goto retry_after_at;
	    }
	  /* APPLE LOCAL CW asm blocks */
	  --parse_in->keep_tokens;
	  break;
	}
	/* APPLE LOCAL begin CW asm blocks C++ */
	if (flag_iasm_blocks_local)
	  {
	    /* This is necessary for C++, as we don't have the tight
	       integration between the lexer and the parser... */
	    /* Return the @-sign verbatim.  */
	    *value = NULL;
	    break;
	  }
       /* APPLE LOCAL end CW asm blocks C++ */
	      
      /* FALLTHROUGH */
    case CPP_HASH:
    case CPP_PASTE:
      /* APPLE LOCAL begin CW asm blocks C++ comments 4248139 */
      /* Because we don't recognize inline asm commments during
	 lexing, we have to pass this back to the parser to error out
	 with or eat as a comment as appropriate.  */
      if (flag_iasm_blocks_local)
	{
	  *value = NULL;
	  break;
	}
      /* APPLE LOCAL end CW asm blocks C++ comments 4248139 */
      {
	unsigned char name[4];

	*cpp_spell_token (parse_in, tok, name, true) = 0;

	error ("stray %qs in program", name);
      }

      goto retry;

    case CPP_OTHER:
      {
	cppchar_t c = tok->val.str.text[0];

	/* APPLE LOCAL begin CW asm blocks C++ comments 4248139 */
	/* Because we don't recognize inline asm commments during
	   lexing, we have to pass this back to the parser to error
	   out with or eat as a comment as appropriate.  */
	if (defer && flag_iasm_blocks_local)
	  {
	    *value = build_int_cst_wide (char_type_node, c, 0);
	    break;
	  }
	/* APPLE LOCAL end CW asm blocks C++ comments 4248139 */
	if (c == '"' || c == '\'')
	  error ("missing terminating %c character", (int) c);
	else if (ISGRAPH (c))
	  error ("stray %qc in program", (int) c);
	else
	  error ("stray %<\\%o%> in program", (int) c);
      }
      goto retry;

    case CPP_CHAR:
    case CPP_WCHAR:
      *value = lex_charconst (tok);
      break;

    case CPP_STRING:
    case CPP_WSTRING:
      if (!c_lex_return_raw_strings)
	{
	  type = lex_string (tok, value, false);
	  break;
	}
      *value = build_string (tok->val.str.len, (char *) tok->val.str.text);
      break;
      
    case CPP_PRAGMA:
      *value = build_int_cst (NULL, tok->val.pragma);
      break;

    /* APPLE LOCAL begin CW asm blocks */
    case CPP_MULT:
      if (inside_iasm_block)
        {
	  /* Check and replace use of '*' with '.' if '*' is followed by '-'
	     or '+'. This is to allow "b *+8" which is disallwed by darwin's
	     assembler but nevertheless is needed to be compatible with CW tools. */
  	  lasttok = tok;
	  ++parse_in->keep_tokens;
	  do
              tok = cpp_get_token (parse_in);
          while (tok->type == CPP_PADDING);
	  _cpp_backup_tokens (parse_in, 1);
	  --parse_in->keep_tokens;
	  if (tok->type == CPP_PLUS || tok->type == CPP_MINUS)
	      type = CPP_DOT;
	  tok = lasttok;
        }
      *value = NULL_TREE;
      break;
    /* APPLE LOCAL end CW asm blocks */
    /* APPLE LOCAL begin 4137741 */
    /* For CPP_BINCL and CPP_EINCL tokens, we shall need to propagate
       line number information; the location field shall already include
       the desired file name.  */
    case CPP_BINCL:
    case CPP_EINCL:
      *value = build_int_cst (integer_type_node, (HOST_WIDE_INT) tok->src_loc);
      break;

    /* APPLE LOCAL end 4137741 */
      /* These tokens should not be visible outside cpplib.  */
    case CPP_HEADER_NAME:
    case CPP_COMMENT:
    case CPP_MACRO_ARG:
      gcc_unreachable ();

    default:
      *value = NULL_TREE;
      break;
    }

  if (cpp_flags)
    *cpp_flags = tok->flags | add_flags;

  /* APPLE LOCAL begin CW asm blocks */
  if (flag_iasm_blocks_local)
    --c_lex_depth;
  /* APPLE LOCAL end CW asm blocks */

    /* APPLE LOCAL begin 4137741 */
  if (!no_more_pch
      && type != CPP_BINCL
      && type != CPP_EINCL)
    /* APPLE LOCAL end 4137741 */
    {
      no_more_pch = true;
      c_common_no_more_pch ();
    }

  timevar_pop (TV_CPP);

  return type;
}