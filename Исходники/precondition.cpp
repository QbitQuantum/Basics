void preconditiont::compute_rec(exprt &dest)
{
  if(dest.id()==ID_address_of)
  {
    // only do index!
    assert(dest.operands().size()==1);
    compute_address_of(dest.op0());
  }
  else if(dest.id()==ID_symbol)
  {
    if(dest.get(ID_identifier)==
       s.get_original_name(SSA_step.ssa_lhs.get_identifier()))
    {
      dest=SSA_step.ssa_rhs;
      s.get_original_name(dest);
    }
  }
  else if(dest.id()==ID_dereference)
  {
    assert(dest.operands().size()==1);

    const irep_idt &lhs_identifier=
      s.get_original_name(SSA_step.ssa_lhs.get_identifier());
  
    // aliasing may happen here

    value_setst::valuest expr_set;
    value_sets.get_values(target, dest.op0(), expr_set);
    hash_set_cont<irep_idt, irep_id_hash> symbols;

    for(value_setst::valuest::const_iterator
        it=expr_set.begin();
        it!=expr_set.end();
        it++)
      find_symbols(*it, symbols);
    
    if(symbols.find(lhs_identifier)!=symbols.end())
    {
      // may alias!
      exprt tmp;
      tmp.swap(dest.op0());
      dereference(target, tmp, ns, value_sets);
      dest.swap(tmp);
      compute_rec(dest);
    }
    else
    {
      // nah, ok
      compute_rec(dest.op0());
    }
  }
  else
    Forall_operands(it, dest)
      compute_rec(*it);
}