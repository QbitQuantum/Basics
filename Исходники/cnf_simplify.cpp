void cnf_join_binary(exprt &expr)
{
  Forall_operands(it, expr)
    cnf_join_binary(*it);

  if(expr.id()==ID_and || expr.id()==ID_or || expr.id()==ID_xor ||
     expr.id()==ID_bitand || expr.id()==ID_bitor || expr.id()==ID_bitxor)
  {
    exprt tmp;

    if(expr.operands().size()==1)
    {
      tmp.swap(expr.op0());
      expr.swap(tmp);
    }
    else
    {
      unsigned count=0;

      forall_operands(it, expr)
      {
        if(it->id()==expr.id())
          count+=it->operands().size();
        else
          count++;
      }

      tmp.operands().reserve(count);

      Forall_operands(it, expr)
      {
        if(it->id()==expr.id())
        {
          Forall_operands(it2, *it)
            tmp.move_to_operands(*it2);
        }
        else
          tmp.move_to_operands(*it);
      }

      expr.operands().swap(tmp.operands());
    }
  }