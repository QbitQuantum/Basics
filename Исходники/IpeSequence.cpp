void IpeSequence::describe(int offset)
{
  AstDumpToNode logger(stdout, offset + 3);
  char          pad[32] = { '\0' };

  if (offset < 32)
  {
    char* tptr = pad;

    for (int i = 0; i < offset; i++)
      *tptr++ = ' ';

    *tptr = '\0';
  }

  printf("%s#<IpeSequence\n", pad);

  for (int i = 1; i <= body.length; i++)
  {
    Expr* expr = body.get(i);

    if (isBlockStmt(expr) == true)
    {
      IpeSequence* seq = (IpeSequence*) expr;

      seq->describe(offset + 3);
    }
    else
    {
      printf("%s   ", pad);
      expr->accept(&logger);
      printf("\n");
    }
  }


  printf("%s>\n", pad);
}