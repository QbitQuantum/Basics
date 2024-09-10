void goto_program_dereferencet::dereference_rec(
  exprt &expr,
  guardt &guard,
  const value_set_dereferencet::modet mode)
{
  if(!dereference.has_dereference(expr))
    return;

  if(expr.id()==ID_and || expr.id()==ID_or)
  {
    if(!expr.is_boolean())
      throw expr.id_string()+" must be Boolean, but got "+
            expr.pretty();

    guardt old_guard=guard;

    for(unsigned i=0; i<expr.operands().size(); i++)
    {
      exprt &op=expr.operands()[i];

      if(!op.is_boolean())
        throw expr.id_string()+" takes Boolean operands only, but got "+
              op.pretty();

      if(dereference.has_dereference(op))
        dereference_rec(op, guard, value_set_dereferencet::modet::READ);

      if(expr.id()==ID_or)
      {
        exprt tmp(op);
        tmp.make_not();
        guard.add(tmp);
      }
      else
        guard.add(op);
    }

    guard.swap(old_guard);

    return;
  }
  else if(expr.id()==ID_if)
  {
    if(expr.operands().size()!=3)
      throw "if takes three arguments";

    if(!expr.op0().is_boolean())
    {
      std::string msg=
        "first argument of if must be boolean, but got "
        +expr.op0().pretty();
      throw msg;
    }

    dereference_rec(expr.op0(), guard, value_set_dereferencet::modet::READ);

    bool o1=dereference.has_dereference(expr.op1());
    bool o2=dereference.has_dereference(expr.op2());

    if(o1)
    {
      guardt old_guard=guard;
      guard.add(expr.op0());
      dereference_rec(expr.op1(), guard, mode);
      guard.swap(old_guard);
    }

    if(o2)
    {
      guardt old_guard=guard;
      exprt tmp(expr.op0());
      tmp.make_not();
      guard.add(tmp);
      dereference_rec(expr.op2(), guard, mode);
      guard.swap(old_guard);
    }

    return;
  }

  if(expr.id()==ID_address_of ||
     expr.id()=="reference_to")
  {
    // turn &*p to p
    // this has *no* side effect!

    assert(expr.operands().size()==1);

    if(expr.op0().id()==ID_dereference)
    {
      assert(expr.op0().operands().size()==1);

      exprt tmp;
      tmp.swap(expr.op0().op0());

      if(tmp.type()!=expr.type())
        tmp.make_typecast(expr.type());

      expr.swap(tmp);
    }
  }

  Forall_operands(it, expr)
    dereference_rec(*it, guard, mode);

  if(expr.id()==ID_dereference)
  {
    if(expr.operands().size()!=1)
      throw "dereference expects one operand";

    dereference_location=expr.find_source_location();

    exprt tmp=dereference.dereference(
      expr.op0(), guard, mode);

    expr.swap(tmp);
  }
  else if(expr.id()==ID_index)
  {
    // this is old stuff and will go away

    if(expr.operands().size()!=2)
      throw "index expects two operands";

    if(expr.op0().type().id()==ID_pointer)
    {
      dereference_location=expr.find_source_location();

      exprt tmp1(ID_plus, expr.op0().type());
      tmp1.operands().swap(expr.operands());

      exprt tmp2=dereference.dereference(tmp1, guard, mode);
      tmp2.swap(expr);
    }
  }
}