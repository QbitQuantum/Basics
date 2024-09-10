void goto_symext::rewrite_quantifiers(exprt &expr, statet &state)
{
  if(expr.id()==ID_forall)
  {
    // forall X. P -> P
    // we keep the quantified variable unique by means of L2 renaming
    assert(expr.operands().size()==2);
    assert(expr.op0().id()==ID_symbol);
    symbol_exprt tmp0=
      to_symbol_expr(to_ssa_expr(expr.op0()).get_original_expr());
    symex_decl(state, tmp0);
    exprt tmp=expr.op1();
    expr.swap(tmp);
  }
}