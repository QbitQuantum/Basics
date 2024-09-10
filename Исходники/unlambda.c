struct expression_s *
parse (FILE *input)
{
  int ch;
  do {
    ch = getc (input);
    if ( ch == '#' )
      while ( ch != '\n' && ch != EOF )
	ch = getc (input);
  } while ( ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' );
  if ( ch == '`' )
    {
      struct expression_s *rator = parse (input);
      struct expression_s *rand = parse (input);
      struct expression_s *expr = new_expression ();

      expr->t = EXPRESSION_APPLICATION;
      init_ptr (&expr->d.expression_application_v.rator, rator);
      init_ptr (&expr->d.expression_application_v.rand, rand);
#if 0  /* Harmless but not necessary */
      free_expression (rator);
      free_expression (rand);
#endif
      return expr;
    }
  else if ( ch == 'i' || ch == 'I' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_I;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 'k' || ch == 'K' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_K;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 's' || ch == 'S' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_S;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 'v' || ch == 'V' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_V;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 'd' || ch == 'D' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_D;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 'e' || ch == 'E' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_E;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 'p' || ch == 'P' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_P;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 'f' || ch == 'F' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_F;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == 'r' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_DOT;
      fun->d.function_dot_v = '\n';
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == '.' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();
      int ch2;

      fun->t = FUNCTION_DOT;
      ch2 = getc (input);
      if ( ch2 == EOF )
	goto ueof;
      fun->d.function_dot_v = ch2;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == '@' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_AT;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == '?' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();
      int ch2;

      fun->t = FUNCTION_QUES;
      ch2 = getc (input);
      if ( ch2 == EOF )
	goto ueof;
      fun->d.function_ques_v = ch2;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == '|' )
    {
      struct function_s *fun = new_function ();
      struct expression_s *expr = new_expression ();

      fun->t = FUNCTION_PIPE;
      expr->t = EXPRESSION_FUNCTION;
      init_ptr (&expr->d.expression_function_v, fun);
#if 0  /* Harmless but not necessary */
      free_function (fun);
#endif
      return expr;
    }
  else if ( ch == EOF )
    {
    ueof:
      fprintf (stderr, "Unexpected end of file\n");
      exit (1);
    }
  else
    {
      fprintf (stderr, "Character not recognized: %c\n", ch);
      exit (1);
    }
  return NULL;
}