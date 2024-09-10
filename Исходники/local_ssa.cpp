void local_SSAt::replace_side_effects_rec(
  exprt &expr, locationt loc, unsigned &counter) const
{
  Forall_operands(it, expr)
    replace_side_effects_rec(*it, loc, counter);

  if(expr.id()==ID_side_effect)
  {
    const side_effect_exprt &side_effect_expr=
      to_side_effect_expr(expr);
    const irep_idt statement=side_effect_expr.get_statement();

    if(statement==ID_nondet)
    {
      // turn into nondet_symbol
      exprt nondet_symbol(ID_nondet_symbol, expr.type());
      counter++;
      const irep_idt identifier=
        "ssa::nondet"+
        i2string(loc->location_number)+
        "."+i2string(counter)+suffix;
      nondet_symbol.set(ID_identifier, identifier);
      
      expr.swap(nondet_symbol);
    }
    else if(statement==ID_malloc)
    {
      counter++;
      std::string tmp_suffix=
        i2string(loc->location_number)+
        "."+i2string(counter)+suffix;
      expr=malloc_ssa(side_effect_expr, tmp_suffix, ns);
    }
    else
      throw "unexpected side effect: "+id2string(statement);
  }
}