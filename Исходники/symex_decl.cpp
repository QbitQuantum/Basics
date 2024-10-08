void goto_symext::symex_decl(statet &state, const symbol_exprt &expr)
{
  // We increase the L2 renaming to make these non-deterministic.
  // We also prevent propagation of old values.

  ssa_exprt ssa(expr);
  state.rename(ssa, ns, goto_symex_statet::L1);
  const irep_idt &l1_identifier=ssa.get_identifier();

  // rename type to L2
  state.rename(ssa.type(), l1_identifier, ns);
  ssa.update_type();

  // in case of pointers, put something into the value set
  if(ns.follow(expr.type()).id()==ID_pointer)
  {
    exprt failed=
      get_failed_symbol(expr, ns);

    exprt rhs;

    if(failed.is_not_nil())
    {
      address_of_exprt address_of_expr;
      address_of_expr.object()=failed;
      address_of_expr.type()=expr.type();
      rhs=address_of_expr;
    }
    else
      rhs=exprt(ID_invalid);

    state.rename(rhs, ns, goto_symex_statet::L1);
    state.value_set.assign(ssa, rhs, ns, true, false);
  }

  // prevent propagation
  state.propagation.remove(l1_identifier);

  // L2 renaming
  // inlining may yield multiple declarations of the same identifier
  // within the same L1 context
  if(state.level2.current_names.find(l1_identifier)==
     state.level2.current_names.end())
    state.level2.current_names[l1_identifier]=std::make_pair(ssa, 0);
  state.level2.increase_counter(l1_identifier);
  const bool record_events=state.record_events;
  state.record_events=false;
  state.rename(ssa, ns);
  state.record_events=record_events;

  // we hide the declaration of auxiliary variables
  // and if the statement itself is hidden
  bool hidden=
    ns.lookup(expr.get_identifier()).is_auxiliary ||
    state.top().hidden_function ||
    state.source.pc->source_location.get_hide();

  target.decl(
    state.guard.as_expr(),
    ssa,
    state.source,
    hidden?symex_targett::HIDDEN:symex_targett::STATE);

  assert(state.dirty);
  if((*state.dirty)(ssa.get_object_name()) &&
     state.atomic_section_id==0)
    target.shared_write(
      state.guard.as_expr(),
      ssa,
      state.atomic_section_id,
      state.source);
}