bool value_sett::eval_pointer_offset(
  exprt &expr,
  const namespacet &ns) const
{
  bool mod=false;

  if(expr.id()==ID_pointer_offset)
  {
    assert(expr.operands().size()==1);

    object_mapt reference_set;
    get_value_set(expr.op0(), reference_set, ns, true);

    exprt new_expr;
    mp_integer previous_offset=0;

    const object_map_dt &object_map=reference_set.read();
    for(object_map_dt::const_iterator
        it=object_map.begin();
        it!=object_map.end();
        it++)
      if(!it->second.offset_is_set)
        return false;
      else
      {
        const exprt &object=object_numbering[it->first];
        mp_integer ptr_offset=compute_pointer_offset(object, ns);

        if(ptr_offset<0)
          return false;

        ptr_offset+=it->second.offset;

        if(mod && ptr_offset!=previous_offset)
          return false;

        new_expr=from_integer(ptr_offset, index_type());
        previous_offset=ptr_offset;
        mod=true;
      }

    if(mod)
      expr.swap(new_expr);
  }
  else
  {
    Forall_operands(it, expr)
      mod=eval_pointer_offset(*it, ns) || mod;
  }

  return mod;
}