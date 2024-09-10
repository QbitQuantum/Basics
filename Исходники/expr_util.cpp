void gen_binary(exprt &expr, const std::string &id, bool default_value)
{
  if(expr.operands().size()==0)
  {
    if(default_value)
      expr.make_true();
    else
      expr.make_false();
  }
  else if(expr.operands().size()==1)
  {
    exprt tmp;
    tmp.swap(expr.op0());
    expr.swap(tmp);
  }
  else
  {
    expr.id(id);
    expr.type()=typet("bool");
  }
}