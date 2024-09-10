void guardt::guard_expr(exprt &dest) const
{
  if(is_true())
  {
    // do nothing
  }
  else
  {
    if(dest.is_false())
    {
      dest=as_expr();
      dest.make_not();
    }
    else
    {
      implies_exprt tmp;
      tmp.op0()=as_expr();
      tmp.op1().swap(dest);
      dest.swap(tmp);
    }
  }
}