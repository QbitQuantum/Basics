bool simplify_exprt::simplify_floatbv_op(exprt &expr)
{
  const typet &type=ns.follow(expr.type());

  if(type.id()!=ID_floatbv)
    return true;

  assert(expr.operands().size()==3);

  exprt op0=expr.op0();
  exprt op1=expr.op1();
  exprt op2=expr.op2(); // rounding mode

  assert(ns.follow(op0.type())==type);
  assert(ns.follow(op1.type())==type);

  // Remember that floating-point addition is _NOT_ associative.
  // Thus, we don't re-sort the operands.
  // We only merge constants!

  if(op0.is_constant() && op1.is_constant() && op2.is_constant())
  {
    ieee_floatt v0(to_constant_expr(op0));
    ieee_floatt v1(to_constant_expr(op1));

    mp_integer rounding_mode;
    if(!to_integer(op2, rounding_mode))
    {
      v0.rounding_mode=(ieee_floatt::rounding_modet)integer2size_t(rounding_mode);
      v1.rounding_mode=v0.rounding_mode;

      ieee_floatt result=v0;

      if(expr.id()==ID_floatbv_plus)
        result+=v1;
      else if(expr.id()==ID_floatbv_minus)
        result-=v1;
      else if(expr.id()==ID_floatbv_mult)
        result*=v1;
      else if(expr.id()==ID_floatbv_div)
        result/=v1;
      else
        assert(false);

      expr=result.to_expr();
      return false;
    }
  }

  // division by one? Exact for all rounding modes.
  if (expr.id()==ID_floatbv_div &&
      op1.is_constant() && op1.is_one())
  {
    exprt tmp;
    tmp.swap(op0);
    expr.swap(tmp);
    return false;
  }

  return true;
}