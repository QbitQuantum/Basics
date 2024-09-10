inline bool ClauseCleaner::cleanClause(XorClause& c)
{
  Lit* i, *j, *end;
  Var origVar1 = c[0].var();
  Var origVar2 = c[1].var();
  uint32_t origSize = c.size();
  for (i = j = c.getData(), end = i + c.size(); i != end; i++)
  {
    const lbool& val = solver.assigns[i->var()];
    if (val.isUndef())
    {
      *j = *i;
      j++;
    }
    else
      c.invert(val.getBool());
  }
  c.shrink(i - j);

  assert(c.size() != 1);
  switch (c.size())
  {
    case 0:
    {
      solver.detachModifiedClause(origVar1, origVar2, origSize, &c);
      return true;
    }
    case 2:
    {
      c[0] = c[0].unsign();
      c[1] = c[1].unsign();
      solver.varReplacer->replace(c, c.xor_clause_inverted(), c.getGroup());
      solver.detachModifiedClause(origVar1, origVar2, origSize, &c);
      return true;
    }
    default:
    {
      if (i - j > 0)
      {
        c.setStrenghtened();
        solver.clauses_literals -= i - j;
      }
      return false;
    }
  }

  assert(false);
  return false;
}