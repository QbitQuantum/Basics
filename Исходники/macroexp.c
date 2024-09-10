static void
substitute_args (struct macro_buffer *dest, 
                 struct macro_definition *def,
		 int is_varargs, const struct macro_buffer *va_arg_name,
                 int argc, struct macro_buffer *argv,
                 struct macro_name_list *no_loop,
                 macro_lookup_ftype *lookup_func,
                 void *lookup_baton)
{
  /* A macro buffer for the macro's replacement list.  */
  struct macro_buffer replacement_list;
  /* The token we are currently considering.  */
  struct macro_buffer tok;
  /* The replacement list's pointer from just before TOK was lexed.  */
  char *original_rl_start;
  /* We have a single lookahead token to handle token splicing.  */
  struct macro_buffer lookahead;
  /* The lookahead token might not be valid.  */
  int lookahead_valid;
  /* The replacement list's pointer from just before LOOKAHEAD was
     lexed.  */
  char *lookahead_rl_start;

  init_shared_buffer (&replacement_list, (char *) def->replacement,
                      strlen (def->replacement));

  gdb_assert (dest->len == 0);
  dest->last_token = 0;

  original_rl_start = replacement_list.text;
  if (! get_token (&tok, &replacement_list))
    return;
  lookahead_rl_start = replacement_list.text;
  lookahead_valid = get_token (&lookahead, &replacement_list);

  for (;;)
    {
      /* Just for aesthetics.  If we skipped some whitespace, copy
         that to DEST.  */
      if (tok.text > original_rl_start)
        {
          appendmem (dest, original_rl_start, tok.text - original_rl_start);
          dest->last_token = dest->len;
        }

      /* Is this token the stringification operator?  */
      if (tok.len == 1
          && tok.text[0] == '#')
	{
	  int arg;

	  if (!lookahead_valid)
	    error (_("Stringification operator requires an argument."));

	  arg = find_parameter (&lookahead, is_varargs, va_arg_name,
				def->argc, def->argv);
	  if (arg == -1)
	    error (_("Argument to stringification operator must name "
		     "a macro parameter."));

	  stringify (dest, argv[arg].text, argv[arg].len);

	  /* Read one token and let the loop iteration code handle the
	     rest.  */
	  lookahead_rl_start = replacement_list.text;
	  lookahead_valid = get_token (&lookahead, &replacement_list);
	}
      /* Is this token the splicing operator?  */
      else if (tok.len == 2
	       && tok.text[0] == '#'
	       && tok.text[1] == '#')
	error (_("Stray splicing operator"));
      /* Is the next token the splicing operator?  */
      else if (lookahead_valid
	       && lookahead.len == 2
	       && lookahead.text[0] == '#'
	       && lookahead.text[1] == '#')
	{
	  int finished = 0;
	  int prev_was_comma = 0;

	  /* Note that GCC warns if the result of splicing is not a
	     token.  In the debugger there doesn't seem to be much
	     benefit from doing this.  */

	  /* Insert the first token.  */
	  if (tok.len == 1 && tok.text[0] == ',')
	    prev_was_comma = 1;
	  else
	    {
	      int arg = find_parameter (&tok, is_varargs, va_arg_name,
					def->argc, def->argv);

	      if (arg != -1)
		appendmem (dest, argv[arg].text, argv[arg].len);
	      else
		appendmem (dest, tok.text, tok.len);
	    }

	  /* Apply a possible sequence of ## operators.  */
	  for (;;)
	    {
	      if (! get_token (&tok, &replacement_list))
		error (_("Splicing operator at end of macro"));

	      /* Handle a comma before a ##.  If we are handling
		 varargs, and the token on the right hand side is the
		 varargs marker, and the final argument is empty or
		 missing, then drop the comma.  This is a GNU
		 extension.  There is one ambiguous case here,
		 involving pedantic behavior with an empty argument,
		 but we settle that in favor of GNU-style (GCC uses an
		 option).  If we aren't dealing with varargs, we
		 simply insert the comma.  */
	      if (prev_was_comma)
		{
		  if (! (is_varargs
			 && tok.len == va_arg_name->len
			 && !memcmp (tok.text, va_arg_name->text, tok.len)
			 && argv[argc - 1].len == 0))
		    appendmem (dest, ",", 1);
		  prev_was_comma = 0;
		}

	      /* Insert the token.  If it is a parameter, insert the
		 argument.  If it is a comma, treat it specially.  */
	      if (tok.len == 1 && tok.text[0] == ',')
		prev_was_comma = 1;
	      else
		{
		  int arg = find_parameter (&tok, is_varargs, va_arg_name,
					    def->argc, def->argv);

		  if (arg != -1)
		    appendmem (dest, argv[arg].text, argv[arg].len);
		  else
		    appendmem (dest, tok.text, tok.len);
		}

	      /* Now read another token.  If it is another splice, we
		 loop.  */
	      original_rl_start = replacement_list.text;
	      if (! get_token (&tok, &replacement_list))
		{
		  finished = 1;
		  break;
		}

	      if (! (tok.len == 2
		     && tok.text[0] == '#'
		     && tok.text[1] == '#'))
		break;
	    }

	  if (prev_was_comma)
	    {
	      /* We saw a comma.  Insert it now.  */
	      appendmem (dest, ",", 1);
	    }

          dest->last_token = dest->len;
	  if (finished)
	    lookahead_valid = 0;
	  else
	    {
	      /* Set up for the loop iterator.  */
	      lookahead = tok;
	      lookahead_rl_start = original_rl_start;
	      lookahead_valid = 1;
	    }
	}
      else
	{
	  /* Is this token an identifier?  */
	  int substituted = 0;
	  int arg = find_parameter (&tok, is_varargs, va_arg_name,
				    def->argc, def->argv);

	  if (arg != -1)
	    {
	      struct macro_buffer arg_src;

	      /* Expand any macro invocations in the argument text,
		 and append the result to dest.  Remember that scan
		 mutates its source, so we need to scan a new buffer
		 referring to the argument's text, not the argument
		 itself.  */
	      init_shared_buffer (&arg_src, argv[arg].text, argv[arg].len);
	      scan (dest, &arg_src, no_loop, lookup_func, lookup_baton);
	      substituted = 1;
	    }

	  /* If it wasn't a parameter, then just copy it across.  */
	  if (! substituted)
	    append_tokens_without_splicing (dest, &tok);
	}

      if (! lookahead_valid)
	break;

      tok = lookahead;
      original_rl_start = lookahead_rl_start;

      lookahead_rl_start = replacement_list.text;
      lookahead_valid = get_token (&lookahead, &replacement_list);
    }
}